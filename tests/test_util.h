#include <tuple>

#ifndef TEST_UTIL_H_
#define TEST_UTIL_H_

const bool SKIP_DEATH = 1;

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

#endif
