/*
Napravi clasu Product sa atributima intSvojstvo, floatSvojstvo, charSvojstvo,
konstruisati podrazumevani i custom konstruktor, 3 f-je koje postavljaju odredjeno svojstvo,
f-ju prikazi, uradi nesto i uradi nesto drugo.
*/

#include <iostream>
using std::cout;
using std::endl;

class Proizvod {
protected:
	int intSvojstvo;
	float floatSvojstvo;
	char charSvojstvo;
public:
	Proizvod() : intSvojstvo(0), floatSvojstvo(0.0), charSvojstvo(' ') {}
	Proizvod(const int ints, const float floats, const char chars):
		intSvojstvo(ints), 
		floatSvojstvo(floats), 
		charSvojstvo(chars){}
	void postaviIntSvojstvo(int ints) {
		intSvojstvo = ints;
	}
	void postaviFloatSvojstvo(float floats) {
		floatSvojstvo = floats;
	}
	void postaviCharSvojstvo(char chars) {
		charSvojstvo = chars;
	}
	void prikazi() {
		cout << "<SASTAV PROIZVODA>" << endl;
		cout << "\tintSvojstvo: " << this->intSvojstvo << endl;
		cout << "\tfloatSvojstvo: " << this->floatSvojstvo << endl;
		cout << "\tcharSvojstvo: " << this->charSvojstvo << endl;
	}
	void uradiNesto() {
		cout << "Proizvod > Radim nesto..." << endl;
	}
	void uradiNestoDrugo() {
		cout << "Proizvod > Radim nesto drugo..." << endl;
	}

};

class Builder {
protected:
	Proizvod proizvod;
public:
	static const int    DEFAULT_INT_SVOJSTVO;
	static const float  DEFAULT_FLOAT_SVOJSTVO;
	static const char   DEFAULT_CHAR_SVOJSTVO;
	Builder() {
		proizvod = Proizvod(DEFAULT_INT_SVOJSTVO, DEFAULT_FLOAT_SVOJSTVO, DEFAULT_CHAR_SVOJSTVO);
	}
	Builder& postaviIntSvojstvo(const int ints) {
		proizvod.postaviIntSvojstvo(ints);
		return *this;
	}
	Builder& postaviFloatSvojstvo(const float floats) {
		proizvod.postaviFloatSvojstvo(floats);
		return *this;
	}
	Builder& postaviCharSvojstvo(const char chars) {
		proizvod.postaviCharSvojstvo(chars);
		return *this;
	}
	Proizvod napraviProizvod() {
		return proizvod;
	}
};

const int Builder::DEFAULT_INT_SVOJSTVO = 5;
const float Builder::DEFAULT_FLOAT_SVOJSTVO = 1.4141f;
const char Builder::DEFAULT_CHAR_SVOJSTVO = 'X';



int main() {

	Proizvod proizvod1 = Builder().postaviIntSvojstvo(2)
		.postaviCharSvojstvo('x')
		.napraviProizvod();
	proizvod1.prikazi();

	Builder builder;
	Proizvod proizvod2 = builder.napraviProizvod(); //vraca default proizvod
	builder.postaviCharSvojstvo('*');
	Proizvod proizvod3 = builder.napraviProizvod();
	proizvod2.prikazi();
	proizvod3.prikazi();

	return 0;
}