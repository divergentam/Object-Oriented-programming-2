/*
 Napisati klase JednostrukoPovezanaLista i Stek i omogućiti trenutno ažuriranje
informacije o veličini, minimalnom i maksimalnom elementu i zbiru elemenata pomoću
zasebnih “posmatrača”. Radi jednostavnosti, u ove strukture samo vršiti dodavanje
elemenata.
*/

#include <iostream>
#include <limits.h>
#include <vector>

class Funkcija {
public:
	virtual void update(int) = 0;
	virtual int f() const = 0;
	virtual std::string opis() const = 0;
	virtual ~Funkcija() {}
};

class Suma : public Funkcija {
	int s = 0;
public:
	void update(int novaVrednost) override {
		s += novaVrednost;
	}
	int f() const override {
		return s;
	}
	std::string opis() const override{
		return "Suma";
	}
};

class Velicina : public Funkcija {
	int br = 0;
public:
	void update(int) override {
		br++;
	}
	int f() const override {
		return br;
	}
	std::string opis() const override {
		return "Velicina";
	}
};

class Maximum : public Funkcija {
	int max = INT_MIN;
public:
	void update(int br) override {
		/*if (max < br)
			max = br;*/
		max = br > max ? br : max;
	}
	int f() const override {
		return max;
	}
	std::string opis() const override {
		return "Maximum";
	}
};

class Minimum : public Funkcija {
	int min = INT_MAX;
public:
	void update(int br) override {
		min = br < min ? br : min;
	}
	int f() const override {
		return min;
	}
	std::string opis() const override {
		return "Minimum";
	}
};

class Kolekcija {
protected:
	std::vector<Funkcija*> funkcije;
	void updateFunkcije(int novaVr) {
		for (auto f : funkcije)
			f->update(novaVr);
	}
public:
	virtual void addElement(int newElem) = 0;
	void addFunkciju(Funkcija* f) {
		funkcije.push_back(f);
	}
	std::vector<Funkcija*> getFunkcije() const {
		return funkcije;
	}
	~Kolekcija(){}
};

#define MAX_VELICINA 10

class Stack : public Kolekcija {
	int top = 0;
	int niz[MAX_VELICINA];
public:
	void addElement(int newElem) override {
		niz[top++] = newElem;
		updateFunkcije(newElem);
	}
};

struct Cvor {
	int broj;
	Cvor* link;
	Cvor(int broj, Cvor* link = nullptr) : broj(broj), link(link) {}
};

class JednostrukoPovezanaLista : public Kolekcija {
	Cvor* head = nullptr;
public:
	void addElement(int newElem) override {
		if (!head) {
			head = new Cvor(newElem);
		}
		else {
			Cvor* novi = head;
			head = new Cvor(newElem, novi);
		}
		updateFunkcije(newElem);
	}
};

int main() {
	Kolekcija* k = new Stack();
	k->addFunkciju(new Velicina());
	k->addFunkciju(new Suma());
	k->addFunkciju(new Minimum());
	k->addFunkciju(new Maximum());

	k->addElement(1);
	k->addElement(11);
	k->addElement(-1);
	k->addElement(100);
	k->addElement(2);
	k->addElement(3);

	// Kad god je tip podataka dostupan u vreme kompajliranja, možemo koristiti ključnu reč 
	// auto umesto tipa (naročito praktično ako nam je naporno pišemo pun naziv tipa
	// poput std::vector<Funkcija*>
	auto funkcije = k->getFunkcije();
	for (auto f : funkcije) {
		std::cout << "Vrednost funkcije " << f->opis() << " je " << f->f() << std::endl;
	}

	return 0;
}