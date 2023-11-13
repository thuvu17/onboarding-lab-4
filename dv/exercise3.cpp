#include <catch2/catch_test_macros.hpp>
#include <VExercise3.h>
#include <cstdint>
#include <stdlib.h>

uint8_t mystery_1(uint8_t a, uint8_t b, uint8_t c) {
  uint8_t d = 0;
  if (a == 0) 
    d = ((b & 7) << 3) | (c & 7);
  else if (a == 1) 
    d = (1 << 6) | ((c & 7) << 3) | (b & 7);
  else if (a == 2) 
    d = b;
  else if (a == 3)
    d = c;
  return d;
}

uint16_t mystery_2(uint8_t a, uint8_t b, bool reset) {
  uint16_t output;
  uint8_t state = 0;
  if (reset) {
    return (b << 8) | a;
  }
  else {
    switch(state) {
      case 0:
        output = (a << 8) | (output & 255);
        break;
      case 1:
        output = (output & 65280) | (b & 255);
        break;
      case 2:
        output = (output << 8) | (output >> 8);
        break;
      case 3:
        output = (output << 12) | ((output & 240) << 4) | ((output & 3840) >> 4) | ((output & 61440) >> 12);
        break;
      case 4:
        bool new_out = output & 1;
        for (int i = 0; i < 16; i++) {
          new_out = new_out ^ ((output >> i) & 1);
        }
        break;
        state++;
        state %= 5;
        output = new_out;
        return output;
    }
  }
}
        


TEST_CASE("Exercise 3") {
  VExercise3 model;

  bool failed = false;
  
  bool reset;
  bool clk;
  uint8_t a;
  uint16_t b, c;
  
  for (int i = 0; i < 100; i++) {
    a = rand() % 15;
    b = rand() % 65535;
    c = rand() % 65535;
    
    // Initial state
    model.clk = 1;
    model.reset = 0;
    model.eval();
    
    // High reset
    model.clk = 0;
    model.reset = 1;
    model.a = a;
    model.b = b;
    model.c = c;
    model.eval();
    
    uint8_t a_test = mystery_1((a & 3), (b & 255), (c & 255));
    uint8_t b_test = mystery_1((a >> 2), (b >> 8), (c >> 8));
    REQUIRE(model.output == mystery_2(a_test, b_test, 1));

    // Low reset
    for (int step = 0; step < 5; step++) {
      model.clk = 1;
      model.reset = 0;
      model.eval();
    
      model.clk = 0;
      model.reset = 0;
      model.a = a;
      model.b = b;
      model.c = c;
      model.eval();
      REQUIRE(model.output == mystery_2(a_test, b_test, 1));
    }
}
