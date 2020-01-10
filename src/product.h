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
	~Product();
	inline string getName() const { return name; }
	inline void setName(const string& n) { name = n; }
	inline int getPrice() const { return price; }
	inline void setPrice(int p) { price = p; }
};

#endif
