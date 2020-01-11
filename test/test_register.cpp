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

	SECTION("scanItem ignores weight parameter if scanned product is entered with weight and product's byWeight is false") {
		int quan = testRegister.getQuantity("chocolate");
		int tot = testRegister.getTotal();
		bool res = testRegister.scanItem("chocolate", 29);

		REQUIRE(testRegister.getQuantity("chocolate") == quan + 1);
		REQUIRE(testRegister.getTotal() == tot + 199);
		REQUIRE(res == true);
	}
}

TEST_CASE("removeItem removes a product from the register and reduces the total by the corresponding amount", "[register]") {
	shared_ptr<Inventory> testInventoryPtr = make_shared<Inventory>();
	testInventoryPtr->insert(make_shared<Product>("milk", 799));
	testInventoryPtr->insert(make_shared<Product>("watermelon", 50, true));
	Register testRegister;
	testRegister.assignInventory(testInventoryPtr);
	
	SECTION("removeItem returns false if passed product has quantity of 0") {
		bool res = testRegister.removeItem("milk");
	
		REQUIRE(res == false);
	}

	SECTION("removeItem returns true if passed product has a quantity above 0") {
		testRegister.scanItem("milk");
		bool res = testRegister.removeItem("milk");

		REQUIRE(res == true);
	}

	SECTION("removeItem reduces quantity of product by 1 if product has a quantity above 0") {
		testRegister.scanItem("milk");
		int milkQuantity = testRegister.getQuantity("milk");
		testRegister.removeItem("milk");

		REQUIRE(testRegister.getQuantity("milk") == milkQuantity - 1);
	}

	SECTION("removeItem reduces total by cost of 1 unit if product has a quantity above 0") {
		testRegister.scanItem("milk");
		int tot = testRegister.getTotal();
		testRegister.removeItem("milk");

		REQUIRE(testRegister.getTotal() == tot - 799);
	}

	SECTION("removeItem ignores passed weight if passed product is not priced by weight") {
		testRegister.scanItem("milk");
		int milkQuantity = testRegister.getQuantity("milk");
		int tot = testRegister.getTotal();
		bool res = testRegister.removeItem("milk", 65);

		REQUIRE(testRegister.getQuantity("milk") == milkQuantity - 1);
		REQUIRE(testRegister.getTotal() == tot - 799);
		REQUIRE(res == true);
	}

	SECTION("removeItem returns false if passed product is priced by weight and no weight is passed") {
		testRegister.scanItem("watermelon", 207);
		bool res = testRegister.removeItem("watermelon");

		REQUIRE(res == false);
	}

	SECTION("removeItem returns false if passed product is priced by weight and weight passed is greater than amount in productList") {
		testRegister.scanItem("watermelon", 513);
		int quant = testRegister.getQuantity("watermelon");
		bool res = testRegister.removeItem("watermelon", quant + 100);

		REQUIRE(res == false);
	}

	SECTION("removeItem decreases quantity of product by passed weight amount if product is priced by weight") {
		testRegister.scanItem("watermelon", 313);
		int quantity = testRegister.getQuantity("watermelon");
		testRegister.removeItem("watermelon", 107);

		REQUIRE(testRegister.getQuantity("watermelon") == quantity - 107);
	}

	SECTION("removeItem decreases total by adjusted price if passed product is priced by weight and a weight amount is passed") {
		testRegister.scanItem("watermelon", 509);
		int tot = testRegister.getTotal();
		testRegister.removeItem("watermelon", 216);

		REQUIRE(testRegister.getTotal() == tot - (int) (50 * (216 / 100.0) + .5));
	}		
}
