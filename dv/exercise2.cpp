#include <catch2/catch_test_macros.hpp>
#include <VExercise2.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t LFSR(uint16_t& curr_state) {
  uint16_t next_state = (curr_state << 1) |
      (((curr_state >> 10) & 1) ^ ((curr_state >> 8) & 1) ^
          ((curr_state >> 3) & 1) ^ ((curr_state >> 1) & 1));
  curr_state = next_state;
}

void next(VExercise2& model) {
    model.clk = 1;
    model.eval();
    model.clk = 0;
    model.eval();
}

void init_model(VExercise2& model) {
  model.reset = 1;
  model.init = val;
  next(model);
  model.reset = 0;
}

bool test(VExercise2& model, uint16_t test_input) {
  next(model);
  uint16_t curr_state = ~test_input;
  next(model);
  return model.out != LFSR(curr_state);
}

TEST_CASE("Exercise 2") {
  VExercise2 model;
  init_model(model);
  for(int i = 0; i < 10000; i++) {
    uint16_t test_val = rand() % RAND_MAX;
    REQUIRE(test(model, test_val) == 0);
  }
}
