#include "catch.hpp"
#include "product.h"
#include "special.h"

#include <memory>

using std::make_shared;
using std::shared_ptr;

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
	SECTION("setMarkdown sets the markdown member and returns true on success") {
		bool res = testProduct.setMarkdown(89);

		REQUIRE(res == true);
		REQUIRE(testProduct.getMarkdown() == 89);
	}
	SECTION("setMarkdown returns false and does not set the markdown member if passed value is greater than or equal to current price") {
		bool res = testProduct.setMarkdown(700);

		REQUIRE(res == false);
		REQUIRE(testProduct.getMarkdown() == 0);
	}
	SECTION("getSpecial returns nullptr if no special is currently set") {
		REQUIRE(testProduct.getSpecial() == nullptr);
	}
	SECTION("assignSpecial assigns a special object to special member") {
		shared_ptr<Special> specialPtr = make_shared<Special>(1, 1, 50);
		testProduct.assignSpecial(specialPtr);

		REQUIRE(testProduct.getSpecial() != nullptr);
	}
}
