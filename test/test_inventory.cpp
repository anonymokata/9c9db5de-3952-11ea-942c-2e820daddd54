#include "catch.hpp"
#include "inventory.h"
#include "product.h"

TEST_CASE("contains returns true when passed a product name in the inventory container", "[inventory]") {
	Inventory testInventory;
	testInventory.productList["rice"] = new Product("rice", 289);

	REQUIRE(testInventory.contains("rice") == true);
}

TEST_CASE("contains returns false when passed a product name not in the inventory container", "[inventory]") {
	Inventory testInventory;
	
	REQUIRE(testInventory.contains("coke") == false);
}

/*TEST_CASE("insert inserts a reference to a product object inside the inventory object for access", "[inventory]") {
	Inventory testInventory;
	testInventory.insert(Product("rice", 289));

	REQUIRE(testInventory.contains("rice") == true);
}*/
