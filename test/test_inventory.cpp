#include "catch.hpp"
#include "inventory.h"
#include "product.h"

#include <memory>

using std::shared_ptr;

TEST_CASE("contains returns a value based on the state of productList", "[inventory]") {
	Inventory testInventory;
	testInventory.insert(std::make_shared<Product>("rice", 298));

	SECTION("contains returns true when passed a product name in the inventory container") {
		REQUIRE(testInventory.contains("rice") == true);
	}

	SECTION("contains returns false when passed a product name not in the inventory container", "[inventory]") {	
		REQUIRE(testInventory.contains("coke") == false);
	}
}

TEST_CASE("insert adds a new product entry to the inventory product list if there is no current entry for the product", "[inventory]") {
	Inventory testInventory;
	bool res = testInventory.insert(std::make_shared<Product>("pasta", 499));
	
	SECTION("insert inserts a reference to a product object inside the inventory object for access", "[inventory]") {
		REQUIRE(testInventory.contains("pasta") == true);
	}

	SECTION("insert returns a value of true when a product is successfully inserted") {
		REQUIRE(res == true);
	}

	SECTION("insert returns a value of false when a product is attempted to be inserted but already has an entry with the same name", "[inventory]") {
		res = testInventory.insert(std::make_shared<Product>("pasta", 185));

		REQUIRE(res == false);
	}
}
