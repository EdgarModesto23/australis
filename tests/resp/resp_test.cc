#include <gtest/gtest.h>

TEST(BasicProtocol, SimpleString) {

  constexpr char *t_Ping = "+PING\r\n";

  EXPECT_STRNE("Hey", "a");
}
