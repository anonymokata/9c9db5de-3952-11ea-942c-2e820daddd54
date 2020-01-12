#include "catch.hpp"
#include "special.h"

TEST_CASE("Special contains members which denote the details of a special applied to a product") {
	Special testSpecial;
	
	SECTION("setPurchaseQuantity sets the amount of products required to be purchased at full price") {
		testSpecial.setPurchaseQuantity(3);

		REQUIRE(testSpecial.getPurchaseQuantity() == 3);
	}
}
