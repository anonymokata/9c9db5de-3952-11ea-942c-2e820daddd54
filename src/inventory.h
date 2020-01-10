#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "product.h"

#include <memory>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::string;
using std::unordered_map;

class Inventory {
private:
	unordered_map<string, shared_ptr<Product>> productList;
public:
	bool contains(string);
	bool insert(shared_ptr<Product>);
	shared_ptr<Product> retrieve(string);
};

#endif
