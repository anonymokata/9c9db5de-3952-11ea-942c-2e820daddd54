#include "catch.hpp"
#include "inventory.h"
#include "product.h"
#include "register.h"

#include <memory>

using std::make_shared;
using std::shared_ptr;

TEST_CASE("assignInventory assigns an inventory object to the register", "[register]") {
	Register testRegister;
	shared_ptr<Inventory> testInventoryPointer = make_shared<Inventory>();

	REQUIRE(!testRegister.getInventory());

	testRegister.assignInventory(testInventoryPointer);

	REQUIRE(testRegister.getInventory());
}

TEST_CASE("scanItem is passed a product name, increases quantity of product and total cost if product is in register's set inventory, and returns a bool as an indicator of success/fail", "[register]") {
	Register testRegister;

	SECTION("scanItem returns false if no inventory object is currently set", "[register]") {
		REQUIRE(testRegister.scanItem("corn") == false);
	}

	shared_ptr<Inventory> testInventoryPointer = make_shared<Inventory>();
	testInventoryPointer->insert(make_shared<Product>("beef", 799));
	testRegister.assignInventory(testInventoryPointer);

	SECTION("scanItem returns true if inventory object is set and product is found in inventory", "[register]") {
		REQUIRE(testRegister.scanItem("beef") == true);
	}

	SECTION("scanItem returns false if inventory object is set and product is not found in inventory", "[register]") {
		REQUIRE(testRegister.scanItem("chips") == false);
	}

	SECTION("scanItem increases the quantity of the product in register's quantity object if product is found in register's inventory", "[register]") {
		testRegister.scanItem("beef");
		
		REQUIRE(testRegister.getQuantity("beef") == 1);
	}

	SECTION("scanItem increases the total of the register by the price of the scanned product", "[register]") {
		int curTotal = testRegister.getTotal();
		testRegister.scanItem("beef");

		REQUIRE(testRegister.getTotal() == curTotal + 799);
	}
}

TEST_CASE("scanItem accepts an additional second parameter indicating the weight of the product being scanned in", "[register]") {
	shared_ptr<Inventory> testInventoryPtr = make_shared<Inventory>();
	testInventoryPtr->insert(make_shared<Product>("ham", 376, true));
	testInventoryPtr->insert(make_shared<Product>("chocolate", 199));
	Register testRegister;
	testRegister.assignInventory(testInventoryPtr);
	testRegister.scanItem("ham", 110);
	
	SECTION("scanItem increases total for weighed items based on weight of product scanned") {
		REQUIRE(testRegister.getTotal() == (int) (376 * (110.0 / 100) +.5));
	}

	SECTION("scanItem increases quantity for weighed items based on weight of product scanned") {
		REQUIRE(testRegister.getQuantity("ham") == 110);
	}

	SECTION("scanItem returns false if weighed product is entered without weight") {
		bool res = testRegister.scanItem("ham");
		
		REQUIRE(res == false);
	}
}
