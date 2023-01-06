#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

//definisemo klasu unapred da bi je oznacili za friend clasu u Paragraf klasi
class ParagrafBuilder;

class Paragraf {
private: // kako bi zabranili da korisnik pravi rucno proizvod
	Paragraf(string tekst) : tekst(tekst) {}
	//koko bu mogla da koristi konstruktor
	friend class ParagrafBuilder;
protected:
	string tekst;
	int velicinaFonta;
	string stilFonta;
	string poravnanje;
	bool prvaLinija;
public:
	void setVelicinaFonta(int v) {
		velicinaFonta = v;
	}
	int getVelicinaFonta() {
		return velicinaFonta;
	}
	void setStilFonta(string s) {
		stilFonta = s;
	}
	string getStilFonta() {
		return stilFonta;
	}
	void setPoravnanje(string p) {
		poravnanje = p;
	}
	string getPoravnanje() {
		return poravnanje;
	}
	void setPrvaLinija(bool pl) {
		prvaLinija = pl;
	}
	void getPrvaLinija() {
		if (prvaLinija) cout << "Prva linija je uvucena";
		else cout << "Prva linija nije uvicena";
	}
	void show() {
		cout << "Paragraf ( " << tekst << " ) " <<
			"_________________" << endl <<
			"Velicina fonta: " << velicinaFonta << endl <<
			"Stil fonta: " << stilFonta << endl <<
			"Poravnanje: " << poravnanje << endl;
		this->getPrvaLinija();
	}
};

static const string DEFAULT_FONT_STYLE = "Times New Roman";
static const string DEFAULT_ALIGNMENT = "LEFT";
static const unsigned int DEFAULT_FONT_SIZE = 12;
static const bool DEFAULT_FIRST_LINE = false;

class ParagrafBuilder {
protected:
	Paragraf* paragraf;
public:
	Paragraf* create(string tekst) {
		paragraf = new Paragraf(tekst);
		paragraf->setPoravnanje(DEFAULT_ALIGNMENT);
		paragraf->setVelicinaFonta(DEFAULT_FONT_SIZE);
		paragraf->setStilFonta(DEFAULT_FONT_STYLE);
		paragraf->setPrvaLinija(DEFAULT_FIRST_LINE);
		return paragraf;
	}
	void putVelicinaFonta(const int v) {
		paragraf->setVelicinaFonta(v);
	}
	void putStilFonta(const string s) {
		paragraf->setStilFonta(s);
	}
	void putPoravnanje(const string p) {
		paragraf->setPoravnanje(p);
	}
	void putPrvaLiija(const bool pl) {
		paragraf->setPrvaLinija(pl);
	}
	Paragraf* returnParagraf() {
		return paragraf;
	}
};

class Director {
protected:
	ParagrafBuilder* builder;
	string tekst;
public:
	Paragraf* HeadingParagraf(ParagrafBuilder* builder) {
		cout << "Koji tekst zelite da vas paragraf sadrzi?" << endl << "Unesite tekst: ";
		cin >> tekst;
		builder->create(tekst);
		builder->putPoravnanje("CENTRALNO");
		builder->putVelicinaFonta(16);
		return builder->returnParagraf();
	}
	Paragraf* NormalParagraf(ParagrafBuilder* builder) {
		cout << "Koji tekst zelite da vas paragraf sadrzi?" << endl << "Unesite tekst: ";
		cin >> tekst;
		builder->create(tekst);
		builder->putPoravnanje("JUSTIFY");
		builder->putVelicinaFonta(12);
		builder->putPrvaLiija(true);
		return builder->returnParagraf();
	}
	Paragraf* ParagrafStiloviID(string tekst, int br) {
		switch (br) {
		case 1:
			HeadingParagraf(builder);
		case 2:
			NormalParagraf(builder);
		}
	}
};



int main() {
	Director dir;
	ParagrafBuilder pb;

	Paragraf* p1 = dir.HeadingParagraf(&pb);
	p1->show();

	delete p1;

	return 0;
}
