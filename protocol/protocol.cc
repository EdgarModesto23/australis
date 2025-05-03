#include "protocol.hh"
#include <boost/parser/parser.hpp>
#include <string>
#include <vector>

namespace bp = boost::parser;

std::vector<std::string> resp_protocol::parse_request(std::string req) {
  auto const result = bp::parse(req, bp::double_ % ',');

  return std::vector<std::string>{};
}
