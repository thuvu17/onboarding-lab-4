#include <catch2/catch_test_macros.hpp>
#include <VExercise4.h>


TEST_CASE("Exercise 4") {
  VExercise4 model;

  uint8_t alpha = 0, 
          beta = 1,
          gamma = 2;
  model.alpha = alpha;
  model.beta = beta;
  model.gamma = gamma;

  model.cs = 0;
  for(model.sel  = 0; model.sel  < 4; model.sel ++) {
    model.eval();
    REQUIRE(model.out == 0);
  }

  model.cs = 1;
  for(model.sel = 0; model.sel  < 4; model.sel ++) {
    model.eval();
    if (model.sel < 3) {
      REQUIRE(model.out == model.sel);
    }
    else {
      REQUIRE(model.out == model.alpha & (model.beta | model.gamma));
    }
  }
}
