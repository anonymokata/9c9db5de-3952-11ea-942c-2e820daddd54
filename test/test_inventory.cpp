#include "catch.hpp"
#include "inventory.h"
#include "product.h"

TEST_CASE("contains returns a value based on the state of productList", "[inventory]") {
	Inventory testInventory;
	testInventory.productList["rice"] = new Product("rice", 289);

	SECTION("contains returns true when passed a product name in the inventory container") {

		REQUIRE(testInventory.contains("rice") == true);
	}

	SECTION("contains returns false when passed a product name not in the inventory container", "[inventory]") {
	
		REQUIRE(testInventory.contains("coke") == false);
	}
}

TEST_CASE("insert inserts a reference to a product object inside the inventory object for access", "[inventory]") {
	Inventory testInventory;
	testInventory.insert(new Product("pasta", 499));

	REQUIRE(testInventory.contains("pasta") == true);
}
