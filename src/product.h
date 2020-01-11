#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>

using std::string;

class Product {
private:
	string name;
	int price; //if byWeight true, represents price per pound
		//else, represents price per unit
	bool byWeight = false;
public:
	Product(string, int);
	Product(string, int, bool);
	inline string getName() const { return name; }
	inline void setName(const string& n) { name = n; }
	inline int getPrice() const { return price; }
	inline void setPrice(int p) { price = p; }
	inline bool getByWeight() const { return byWeight; }
	inline void setByWeight(bool w) { byWeight = w; }
};

#endif
