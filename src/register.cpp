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
	int dec = 1;
	if (w != 0) { //amount to decrement from the current quantity to account for weight priced specials
		dec = w;
	}
	decTotal(calcPrice(price, w, curQuantity - dec, special));
	//subtract the amount of product being removed from curQuantity to calculate if the unit being removed was priced at discount
	decQuantity(n, w);
	return true;
}

int Register::calcPrice(int p, int w, int q, shared_ptr<Special> s) {
	if (w && s) { //special for weighted item
		//450 -> 250 --- rem 150 full, 50 disc
		int purchaseQuantity = s->getPurchaseQuantity(); //200
		int discountQuantity = s->getDiscountQuantity(); //100
		int discountPercentage = s->getDiscountPercentage(); //50
		int totalSpecialQuantity = purchaseQuantity + discountQuantity;
		int discountPrice = (int) (p * ((100 - discountPercentage) / 100.0) + .5); //cents per lb
		int price = 0;
		int fullCycles = w / totalSpecialQuantity; //0
		w = w % totalSpecialQuantity; //200
		price += ((int) ((fullCycles * discountPrice * discountQuantity / 100.0) + (fullCycles * p * purchaseQuantity / 100.0) + .5));
		int margin = q % totalSpecialQuantity; //250 amount of product towards next cycle previously scanned
		if (margin / purchaseQuantity) { //already in discount price
			int discPriceQuantity = totalSpecialQuantity - margin;
			discPriceQuantity = discPriceQuantity < w ? discPriceQuantity : w;
			price += ((int) (discountPrice * (discPriceQuantity / 100.0) + .5));
			w -= discPriceQuantity;
			price += ((int) (p * (w / 100.0) + .5)); //dump rest into full price
		}
		else { //have some way to go in full price
			int fullPriceQuantity = purchaseQuantity - margin;
			fullPriceQuantity = fullPriceQuantity < w ? fullPriceQuantity : w; //check if enough weight to cover fPQ
			w -= fullPriceQuantity;
			price += ((int) (p * (fullPriceQuantity / 100.0) + .5));
			price += ((int) (discountPrice * (w / 100.0) + .5)); //dump rest into disc price
		}
		//add rest as discount price
		//price += ((int) (discountPrice * (w / 100.0) + .5));
		/*if (w > margin) {
			price += ((int) ((w - margin) / 100.0 + .5) * discountPrice);
			w = margin;
		}
		price += ((int) (w / 100.0 + .5)) * p;*/
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
