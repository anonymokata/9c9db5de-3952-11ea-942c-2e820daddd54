#ifndef _SPECIAL_H_
#define _SPECIAL_H_

class Special {
private:
	int purchaseQuantity = 0;
public:
	inline int getPurchaseQuantity() { return purchaseQuantity; }
	inline void setPurchaseQuantity(int p) { purchaseQuantity = p; }
};

#endif
