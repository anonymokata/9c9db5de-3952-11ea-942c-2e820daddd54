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

TEST_CASE("getPriceReturnsPriceOfProductInCents", "[product]") {
	Product testProduct;
	testProduct.price = 824;
	REQUIRE(testProduct.getPrice() == 824);
}

TEST_CASE("setPriceSetsPriceOfProductInCents", "[product]") {
	Product testProduct;
	testProduct.setPrice(421);
	REQUIRE(testProduct.getPrice() == 421);
}
