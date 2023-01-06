#include <iostream>

using std::cout;
using std::endl;

class Implementator {
public:
	virtual void implementation() = 0;
	virtual ~Implementator() {};
};

class ConcreteImplementator1 : public Implementator {
public:
	void implementation() {
		cout << "Concrete implementation 1" << endl;
	}
};

class ConcreteImplementator2 : public Implementator {
public:
	void implementation() {
		cout << "Concrete implementation 2" << endl;
	}
};

class Abstraction {
protected:
	Implementator* implementator;
public:
	Abstraction(Implementator* impl) :
		implementator(impl) {}
	virtual void function() {
		implementator->implementation();
	}
	virtual ~Abstraction() {
		delete implementator;
	}
};

class RedefinedAbstraction : public Abstraction {
public:
	RedefinedAbstraction(Implementator* impl) :
		Abstraction(impl) {}
	virtual void function() {
		cout << "RedefinedAbstraction: ";
		implementator->implementation();
	}
};

int main() {
	Abstraction* a1 = new Abstraction(new ConcreteImplementator2());
	Abstraction* a2 = new RedefinedAbstraction(new ConcreteImplementator1());

	a1->function();
	a2->function();
	
	return 0;
}