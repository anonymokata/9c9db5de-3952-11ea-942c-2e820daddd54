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
	unordered_map<string, int> quantity;
	shared_ptr<Inventory> productList = nullptr;
public:
	inline shared_ptr<Inventory> getInventory() { return productList; }
	void assignInventory(shared_ptr<Inventory>);
	inline int getQuantity(string s) { return quantity[s]; }
	bool scanItem(string);

};

#endif
