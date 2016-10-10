#include <Catch/Catch.hpp>
#include <Game/Test.hpp>

TEST_CASE("Factorials are computed") {
  Test test;
  REQUIRE(test.getTwo() == 2);
}