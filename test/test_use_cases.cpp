#include "catch.hpp"
#include "inventory.h"
#include "product.h"
#include "register.h"

#include <memory>

using std::make_shared;
using std::shared_ptr;

TEST_CASE("after configuring an inventory with products, a register repeatedly accepts scanned items and keeps an accurate running total", "[inventory][product][register]") {
	shared_ptr<Inventory> testInventoryPtr = make_shared<Inventory>();
	testInventoryPtr->insert(make_shared<Product>("tea", 299));
	testInventoryPtr->insert(make_shared<Product>("chips", 185));
	Register testRegister;
	testRegister.assignInventory(testInventoryPtr);

	REQUIRE(testRegister.getTotal() == 0);

	testRegister.scanItem("tea");

	REQUIRE(testRegister.getTotal() == 299);

	testRegister.scanItem("chips");

	REQUIRE(testRegister.getTotal() == 299 + 185);
}
