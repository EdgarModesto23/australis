#include <cstdint>
#include <exception>
#include <iostream>
#include <seastar/core/app-template.hh>
#include <seastar/core/do_with.hh>
#include <seastar/core/future.hh>
#include <seastar/core/loop.hh>
#include <seastar/core/reactor.hh>
#include <seastar/core/seastar.hh>
#include <seastar/core/sleep.hh>
#include <seastar/core/smp.hh>
#include <seastar/core/temporary_buffer.hh>
#include <seastar/net/api.hh>
#include <seastar/util/log.hh>
#include <sys/socket.h>
#include <utility>

const char *canned_response = "+PONG\r\n";

constexpr uint16_t PORT = 6379;

seastar::future<> main_australis() {
  seastar::logger logger{"main"};
  seastar::listen_options lo;
  lo.reuse_address = true;
  logger.info("Listening on port: {}", PORT);
  return seastar::do_with(
      seastar::listen(seastar::make_ipv4_address({PORT}), lo),
      [](auto &listener) {
        return seastar::keep_doing([&listener]() {
          return listener.accept().then([](seastar::accept_result res) {
            auto s = std::move(res.connection);
            auto in = s.input();
            auto out = s.output();
            auto const data =
                in.read().then([](seastar::temporary_buffer<char> data) {
                  std::cout << data.get() << '\n';
                });
            return seastar::do_with(
                std::move(s), std::move(out), [](auto &s, auto &out) {
                  return out.write(canned_response).then([&out] {
                    return out.close();
                  });
                });
          });
        });
      });
};

auto main(int argc, char **argv) -> int {

  seastar::app_template app;
  try {
    app.run(argc, argv, main_australis);
  } catch (...) {
    std::cerr << "Couldn't start application: " << std::current_exception()
              << "\n";
    return 1;
  }
  return 0;
}
