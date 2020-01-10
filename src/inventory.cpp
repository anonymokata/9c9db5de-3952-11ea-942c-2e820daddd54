#include "inventory.h"

bool Inventory::contains(string n) {
	auto it = productList.find(n);
	if (it == productList.end()) {
		return false;
	}
	return true;
}
