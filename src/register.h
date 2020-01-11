#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "inventory.h"

#include <memory>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::string;
using std::unordered_map;

class Register {
private:
	int total = 0;
	unordered_map<string, int> quantity;
	shared_ptr<Inventory> productList = nullptr;

	void incTotal(int);
public:
	inline int getTotal() const { return total; }
	inline shared_ptr<Inventory> getInventory() { return productList; }
	void assignInventory(shared_ptr<Inventory>);
	inline int getQuantity(string s) { return quantity[s]; }
	bool scanItem(string);
};

#endif
