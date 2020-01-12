#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

class Special;

class Product {
private:
	string name;
	int price; //if byWeight true, represents price per pound
		//else, represents price per unit
	bool byWeight = false;
	int markdown = 0;
	shared_ptr<Special> special = nullptr;
public:
	Product(string, int);
	Product(string, int, bool);
	inline string getName() const { return name; }
	inline void setName(const string& n) { name = n; }
	inline int getPrice() const { return price; }
	inline void setPrice(int p) { price = p; }
	inline bool getByWeight() const { return byWeight; }
	inline void setByWeight(bool w) { byWeight = w; }
	inline int getMarkdown() const { return markdown; }
	bool setMarkdown(int);
	inline shared_ptr<Special> getSpecial() const { return special; }
};

#endif
