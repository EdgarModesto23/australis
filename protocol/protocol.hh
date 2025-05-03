#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace resp_protocol {
constexpr std::string_view OK = "+OK\r\n";

template <typename T> class DataType {
private:
  T value;
  size_t size;

public:
  T get() { return value; }

  DataType<T>(T value, size_t size) : value(value), size(size){};
};

std::vector<std::string> parse_request(std::string req);
} // namespace resp_protocol
