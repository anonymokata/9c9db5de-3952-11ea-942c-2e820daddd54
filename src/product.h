#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using std::string;

class Product {
private:
	string name;
	int price;
public:
	Product();
	Product(string, int);
	string getName() { return name; }
	void setName(string n) { name = n; }
	int getPrice() { return price; }
	void setPrice(int p) { price = p; }
};

#endif
