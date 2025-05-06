add_executable(test_resp resp_test.cc)

target_link_libraries(test_resp PRIVATE GTest::gtest_main resp)

gtest_discover_tests(test_resp)
