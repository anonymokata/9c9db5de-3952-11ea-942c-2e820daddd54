#include "catch.hpp"
#include "inventory.h"
#include "product.h"
#include "register.h"

#include <memory>

using std::shared_ptr;

TEST_CASE("assignInventory assigns an inventory object to the register", "[register]") {
	Register testRegister;
	shared_ptr<Inventory> testInventoryPointer = std::make_shared<Inventory>();

	REQUIRE(!testRegister.getInventory());

	testRegister.assignInventory(testInventoryPointer);

	REQUIRE(testRegister.getInventory());
}

/*TEST_CASE("scanItem increases the quantity of the product in register object if product is found in register's inventory", "[register]") {
	Register testRegister;
	Inventory testInventory;
	testInventory.insert(shared_ptr<Product>("coffee", 719));
	testRegister.assignInventory(testInventory&);
	testRegister.scanItem("coffee");

	REQUIRE(testRegister.getQuantity("coffee") == 1);
}*/
