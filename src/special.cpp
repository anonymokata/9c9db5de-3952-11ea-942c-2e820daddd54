#include "special.h"

SpecialBogo::SpecialBogo(int pq, int dq, int dp, int l) {
	type = "BOGO";
	purchaseQuantity = pq;
	discountQuantity = dq;
	discountPercentage = dp;
	limit = l;
}

bool SpecialBogo::setDiscountPercentage(int d) {
	if (d > 100 || d < 0) {
		return false;
	}
	discountPercentage = d;

	return true;
}

SpecialBulk::SpecialBulk(int pq, int dp, int l) {
	type = "BULK";
	purchaseQuantity = pq;
	discountPrice = dp;
	limit = l;
}
