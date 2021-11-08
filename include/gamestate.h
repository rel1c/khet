#ifndef GAMESTATE_H_
#define GAMESTATE_H_

namespace khet {

enum Layout {
  CLASSIC,
  IMHOTEP,
  DYNASTY
};

class Gamestate {
public:
  Gamestate(Layout);
  void initLayout(Layout);
private:
  Board board_;
};

} // namespace khet

#endif
