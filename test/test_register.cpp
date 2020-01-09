#include "catch.hpp"
#include "register.h"

TEST_CASE("scanItem increases the quantity of the item in register object", "[register]") {
	Register testRegister;
	testRegister.scanItem("coffee");

	REQUIRE(testRegister.getQuantity("coffee") == 1);
}
