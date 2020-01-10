#include "inventory.h"

bool Inventory::contains(string n) {
	auto it = productList.find(n);
	if (it == productList.end()) {
		return false;
	}
	return true;
}

bool Inventory::insert(shared_ptr<Product> p) {
	if (this->contains(p->getName())) {
		return false;
	}
	productList[p->getName()] = p;
	return true;
}
