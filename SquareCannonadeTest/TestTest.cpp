#include "Catch.hpp"
#include <Game/Test.hpp>

TEST_CASE("Factorials are computed", "[factorial]") {
  Test test;
  REQUIRE(test.getTwo() == 2);
}

TEST_CASE("Swag", "[swag]") {
  REQUIRE("Bob" == "Bob");
  REQUIRE("Bob1" == "Bob2");
}