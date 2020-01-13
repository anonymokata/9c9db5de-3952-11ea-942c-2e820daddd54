#ifndef _SPECIAL_H_
#define _SPECIAL_H

#include <string>

using std::string;

class Special {
protected:
	string type;
	int purchaseQuantity;
	int limit;
public:
	inline string getSpecialType() const { return type; }
	inline int getPurchaseQuantity() const { return purchaseQuantity; }
	inline void setPurchaseQuantity(int p) { purchaseQuantity = p; }
	inline int getLimit() const { return limit; }
	inline void setLimit(int l) { limit = l; }
	virtual inline int getDiscountQuantity() const { return 0; }
	virtual inline void setDiscountQuantity(int) { }
	virtual inline int getDiscountPercentage() const { return 0; }
	virtual inline bool setDiscountPercentage(int) { return false; }
	virtual inline int getDiscountPrice() const { return 0; }
	virtual inline void setDiscountPrice(int) { }
};

class SpecialBogo : public Special {
private:
	int discountQuantity = 0;
	int discountPercentage = 0; //represents percent off, from 0 to 100
public:
	SpecialBogo(int, int, int, int = 0);
	inline int getDiscountQuantity() const override { return discountQuantity; }
	inline void setDiscountQuantity(int d) override { discountQuantity = d; }
	inline int getDiscountPercentage() const override { return discountPercentage; }
	bool setDiscountPercentage(int) override;
};

class SpecialBulk : public Special {
private:
	int discountPrice = 0;
public:
	SpecialBulk(int, int, int = 0);
	inline int getDiscountPrice() const override { return discountPrice; }
	inline void setDiscountPrice(int d) override { discountPrice = d; }
};

#endif
