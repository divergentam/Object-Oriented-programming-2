#include <iostream>

using std::cout;
using std::endl;

class Proizvod {
public:
	virtual void use() = 0;
};

class KonkretanProizvod : public Proizvod {
	void use() {
		cout << "Koristim konkretan proizvod" << endl;
	}
};

class Creator {
public:
	virtual Proizvod* factoryMethod() = 0;
};

class KonkretniCreator : public Creator{
public:
	Proizvod* factoryMethod(){
		return new KonkretanProizvod();
	}
};

int main() {
	KonkretniCreator creator;
	Proizvod* proizvod = creator.factoryMethod();
	proizvod->use();

	delete proizvod;
}