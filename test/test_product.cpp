#include "catch.hpp"
#include "product.h"

TEST_CASE("product member variables can be accessed and assigned", "[product]") {
	Product testProduct("cereal", 499);

	REQUIRE(testProduct.getName() == "cereal");
	REQUIRE(testProduct.getPrice() == 499);

	SECTION("setName sets the name of a product") {
		testProduct.setName("oatmeal");

		REQUIRE(testProduct.getName() == "oatmeal");
	}
	SECTION("setPrice sets the price of a product") {
		testProduct.setPrice(399);

		REQUIRE(testProduct.getPrice() == 399);
	}
}
