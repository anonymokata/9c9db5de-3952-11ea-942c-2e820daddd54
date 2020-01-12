#include "special.h"

Special::Special(int p, int dq, int dp) {
	purchaseQuantity = p;
	discountQuantity = dq;
	discountPercentage = dp;
}

bool Special::setDiscountPercentage(int d) {
	if (d > 100 || d < 0) {
		return false;
	}
	discountPercentage = d;

	return true;
}
