#include "catch.hpp"
#include "inventory.h"
#include "product.h"
#include "register.h"

#include <memory>

using std::make_shared;
using std::shared_ptr;

TEST_CASE("assignInventory assigns an inventory object to the register", "[register]") {
	Register testRegister;
	shared_ptr<Inventory> testInventoryPointer = std::make_shared<Inventory>();

	REQUIRE(!testRegister.getInventory());

	testRegister.assignInventory(testInventoryPointer);

	REQUIRE(testRegister.getInventory());
}

TEST_CASE("scanItem returns false if no inventory object is currently set", "[register]") {
	Register testRegister;

	REQUIRE(testRegister.scanItem("corn") == false);
}

TEST_CASE("scanItem returns true if inventory object is set and product is found in inventory", "[register]") {
	Register testRegister;
	shared_ptr<Inventory> testInventoryPointer = make_shared<Inventory>();
	testInventoryPointer->insert(make_shared<Product>("beef", 799));
	testRegister.assignInventory(testInventoryPointer);

	REQUIRE(testRegister.scanItem("beef") == true);
}

/*TEST_CASE("scanItem increases the quantity of the product in register object if product is found in register's inventory", "[register]") {
	Register testRegister;
	Inventory testInventory;
	testInventory.insert(shared_ptr<Product>("coffee", 719));
	testRegister.assignInventory(testInventory&);
	testRegister.scanItem("coffee");

	REQUIRE(testRegister.getQuantity("coffee") == 1);
}*/
