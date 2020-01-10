#include "register.h"

void Register::assignInventory(shared_ptr<Inventory> i) {
	productList = i;
}

bool Register::scanItem(string s) {
	if (!this->productList) {
		return false;
	}
	if (this->productList->contains(s)) {
		return true;

	}
	return false;
}
