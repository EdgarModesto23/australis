#include <memory>
#include <string>
#include <vector>

namespace resp_types {
enum StrType { Simple, Bulk, Unknown };

class Encode {
public:
  virtual std::string encode() = 0;
  virtual ~Encode() = default;
};

class R_String : public Encode {
private:
  std::string m_Value;
  StrType m_StrType;

public:
  std::string encode() override;
  R_String(std::string data, int ptr);
  R_String(std::string data, int ptr, int len);
};

class R_Vec : public Encode {
private:
  std::vector<std::unique_ptr<Encode>> m_Values;

public:
  std::string encode() override;
  R_Vec(std::string data, int ptr);
};
} // namespace resp_types
