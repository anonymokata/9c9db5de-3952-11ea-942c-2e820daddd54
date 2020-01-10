#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "product.h"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class Inventory {
private:
	unordered_map<string, Product*> productList;
public:
	bool contains(string);
	bool insert(Product*);
};

#endif
