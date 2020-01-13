#ifndef _SPECIAL_H_
#define _SPECIAL_H_

class Special {
protected:
	int purchaseQuantity;
public:
	inline int getPurchaseQuantity() const { return purchaseQuantity; }
	inline void setPurchaseQuantity(int p) { purchaseQuantity = p; }
	virtual inline int getDiscountQuantity() const { return 0; }
	virtual inline void setDiscountQuantity(int) { }
	virtual inline int getDiscountPercentage() const { return 0; }
	virtual inline bool setDiscountPercentage(int) { return false; }
};

class SpecialBogo : public Special {
private:
	int discountQuantity = 0;
	int discountPercentage = 0; //represents percent off, from 0 to 100
public:
	SpecialBogo() {};
	SpecialBogo(int, int, int);
	inline int getDiscountQuantity() const override { return discountQuantity; }
	inline void setDiscountQuantity(int d) override { discountQuantity = d; }
	inline int getDiscountPercentage() const override { return discountPercentage; }
	bool setDiscountPercentage(int) override;
};

/*class SpecialBulk {
private:
	int discountPrice = 0;
public:
	SpecialBulk(int, int);
	inline int getDiscountPrice() const { return discountPrice; }
	inline void setDiscountPrice(int d) { discountPrice = d; }
};*/

#endif
