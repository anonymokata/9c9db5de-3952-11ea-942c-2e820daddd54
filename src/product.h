#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using std::string;

class Product {
public:
	string name;
	string getName() { return name; }
	void setName(string n) { name = n; }
};

#endif
