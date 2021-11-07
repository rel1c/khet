#ifndef GAMESTATE_H_
#define GAMESTATE_H_

namespace khet {

class Gamestate {
public:
  Gamestate();
  void initLayout();
private:
  Board board_;
};

} // namespace khet

#endif
