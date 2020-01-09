#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using std::string;

class Product {
private:
	string name;
public:
	string getName() { return name; }
	void setName(string n) { name = n; }
};

#endif
