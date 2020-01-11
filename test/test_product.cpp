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
	SECTION("product constructor takes an optional third boolean parameter byWeight") {
		Product testProduct2("80 lean ground beef", 599, true);
		
		REQUIRE(testProduct2.getByWeight() == true);
	}
	SECTION("setByWeight sets the byWeight member") {
		Product testProduct2("banana", 299);

		REQUIRE(testProduct2.getByWeight() == false);

		testProduct2.setByWeight(true);

		REQUIRE(testProduct2.getByWeight() == true);

		testProduct2.setByWeight(false);

		REQUIRE(testProduct2.getByWeight() == false);
	}
}
