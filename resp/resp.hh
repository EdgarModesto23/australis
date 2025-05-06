#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace resp_protocol {
constexpr std::string_view OK = "+OK\r\n";

template <typename T> class DataType {
private:
  T m_Value;
  size_t m_Size;

public:
  T get() { return m_Value; }

  DataType<T>(T value, size_t size) : m_Value(value), m_Size(size){};
};

class Command {
public:
  virtual std::string serve() = 0;
  virtual std::unique_ptr<Command> move() const = 0;
  virtual ~Command() = default;
};

class Ping : public Command {
private:
  std::string m_Message;

public:
  std::string serve() override;
  std::unique_ptr<Command> move() const override;
  Ping() : m_Message() {};
  explicit Ping(std::string &&message) : m_Message(std::move(message)) {};
  Ping(std::string_view message) : m_Message(message) {};
};

class Request {
private:
  std::vector<std::unique_ptr<Command>> m_Queue;
  // seastar::connected_socket m_Conn;

public:
  Request(Command &c) : m_Queue{} { m_Queue.emplace_back(c.move()); };
  Request() : m_Queue{} {};
};

Request parse_request(std::string req);
} // namespace resp_protocol
