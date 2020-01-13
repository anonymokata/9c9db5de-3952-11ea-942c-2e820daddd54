#include "special.h"

SpecialBogo::SpecialBogo(int pq, int dq, int dp) {
	purchaseQuantity = pq;
	discountQuantity = dq;
	discountPercentage = dp;
}

bool SpecialBogo::setDiscountPercentage(int d) {
	if (d > 100 || d < 0) {
		return false;
	}
	discountPercentage = d;

	return true;
}

/*SpecialBulk::SpecialBulk(int pq, int dp) {
	purchaseQuantity = pq;
	discountPrice = dp;
}*/
