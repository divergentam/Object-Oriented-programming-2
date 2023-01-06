#pragma once
#include <iostream>
#include <unordered_map>

class Kontekst {
	std::unordered_map<std::string, bool> vrednosti;
public:
	bool vrednost(std::string kljuc) {
		return vrednosti[kljuc];
	}
	bool& operator[] (std::string kljuc) {
		return vrednosti[kljuc];
	}
	friend std::ostream& operator << (std::ostream& os, Kontekst k) {
		for (auto it = k.vrednosti.begin(); it != k.vrednosti.end(); it++) {
			os << it->first << ": " << it->second << std::endl;
		}
		os << std::endl;
		return os;
	}
};

class LogickiIzraz {
public:
	virtual bool interpretiraj(Kontekst& k) const = 0;
	virtual void ispisi() const = 0;
	virtual ~LogickiIzraz() {}
};

//termalni izrazi
class Konstanta : public LogickiIzraz {
	bool vrednost;
public:
	Konstanta(bool vrednost) : vrednost(vrednost){}
	void ispisi() const override {
		std::cout << vrednost;
	}
	friend std::ostream& operator << (std::ostream& os, const Konstanta& k) {
		os << k.vrednost;
		return os;
	}
};

//termalni izrazi
class Promenljiva : public LogickiIzraz {
	std::string ime;
public:
	Promenljiva(const std::string& ime) : ime(ime) {}
	bool interpretiraj(Kontekst& k) const override {
		return k.vrednost(ime);
	}
	void ispisi() const override {
		std::cout << ime;
	}
	friend std::ostream& operator << (std::ostream& os, const Promenljiva& p) {
		os << p.ime;
		return os;
	}
};

//netermalni izrazi
template <typename LevaFormula, typename DesnaFormula>
class LogickoIli : public LogickiIzraz {
	LevaFormula leva;
	DesnaFormula desna;
public:
	LogickoIli(const LevaFormula& leva, const DesnaFormula& desna) :
		leva(leva), desna(desna) {}
	bool interpretiraj(Kontekst& k) const override {
		return leva.interpretiraj(k) || desna.interpretiraj(k);
	}
	void ispisi() const override {
		std::cout << *this;
	}
	friend std::ostream& operator << (std::ostream& os, const LogickoIli& ili) {
		os << "OR(" << ili.leva << ", " << ili.desna << ")";
		return os;
	}
};

template <typename LevaFormula, typename DesnaFormula>
class LogickoI : public LogickiIzraz {
	LevaFormula leva;
	DesnaFormula desna;
public:
	LogickoI(const LevaFormula& leva, const DesnaFormula& desna) :
		leva(leva), desna(desna) {}
	bool interpretiraj(Kontekst& k) const override {
		return leva.interpretiraj(k) && desna.interpretiraj(k);
	}
	void ispisi() const override {
		std::cout << *this;
	}
	friend std::ostream& operator << (std::ostream& os, const LogickoI& i) {
		os << "AND(" << i.leva << ", " << i.desna << ")";
		return os;
	}
};

template <typename Izraz>
class Negacija : public LogickiIzraz {
	Izraz izraz;
public:
	Negacija(const Izraz& izraz) : izraz(izraz) {}
	bool interpretiraj(Kontekst& k) const override {
		return !izraz.interpretiraj(k);
	}
	void ispisi()const override {
		std::cout << *this;
	}
	friend std::ostream& operator << (std::ostream& os, const Negacija& ne) {
		os << "NOT(" << ne.izraz << ")";
		return os;
	}
};

