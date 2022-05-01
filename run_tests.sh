#!/bin/bash

CLEAR="clear"

if type tmux >/dev/null 2>/dev/null; then
  if [ "$TERM_PROGRAM" = tmux ]; then
    CLEAR+=" && tmux clear-history"
  fi
fi

eval $CLEAR && cmake --build ./build && ./build/tests
