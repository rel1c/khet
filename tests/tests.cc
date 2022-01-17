#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>

#include "piece_tests.h"
#include "board_tests.h"

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
