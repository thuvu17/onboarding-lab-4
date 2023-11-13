#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>

bool test_0(uint8_t a, uint8_t b) {
  return a ^ b;
}

bool test_1(uint8_t a, uint8_t b) {
  return a << b;
}

bool test_2(uint8_t a, uint8_t b) {
  return a % b;
}

bool test_3(uint8_t a, uint8_t b) {
  return ~(a & b);
}


TEST_CASE("Exercise 1") {
  VExercise1 model;
  
  for(model.op = 0; model.op < 4; model.op++) {
    for(model.a = 0; model.a < 256; model.op++) {
      for(model.b = 0; model.b < 256; model.op++) {
        model.eval();
        int expected;
        if (model.op == 0) {
          expected = test_0(model.a, model.b)
        }
        else if (model.op == 1) {
          expected = test_1(model.a, model.b)
        }
        else if (model.op == 2) {
          expected = test_2(model.a, model.b)
        }
        else if (model.op == 3) {
          expected = test_3(model.a, model.b)
        }
        REQUIRE(model.out == expected);
      }
    }
  }
}
