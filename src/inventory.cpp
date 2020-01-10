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

shared_ptr<Product> Inventory::retrieve(string n) {
	shared_ptr<Product> p = productList[n];
	return p;
}
