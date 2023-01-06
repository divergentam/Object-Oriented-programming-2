#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class AbstractProductA {
protected:
	int a;
public:
	AbstractProductA(int a) : a(a) {
		cout << "Custom konstruktor: AbstractProductA(int a)" << endl;
	}
	virtual void describe() = 0;
	virtual ~AbstractProductA(){}
};

class ProductA1 : public AbstractProductA {
private: 
	string naziv;
public:
	ProductA1(int a1, string naziv) : AbstractProductA(a1), naziv(naziv) {
		cout << "Custom konstruktor: ProductA1(int a1, string naslov1)" << endl;
	}
	void describe() {
		cout << "Proozvod A1: ( " << a << ", " << naziv << " )" << endl;
	}
};

class ProductA2 : public AbstractProductA {
private:
	string naziv;
public:
	ProductA2(int a2, string naziv) : AbstractProductA(a2), naziv(naziv) {
		cout << "Custom konstruktor: ProductA2(int a2, string naslov2)" << endl;
	}
	void describe() {
		cout << "Proozvod A2: ( " << a << ", " << naziv << " )" << endl;
	}
};

class AbstractProductB {
protected:
	int b;
public:
	AbstractProductB(int b) : b(b) {
		cout << "Custom konstruktor: AbstractProductB(int b)" << endl;
	}
	void setb(int b) {
		this->b = b;
	}
	virtual void describe() = 0;
	virtual ~AbstractProductB() {}
};

class ProductB1 : public AbstractProductB {
private:
	string naziv;
public:
	ProductB1(int b1, string naziv) : AbstractProductB(b1), naziv(naziv) {
		cout << "Custom konstruktor: ProductB1(int b1, string naslov1)" << endl;
	}
	void describe() {
		cout << "Proozvod B1: ( " << b << ", " << naziv << " )" << endl;
	}
};

class ProductB2 : public AbstractProductB {
private:
	string naziv;
public:
	ProductB2(int b2, string naziv) : AbstractProductB(b2), naziv(naziv) {
		cout << "Custom konstruktor: ProductB2(int b2, string naslov2)" << endl;
	}
	void describe() {
		cout << "Proozvod B2: ( " << b << ", " << naziv << " )" << endl;
	}
};

class AbstractFactory {
public:
	virtual AbstractProductA* createProductA() = 0;
	virtual AbstractProductB* createProductB() = 0;
	virtual void describe() = 0;
	virtual ~AbstractFactory() {}
};

class ConcreteFactory1 : public AbstractFactory{
public:
	AbstractProductA* createProductA() {
		AbstractProductA*  producta1 = new ProductA1(1, "Product A1");
		return producta1;
	}
	AbstractProductB* createProductB() {
		AbstractProductB* productb1 = new ProductB1(1, "Product B1");
		return productb1;
	}
	void describe() {
		cout << "ConcreteFactory1: " << endl;
	}
	~ConcreteFactory1() {}
};

class ConcreteFactory2 : public AbstractFactory {
public:
	AbstractProductA* createProductA() {
		AbstractProductA* producta2 = new ProductA2(2, "Product A2");
		return producta2;
	}
	AbstractProductB* createProductB() {
		AbstractProductB* productb2 = new ProductB2(2, "Product B2");
		return productb2;
	}
	void describe() {
		cout << "ConcreteFactory2: " << endl;
	}
	~ConcreteFactory2() {}
};

int main() {
	ConcreteFactory1 cf1;
	ConcreteFactory2 cf2;

	cf1.describe();
	cf1.createProductA()->describe();
	cf1.createProductB()->describe();

	cout << endl;

	cf2.describe();
	cf2.createProductA()->describe();
	cf2.createProductB()->describe();

	return 0;
}