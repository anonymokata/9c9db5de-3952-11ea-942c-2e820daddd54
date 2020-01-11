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
	int total = 0; //total cost of scanned items in cents
	unordered_map<string, int> quantity; //stores quantity of scanned items
		//if product is priced by weight, stores hundredths of a pound
		//otherwise, stores number of units
	shared_ptr<Inventory> productList = nullptr;

	int calcPrice(int, int);
	void incTotal(int);
	void decTotal(int);
	void incQuantity(string, int = 0);
	void decQuantity(string, int = 0);
public:
	inline int getTotal() const { return total; }
	inline shared_ptr<Inventory> getInventory() { return productList; }
	void assignInventory(shared_ptr<Inventory>);
	inline int getQuantity(string s) { return quantity[s]; }
	bool scanItem(string, int = 0);
	bool removeItem(string, int = 0);
};

#endif
