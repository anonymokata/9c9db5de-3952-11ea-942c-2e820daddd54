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
	int total = 0;
	int overLimit = 0; //used for weight priced specials
	if (w && s && s->getLimit() != 0) {
		overLimit = w + q - s->getLimit();
		overLimit = overLimit > 0 ? overLimit : 0;
		w -= overLimit;
	}
	if (w && s) { //special for weighted item
		int purchaseQuantity = s->getPurchaseQuantity();
		int discountQuantity = s->getDiscountQuantity();
		int discountPercentage = s->getDiscountPercentage();
		int totalSpecialQuantity = purchaseQuantity + discountQuantity;
		int discountPrice = (int) (p * ((100 - discountPercentage) / 100.0) + .5); //cents per lb
		int price = 0;
		int fullCycles = w / totalSpecialQuantity; //amount of sets of max full price and discount price quantities
		w = w % totalSpecialQuantity; //amount left over after taking out full sets
		price += ((int) ((fullCycles * discountPrice * discountQuantity / 100.0) + (fullCycles * p * purchaseQuantity / 100.0) + .5)); //adding the total of max full and discount price quantities
		int margin = q % totalSpecialQuantity; //amount of product towards next cycle previously scanned
		if (margin / purchaseQuantity) { //already in discount price
			int discPriceQuantity = totalSpecialQuantity - margin; //calculate how much quantity to add until out of discount price range and add
			discPriceQuantity = discPriceQuantity < w ? discPriceQuantity : w; //check if enough weight to cover dpq range
			price += ((int) (discountPrice * (discPriceQuantity / 100.0) + .5));
			w -= discPriceQuantity;
			price += ((int) (p * (w / 100.0) + .5)); //dump rest into full price
		}
		else { //have some way to go in full price
			int fullPriceQuantity = purchaseQuantity - margin; //calculate how much quantity to add in full price range and add
			fullPriceQuantity = fullPriceQuantity < w ? fullPriceQuantity : w; //check if enough weight to cover fPQ
			w -= fullPriceQuantity;
			price += ((int) (p * (fullPriceQuantity / 100.0) + .5));
			price += ((int) (discountPrice * (w / 100.0) + .5)); //dump rest into disc price
		}
		w = overLimit;
		total = price;
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
	if (w != 0) { //multiply price per pound by quantity in
		//hundredths of a pound
		double lbScanned = w / 100.0;
		double cost = lbScanned * p;
		cost += .5; //for rounding
		total += (int) cost;
	}
	if (total) { //for weight priced items
		p = total;
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
