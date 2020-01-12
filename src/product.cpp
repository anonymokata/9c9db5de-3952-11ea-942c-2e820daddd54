#include "product.h"

Product::Product(string n, int p) {
	name = n;
	price = p;
}

Product::Product(string n, int p, bool w) {
	name = n;
	price = p;
	byWeight = w;
}

bool Product::setMarkdown(int m) {
	markdown = m;
	return true;
}
