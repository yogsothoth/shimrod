#define CATCH_CONFIG_MAIN

#include "catch.hpp"

/*unsigned int Factorial(unsigned int number) {
  return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
  }*/

#include <complex>
#include "Viewport.h"

using shimrod::Viewport;
using shimrod::linear_projection;

TEST_CASE("Viewports can be created", "[viewports]") {
  Viewport<int> v(1,2,3,4);
    REQUIRE(v.get_x_min() == 1);
    REQUIRE(v.get_x_max() == 2);
    REQUIRE(v.get_y_min() == 3);
    REQUIRE(v.get_y_max() == 4);
}

TEST_CASE("Viewports can calculate their dimensions", "[viewports]") {
    Viewport<int> v1(0,2,0,4);
    Viewport<int> v2(-2, 2, -3, 3);
    Viewport<int> v3(-2, -1, -3, -1);
    
    REQUIRE(v1.height() == 4);
    REQUIRE(v2.height() == 6);
    REQUIRE(v3.height() == 2);
    REQUIRE(v1.width() == 2);
    REQUIRE(v2.width() == 4);
    REQUIRE(v3.width() == 1);
    REQUIRE(v1.size() == 8);
    REQUIRE(v2.size() == 24);
    REQUIRE(v3.size() == 2);
}

TEST_CASE("Viewports linear projection works", "[viewports]") {
  Viewport<int> screen1(-2,2,-2,2);
  Viewport<double> space1(-2.0, 2.0, -2.0, 2.0);
  std::complex<double> c0(0, 0);

  REQUIRE(linear_projection(0, 0, screen1, space1, c0) == std::complex<double>(-2, -2));
  REQUIRE(linear_projection(4, 4, screen1, space1, c0) == std::complex<double>(2, 2));
}
