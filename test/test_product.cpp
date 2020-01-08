#include "catch.hpp"
#include "product.h"

TEST_CASE("getNameReturnsNameOfProduct", "[product]") {
	Product testProduct;
	testProduct.name = "soup";
	REQUIRE(testProduct.getName() == "soup");
}
