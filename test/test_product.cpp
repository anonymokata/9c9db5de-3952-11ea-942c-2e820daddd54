#include "catch.hpp"
#include "product.h"

TEST_CASE("getNameReturnsNameOfProduct", "[product]") {
	Product testProduct;
	testProduct.setName("soup");
	REQUIRE(testProduct.getName() == "soup");
}

TEST_CASE("setNameSetsNameOfProduct", "[product]") {
	Product testProduct;
	testProduct.setName("cereal");
	REQUIRE(testProduct.getName() == "cereal");
}
