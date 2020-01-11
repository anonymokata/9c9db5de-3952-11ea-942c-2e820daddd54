#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using std::string;

class Product {
private:
	string name;
	int price;
	bool byWeight = false;
public:
	Product(string, int);
	Product(string, int, bool);
	inline string getName() const { return name; }
	inline void setName(const string& n) { name = n; }
	inline int getPrice() const { return price; }
	inline void setPrice(int p) { price = p; }
	inline bool getByWeight() const { return byWeight; }
	inline void setByWeight() { }
};

#endif
