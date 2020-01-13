#include "register.h"

void Register::assignInventory(shared_ptr<Inventory> i) {
	productList = i;
}

bool Register::scanItem(string s, int w) {
	if (!this->productList) {
		return false;
	}
	if (this->productList->contains(s)) {
		shared_ptr<Product> prodPtr = productList->retrieve(s);
		if (prodPtr->getByWeight() && w == 0) {
			//weighted object scanned without weight
			return false;
		}
		if (prodPtr->getByWeight() == false) {
			//ignore weight if product not priced by weight
			w = 0;
		}
		int price = prodPtr->getPrice() - prodPtr->getMarkdown();
		int curQuantity = getQuantity(s);
		shared_ptr<Special> special = prodPtr->getSpecial();
		incTotal(calcPrice(price, w, curQuantity, special));
		incQuantity(s, w);
		return true;
	}
	return false;
}

bool Register::removeItem(string n, int w) {
	shared_ptr<Product> prodPtr = productList->retrieve(n);
	if (prodPtr->getByWeight() && w > getQuantity(n)) {
		//trying to remove more pounds than currently have
		return false;
	}
	else if (getQuantity(n) == 0) {
		//trying to remove product not currently scanned
		return false;
	}
	if (prodPtr->getByWeight() && w == 0) {
		//trying to remove weighted item without passing weight
		return false;
	}
	if (prodPtr->getByWeight() == false) {
		w = 0;
	}
	int price = prodPtr->getPrice() - prodPtr->getMarkdown();
	int curQuantity = getQuantity(n);
	shared_ptr<Special> special = prodPtr->getSpecial();
	decTotal(calcPrice(price, w, curQuantity - 1, special));
	//subtract one from curQuantity to calculate if the unit being removed
	//was priced at discount
	decQuantity(n, w);
	return true;
}

int Register::calcPrice(int p, int w, int q, shared_ptr<Special> s) {
	if (w && s) { //special for weighted item
		//identify total after scanning
		//calculate how many complete specials there are
		//add remainder as full price
		int purchaseQuantity = s->getPurchaseQuantity(); //200
		int discountQuantity = s->getDiscountQuantity(); //100
		int discountPercentage = s->getDiscountPercentage(); //50
		int totalSpecialQuantity = purchaseQuantity + discountQuantity; //300
		int discountPrice = (int) (p * ((100 - discountPercentage) / 100.0) + .5); //cents per lb
		int price = 0;
		int fullCycles = w / totalSpecialQuantity; //1
		w = w % totalSpecialQuantity; //0
		price += ((int) ((fullCycles * discountPrice * discountQuantity / 100.0) + (fullCycles * p * purchaseQuantity / 100.0) + .5));
		int margin = q % totalSpecialQuantity;
		if (w > margin) {
			price += ((int) ((w - margin) / 100.0 + .5) * discountPrice);
			w = margin;
		}
		price += ((int) (w / 100.0 + .5)) * p;
		p = price;
	}
	else if (s && (q < s->getLimit() || s->getLimit() == 0) && s->getSpecialType() == "BOGO") {
		int purchaseQuantity = s->getPurchaseQuantity();
		int discountQuantity = s->getDiscountQuantity();
		int discountPercentage = s->getDiscountPercentage();
		int totalSpecialQuantity = purchaseQuantity + discountQuantity;
		if (q % totalSpecialQuantity >= purchaseQuantity) {
			double discountPrice = 100 - discountPercentage;
			discountPrice /= 100.0;
			discountPrice *= p;
			discountPrice += .5; //for rounding
			p = (int) discountPrice;
		}
	}
	else if (s && (q < s->getLimit() || s->getLimit() == 0) && s->getSpecialType() == "BULK") {
		int purchaseQuantity = s->getPurchaseQuantity();
		int discountPrice = s->getDiscountPrice();
		if (q % purchaseQuantity == purchaseQuantity - 1) {
			p = discountPrice - (p * (purchaseQuantity - 1));
		}
	}
	else if (w != 0) { //multiply price per pound by quantity in
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

void Register::decTotal(int p) {
	total -= p;
}

void Register::incQuantity(string n, int w) {
	if (w == 0) {
		++quantity[n];
	}
	else {
		quantity[n] += w;
	}
}

void Register::decQuantity(string n, int w) {
	if (w == 0) {
		--quantity[n];
	}
	else {
		quantity[n] -= w;
	}
}
