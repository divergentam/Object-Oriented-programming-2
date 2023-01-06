/*
Napraviti klasu Product koja je klasa za neki konkretan/krajnji prozvod
Neka sadrzi od atributa part tipa int i fje setPart i showUse
koja opisuje proizvod koji koristim i koliko delova proizvod ima.
Konstruisati bildera sa f-jama buildProduct buildPart i implementirati getProduct.
U konkretnom graditelju implementirati buildProduct i buildPart (5)*/

#include <iostream>
using std::cout;
using std::endl;

class Product {
protected:
	int part;
public:
	void setPart(int part) {
		this->part = part;
	}
	void showUse() {
		cout << "Koristim proizvod koji ima " << part << " deo" << endl;
	}
};

class Builder {
protected:
	Product* product;
public:
	virtual void buildProduct() = 0;
	virtual void buildPart() = 0;
	Product* getProduct() {
		return product;
	}
};

class ConcreteBuilder :
	public Builder {
public:
	void buildProduct() {
		product = new Product();
	}
	void buildPart() {
		product->setPart(5);
	}
};

class Director {
public:
	Product* create(Builder* builder) {
		builder->buildProduct();
		builder->buildPart();
		return builder->getProduct();
	}
};

int main() {
	Director dir;
	ConcreteBuilder cb;

	Product* proizvod1 = dir.create(&cb);
	proizvod1->showUse();

	delete proizvod1;
	return 0;
}