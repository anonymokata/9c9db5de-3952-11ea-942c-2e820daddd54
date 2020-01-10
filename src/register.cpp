#include "register.h"

void Register::assignInventory(shared_ptr<Inventory> i) {
	productList = i;
}

void Register::scanItem(string s) {
	++quantity[s];
}
