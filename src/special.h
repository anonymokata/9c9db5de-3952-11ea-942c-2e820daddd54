#ifndef _SPECIAL_H_
#define _SPECIAL_H_

class Special {
private:
	int purchaseQuantity = 0;
	int discountQuantity = 0;
	int discountPercentage = 0; //represents percent off, from 0 to 100
public:
	inline int getPurchaseQuantity() const { return purchaseQuantity; }
	inline void setPurchaseQuantity(int p) { purchaseQuantity = p; }
	inline int getDiscountQuantity() const { return discountQuantity; }
	inline void setDiscountQuantity(int d) { discountQuantity = d; }
	inline int getDiscountPercentage() const { return discountPercentage; }
	bool setDiscountPercentage(int);
};

#endif
