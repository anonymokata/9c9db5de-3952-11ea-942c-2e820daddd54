#ifndef _SPECIAL_H_
#define _SPECIAL_H_

class Special {
private:
	int purchaseQuantity = 0;
	int discountQuantity = 0;
public:
	inline int getPurchaseQuantity() { return purchaseQuantity; }
	inline void setPurchaseQuantity(int p) { purchaseQuantity = p; }
	inline int getDiscountQuantity() { return discountQuantity; }
	inline void setDiscountQuantity(int d) { discountQuantity = d; }
};

#endif
