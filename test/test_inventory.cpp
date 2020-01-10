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

TEST_CASE("insert returns a value of true when a product is sucessfully inserted") {
	Inventory testInventory;
	
	REQUIRE(testInventory.contains("apple") == false);

	bool res = testInventory.insert(new Product("apple", 299));

	REQUIRE(testInventory.contains("apple") == true);
	REQUIRE(res == true);
}
