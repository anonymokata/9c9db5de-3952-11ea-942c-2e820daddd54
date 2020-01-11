#include "register.h"

void Register::assignInventory(shared_ptr<Inventory> i) {
	productList = i;
}

/*bool Register::scanItem(string s) {
	if (!this->productList) {
		return false;
	}
	if (this->productList->contains(s)) {
		++quantity[s];
		shared_ptr<Product> prodPtr = productList->retrieve(s);
		incTotal(prodPtr->getPrice());
		return true;
	}
	return false;
}*/

bool Register::scanItem(string s, int w) {
	if (!this->productList) {
		return false;
	}
	if (this->productList->contains(s)) {
		incQuantity(s, w);
		shared_ptr<Product> prodPtr = productList->retrieve(s);
		incTotal(calcPrice(prodPtr->getPrice(), w));
		return true;
	}
	return false;
}

int Register::calcPrice(int p, int w) {
	if (w != 0) { //multiply price per pound by quantity in
		//hundredths of a pound
		double lbScanned = w / 100.0;
		double cost = lbScanned * p;
		cost += .5; //for rounding
		p = (int) cost;
	}
	return p;
}

void Register::incTotal(int p) {
	total += p;
}

void Register::incQuantity(string n, int w) {
	if (w == 0) {
		++quantity[n];
	}
	else {
		quantity[n] += w;
	}
}
