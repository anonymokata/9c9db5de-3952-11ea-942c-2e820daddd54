#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using std::string;

class Product {
private:
	string name;
public:
	int price;
	string getName() { return name; }
	void setName(string n) { name = n; }
	int getPrice() { return price; }
};

#endif
