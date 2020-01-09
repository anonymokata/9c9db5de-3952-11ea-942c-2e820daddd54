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
	testProduct.setPrice(824);
	REQUIRE(testProduct.getPrice() == 824);
}

TEST_CASE("setPriceSetsPriceOfProductInCents", "[product]") {
	Product testProduct;
	testProduct.setPrice(421);
	REQUIRE(testProduct.getPrice() == 421);
}

TEST_CASE("productParameterizedConstructorSetsMembers", "[product]") {
	Product testProduct("milk", 512);
	REQUIRE(testProduct.getName() == "milk");
	REQUIRE(testProduct.getPrice() == 512);
}
