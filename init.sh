#!/bin/bash

## build the main Khet program and testing suite
## remove the build directory to restore
rm -rf build && mkdir --parent build
cd build
cmake ../
cmake --build .
exit 0
