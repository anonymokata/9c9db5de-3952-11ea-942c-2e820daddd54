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
	testInventoryPtr->insert(make_shared<Product>("chicken", 499, true));
	shared_ptr<Product> testPtr = make_shared<Product>("sugar", 895);
	testPtr->setMarkdown(125); //sugar markdown
	testInventoryPtr->insert(testPtr);
	testPtr = make_shared<Product>("sweet pepper", 499, true);
	testPtr->setMarkdown(99); //sweet pepper markdown
	testInventoryPtr->insert(testPtr);
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
		
	testRegister.scanItem("chicken", 147);
	
	SECTION("scanning an item priced by weight increases quantity and total by amount of product scanned") {
		REQUIRE(testRegister.getTotal() == 185 + (int) ((147/100.0) * 499 + .5));
		REQUIRE(testRegister.getQuantity("chicken") == 147);
	}

	int total = testRegister.getTotal();
	int chickenQuantity = testRegister.getQuantity("chicken");
	testRegister.removeItem("chicken", 32);

	SECTION("removing an item priced by weight reduces quantity by amount passed to removeItem and total by price of removed amount") {
		REQUIRE(testRegister.getTotal() == total - (int) ((32/100.0) * 499 + .5));
		REQUIRE(testRegister.getQuantity("chicken") == chickenQuantity - 32);
	}

	total = testRegister.getTotal();
	chickenQuantity = testRegister.getQuantity("chicken");
	testRegister.removeItem("chicken", 600);

	SECTION("attempting to remove more of a weight priced item than currently in quantity results in no change to total or quantity") {
		REQUIRE(testRegister.getTotal() == total);
		REQUIRE(testRegister.getQuantity("chicken") == chickenQuantity);
	}

	total = testRegister.getTotal();
	testRegister.scanItem("sugar");

	SECTION("scanning an item with a markdown increases the total by the price less the markdown") {
		REQUIRE(testRegister.getTotal() == total + 895 - 125);
	}
}
