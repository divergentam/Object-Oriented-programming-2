/*
Krajnji proizvod je pica sa int atributima velicina, kecap, sir, sunka, papricice
imamo podrazumevanu picu koja ima vel 10
iammo fje za sve atribute getAtrubut i setAtribut i show
Imamo pica graditelja sa fjama putAtribut 

*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Pizza {
protected:
	int size;
	int ketchup;
	int cheese;
	int ham;
	int pepperoni;
public:
	Pizza() {
		size = 10;
		ketchup = 0;
		cheese = 0;
		ham = 0;
		pepperoni = 0;
	}
	void setSize(int size) {
		this->size = size;
	}
	int getSize(){
		return size;
	}
	void setKetchup(int ketchup) {
		this->ketchup = ketchup;
	}
	int getKetchup() {
		return ketchup;
	}
	void setCheese(int cheese) {
		this->cheese = cheese;
	}
	int getCheese() {
		return cheese;
	}
	void setHam(int ham) {
		this->ham = ham;
	}
	int getHam() {
		return ham;
	}
	void setPepperoni(int pepperoni) {
		this->pepperoni = pepperoni;
	}
	int getPepperoni() {
		return pepperoni;
	}
	void show() {
		cout  << "<<<<Pizza>>>>" << endl <<
			"------size: " << size << endl <<
			"--ketchhup: " << ketchup << "g " <<  endl <<
			"----chesse: " << cheese << "g " << endl <<
			"-------ham: " << ham << "g " << endl <<
			"-pepperoni: " << pepperoni << "g " << endl << endl;
	}
};

class PizzaBuilder {
protected:
	Pizza* pizza;
public:
	virtual void createPizza() = 0;
	virtual void putSize(int s) = 0;
	virtual void putKetchup(int k) = 0; 
	virtual void putCheese(int c) = 0;
	virtual void putHam(int h) = 0;
	virtual void putPepperoni(int p) = 0;
	Pizza* getPizza(){
		return pizza;
	}
};

class ConcreteBuilder:
	public PizzaBuilder{
public:
	void createPizza() {
		pizza = new Pizza();
	}
	void putSize(int s) {
		pizza->setSize(s);
	 }
	void putKetchup(int k) {
		pizza->setKetchup(k);
	 }
	void putCheese(int c) {
		pizza->setCheese(c);
	 }
	void putHam(int h) {
		pizza->setHam(h);
	 }
	void putPepperoni(int p) {
		pizza->setPepperoni(p);
	}
};

class Pizzeria {
public:
	int s;
	Pizza* createMargarita(PizzaBuilder *builder) {
		builder->createPizza();
		cout << "Unesite zeljenu velicinu pice u cm : ";
		cin >> s;
		if (s < 25)
			throw std::exception("Velicina pizze moraja biti veca od 25!");
		builder->putSize(s);
		builder->putKetchup(s*5);
		builder->putCheese(s*7);
		builder->putHam(s*8);
		cout << "Cena Margarite pize je: " << s * 25 << " din" << endl;
		return builder->getPizza();
	}
	Pizza* createCapriccosa(PizzaBuilder* builder) {
		builder->createPizza();
		cout << "Unesite zeljenu velicinu pice u cm : ";
		cin >> s;
		if (s < 25)
			throw std::exception("Velicina pizze moraja biti veca od 25!");
		builder->putSize(s);
		builder->putKetchup(s * 8);
		builder->putCheese(s * 10);
		builder->putHam(s * 15);
		cout << "Cena Capriccosa pize je: " << s * 30 << " din" << endl;
		return builder->getPizza();
	}
};


int main() {
	Pizzeria pizerija;
	ConcreteBuilder cb;
	try {
		Pizza* piza1 = pizerija.createMargarita(&cb);
		piza1->show();

		Pizza* piza2 = pizerija.createCapriccosa(&cb);
		piza2->show();
	}
	catch(std::exception &e) {
		cout << e.what() << endl;
	}
	return 0;
}