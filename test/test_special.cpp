#include "catch.hpp"
#include "special.h"

TEST_CASE("SpecialBogo is a type of Special which contains members which denote the details of a special applied to a product in the form of buy N items, get M at X off") {
	SpecialBogo testSpecial;
	
	SECTION("setPurchaseQuantity sets the amount of products required to be purchased at full price") {
		testSpecial.setPurchaseQuantity(3);

		REQUIRE(testSpecial.getPurchaseQuantity() == 3);
	}
	SECTION("setDiscountQuantity sets the amount of products able to be purchased at discount after purchasing the amount equal to purchaseQuantity") {
		testSpecial.setDiscountQuantity(2);

		REQUIRE(testSpecial.getDiscountQuantity() == 2);
	}
	SECTION("setDiscountPercentage sets the percent (as a 0-precision int) off the marked price that discounted items are purchased at") {
		testSpecial.setDiscountPercentage(50);
		
		REQUIRE(testSpecial.getDiscountPercentage() == 50);
	}
	SECTION("setDiscountPercentage checks the input for bounds of 0 and 100 inclusive and returns false without setting member if input is out of bounds") {
		bool res = testSpecial.setDiscountPercentage(777);

		REQUIRE(res == false);
		REQUIRE(testSpecial.getDiscountPercentage() == 0);

		res = testSpecial.setDiscountPercentage(-25);

		REQUIRE(res == false);
		REQUIRE(testSpecial.getDiscountPercentage() == 0);
	}
	SECTION("parameterized constructor for special takes purchaseQuantity, discountQuantity, and discountPercentage") {
		SpecialBogo testSpecial2(5, 1, 100);

		REQUIRE(testSpecial2.getPurchaseQuantity() == 5);
		REQUIRE(testSpecial2.getDiscountQuantity() == 1);
		REQUIRE(testSpecial2.getDiscountPercentage() == 100);
		}
}

TEST_CASE("SpecialBulk is a type of Special which contains members which denote the details of a special applied to a product in the form of buy N items for X") {
	SpecialBulk testSpecial;

	SECTION("setPurchaseQuantity sets the number of products required to be bought for the special rate to apply") {
		testSpecial.setPurchaseQuantity(7);

		REQUIRE(testSpecial.getPurchaseQuantity() == 7);
	}
}
