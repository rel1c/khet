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
