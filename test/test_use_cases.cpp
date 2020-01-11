#include "catch.hpp"
#include "inventory.h"
#include "product.h"
#include "register.h"

#include <memory>

using std::make_shared;
using std::shared_ptr;

TEST_CASE("after configuring an inventory with products, a register repeatedly allows scanning items, removing items, and keeps an accurate running total", "[inventory][product][register]") {
	shared_ptr<Inventory> testInventoryPtr = make_shared<Inventory>();
	testInventoryPtr->insert(make_shared<Product>("tea", 299));
	testInventoryPtr->insert(make_shared<Product>("chips", 185));
	Register testRegister;
	testRegister.assignInventory(testInventoryPtr);
	
	SECTION("register total and quantities initialize as 0") {
		REQUIRE(testRegister.getTotal() == 0);
		REQUIRE(testRegister.getQuantity("tea") == 0);
		REQUIRE(testRegister.getQuantity("chips") == 0);
	}

	testRegister.scanItem("tea");

	SECTION("scanning an item increases the total and quantity") {
		REQUIRE(testRegister.getTotal() == 299);
		REQUIRE(testRegister.getQuantity("tea") == 1);
	}

	testRegister.scanItem("chips");
	
	SECTION("repeated scanning keeps a running total and quantity of each item") {
		REQUIRE(testRegister.getTotal() == 299 + 185);
		REQUIRE(testRegister.getQuantity("chips") == 1);
	}

	testRegister.removeItem("tea");

	SECTION("removing an item not priced by weight reduces the total by one unit and quantity by one") {
		REQUIRE(testRegister.getTotal() == 185);
		REQUIRE(testRegister.getQuantity("tea") == 0);
	}

	testRegister.removeItem("tea");
	
	SECTION("removing an item which has a current quantity of 0 does not affect the total or quantity") {
		REQUIRE(testRegister.getTotal() == 185);
		REQUIRE(testRegister.getQuantity("tea") == 0);

	}
}
