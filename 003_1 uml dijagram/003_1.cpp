//1.Implementirati opšti oblik projektnog uzorka Prototip na osnovu UML dijagrama sa slike

#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

//apstraktni prototip
class Prototype {
protected:
	int a;
	string b;
public:
	Prototype() {}
	Prototype(int a, const string& b) : a(a), b(b) {
		cout << "Kreiram prototip i vrsim kompleksnu racunicu" << endl;
	}
	void setB(const string& b) {
		this->b = b;
	}
	virtual Prototype* clone() = 0;
	virtual void describe() = 0;

	virtual ~Prototype() {}
};

//konkretni prototip 1
class ConcretePrototype1 : public Prototype {
public:
	ConcretePrototype1() : Prototype() {}
	ConcretePrototype1(int a, const string& b) : Prototype(a, b) {
		cout << "Kreiram konkretni prototip 1 i vrsim kompleksnu racunicu" << endl;
	}
	//
	Prototype* clone() {
		ConcretePrototype1* clone = new ConcretePrototype1();
		cout << "Kloniram protototip 1: " << this->a << " ," << this->b << endl;
		clone->a = this->a;
		clone->b = this->b;
		cout << "Kloniram protototip 1 nakon postavljanja a i b: " << this->a << " ," << this->b << endl;
		return clone;
	}
	void describe() {
		cout << "Konkretni prototip 1 :" << this->b << endl;
	}
};

class ConcretePrototype2 : public Prototype {
public:
	ConcretePrototype2() : Prototype() {}
	ConcretePrototype2(int a, const string& b) : Prototype(a, b) {
		cout << "Kreiram konkretni prototip 2 i vrsim kompleksnu racunicu" << endl;
	}
	//
	Prototype* clone() {
		ConcretePrototype2* clone = new ConcretePrototype2();
		cout << "Kloniram protototip 2: " << this->a << " ," << this->b << endl;
		clone->a = this->a;
		clone->b = this->b;
		cout << "Kloniram protototip 2 nakon postavljanja a i b: " << this->a << " ," << this->b << endl;
		return clone;
	}
	void describe() {
		cout << "Konkretni prototip 2 :" << this->b << endl;
	}
};

int main() {
	Prototype* prvi, * drugi, * c, * d;
	prvi = new ConcretePrototype1(1, "prvi");
	drugi = new ConcretePrototype2(2, "drugi");
	cout << "PRVI PROTOTIP : ";
	prvi->describe();
	cout << "PRVI PROTOTIP : ";
	drugi->describe();


	c = prvi->clone();
	cout << "C PROTOTIP : ";
	c->describe();
	c->setB("c");
	cout << "Novo c: ";
	c->describe();

	cout << "D PROTOTIP : ";
	d = drugi->clone();
	d->describe();
	d->setB("d");
	cout << "Novo d: ";
	d->describe();

	delete prvi;
	delete drugi;
	delete c;
	delete d;
	return 0;
}