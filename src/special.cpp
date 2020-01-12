#include "special.h"

bool Special::setDiscountPercentage(int d) {
	if (d > 100 || d < 0) {
		return false;
	}
	discountPercentage = d;

	return true;
}
