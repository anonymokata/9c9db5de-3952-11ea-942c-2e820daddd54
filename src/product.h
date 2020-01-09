#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using std::string;

class Product {
private:
	string name;
	int price;
public:
	Product(string, int);
	inline string getName() { return name; }
	inline void setName(string n) { name = n; }
	inline int getPrice() { return price; }
	inline void setPrice(int p) { price = p; }
};

#endif
