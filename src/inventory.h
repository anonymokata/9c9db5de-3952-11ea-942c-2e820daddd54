#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "product.h"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class Inventory {
public:
	unordered_map<string, Product*> productList;
	bool contains(string);
	void insert(Product*);
};

#endif
