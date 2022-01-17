#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

#include "types_tests.h"

class CoutRedirect {
public:
  CoutRedirect() {
    old = std::cout.rdbuf(buffer.rdbuf());
  }

  ~CoutRedirect() {
    std::cout.rdbuf(old);
  }

  std::string getString() {
    return buffer.str();
  }
private:
    std::stringstream buffer;
    std::streambuf* old;
};

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
