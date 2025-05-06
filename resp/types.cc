#include "types.hh"
#include <fmt/format.h>
#include <stdexcept>
#include <string>

using namespace resp_types;

std::string R_String::encode() {
  if (m_StrType == StrType::Simple) {
    return "+" + m_Value + "\r\n";
  } else if (m_StrType == StrType::Bulk) {
    return "$" + std::to_string(m_Value.size()) + "\r\n" + m_Value + "\r\n";
  } else {
    throw std::invalid_argument("Unknown StrType");
  }
}

std::string R_Vec::encode() {
  std::string res{fmt::format("*{}", m_Values.size())};
  for (const auto &val : m_Values) {
    res.append(val->encode());
  }
  return res;
}
