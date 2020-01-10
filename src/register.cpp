#include "register.h"

void Register::assignInventory(shared_ptr<Inventory> i) {
	productList = i;
}

bool Register::scanItem(string s) {
	if (!this->productList) {
		return false;
	}
	if (this->productList->contains(s)) {
		++quantity[s];
		shared_ptr<Product> prodPtr = productList->retrieve(s);
		incTotal(prodPtr->getPrice());
		return true;
	}
	return false;
}

void Register::incTotal(int p) {
	total += p;
}
