/*
5.Kreirati apstraktne klase Stolica, Sto i Polica (sa �isto virtuelnom metodom opis()) i
konkretne klase DrvenaStolica, DrveniSto, DrvenaPolica, ModernaStolica, ModerniSto, ModernaPolica
kao i fabrike za proizvode ove dve familije proizvoda
*/
#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class Stolica {
public:
	virtual void opis() = 0;
	virtual ~Stolica() {}
};

class DrvenaStolica : public Stolica {
public:
	void opis() {
		cout << "Drvena stolica." << endl;
	}
};

class ModernaStolica : public Stolica {
public:
	void opis() {
		cout << "Moderna stolica." << endl;
	}
};


class Sto {
public:
	virtual void opis() = 0;
	virtual ~Sto() {}
};

class DrveniSto : public Sto {
public:
	void opis() {
		cout << "Drveni sto." << endl;
	}
};

class ModerniSto : public Sto {
public:
	void opis() {
		cout << "Moderni sto." << endl;
	}
};

class Polica {
public:
	virtual void opis() = 0;
	virtual ~Polica() {}
};

class DrvenaPolica : public Polica {
public:
	void opis() {
		cout << "Drvena polica." << endl;
	}
};

class ModernaPolica : public Polica {
public:
	void opis() {
		cout << "Moderna polica." << endl;
	}
};

class FabrikaNamestaja {
public:
	virtual Stolica* napravistolicu() = 0;
	virtual Sto* napravisto() = 0;
	virtual Polica* napravipolicu() = 0;
	virtual ~FabrikaNamestaja(){}
};

class DrveniNamestaj : public FabrikaNamestaja {
public:
	Stolica* napravistolicu() {
		return new DrvenaStolica();
	}
	Sto* napravisto() {
		return new DrveniSto();
	}
	Polica* napravipolicu() {
		return new DrvenaPolica();
	}
};

class ModerniNamestaj : public FabrikaNamestaja {
public:
	Stolica* napravistolicu() {
		return new ModernaStolica();
	}
	Sto* napravisto() {
		return new ModerniSto();
	}
	Polica* napravipolicu() {
		return new ModernaPolica();
	}
};

/*
6.Napraviti klasu Soba koja ima stolicu, sto i policu.
Sobu treba kreirati kao objekat klase Dizajner na na�in:
Soba s = dizajner.kreirajSobu(stilSobe);
Mo�emo imati dva graditelja koja �e kreirati sobu postavljaju�i name�taj iz odre�ene fabrike
(jedan graditelj koristi jednu fabriku, drugi drugu). Dizajner bi igrao ulogu upravlja�a/direktora.
Ukoliko konkretne graditelje kreiramo na osnovu stila sobe (enum ili string)
onda imamo tako�e i primenu fabri�kog metoda koji �e kreirati graditelja.
*/

class Soba {
private:
	Sto* sto;
	Stolica* stolica;
	Polica* polica;
public:
	void setSto(Sto* sto) {
		this->sto = sto;
	}
	void setStolicu(Stolica* stolica) {
		this->stolica = stolica;
	}
	void setPolicu(Polica* polica) {
		this->polica = polica;
	}
	void opisi() {
		cout << "Soba sadrzi : " << endl;
			sto->opis();
			stolica->opis();
			polica->opis();
	}
};

enum class StilSobe { DRVENA, MODERNA };

class GraditeljSobe {
protected:
	Soba* soba;
public:
	GraditeljSobe& napraviPraznuSobu() {
		soba = new Soba();
		return *this;
	}
	virtual GraditeljSobe& postaviSto() = 0;
	virtual GraditeljSobe& postaviStolicu() = 0;
	virtual GraditeljSobe& postaviPolicu() = 0;
	Soba* returnSoba() {
		return soba;
	}
	static GraditeljSobe* kreirajGraditelja(StilSobe stil);
	~GraditeljSobe() {};
};

class GraditeljDrveneSobe : public GraditeljSobe {
private:
	DrveniNamestaj fabrika;
public:
	GraditeljSobe& postaviSto() {
		soba->setSto(fabrika.napravisto());
		return *this;
	}
	GraditeljSobe& postaviStolicu() {
		soba->setStolicu(fabrika.napravistolicu());
		return *this;
	}
	GraditeljSobe& postaviPolicu() {
		soba->setPolicu(fabrika.napravipolicu());
		return *this;
	}
};

class GraditeljModerneSobe : public GraditeljSobe{
private:
	ModerniNamestaj fabrika;
public:
	GraditeljSobe& postaviSto() {
		soba->setSto(fabrika.napravisto());
		return *this;
	}
	GraditeljSobe& postaviStolicu() {
		soba->setStolicu(fabrika.napravistolicu());
		return *this;
	}
	GraditeljSobe& postaviPolicu() {
		soba->setPolicu(fabrika.napravipolicu());
		return *this;
	}
};

class Dizajer {
public:
	Soba* napraviSobu(GraditeljSobe* builder) {
		builder->napraviPraznuSobu();
		builder->postaviSto().postaviStolicu().postaviPolicu();
		return builder->returnSoba();
	}
};

GraditeljSobe* GraditeljSobe::kreirajGraditelja(StilSobe stil) {
	if (stil == StilSobe::MODERNA) return new GraditeljModerneSobe();
	else return new GraditeljDrveneSobe();
}

class ENUMDizajner {
public:
	Soba* kreirajSobu(StilSobe stil) {
		GraditeljSobe* builder = GraditeljSobe::kreirajGraditelja(stil);
		builder->napraviPraznuSobu();
		builder->postaviSto().postaviStolicu().postaviPolicu();
		Soba* soba = builder->returnSoba();
		delete builder;
		return soba;
	}
};

int main() {
	DrveniNamestaj dn;
	ModerniNamestaj mn;

	dn.napravistolicu()->opis();
	dn.napravisto()->opis();
	dn.napravipolicu()->opis();

	cout << endl;

	mn.napravistolicu()->opis();
	mn.napravisto()->opis();
	mn.napravipolicu()->opis();

	Dizajer diz;
	GraditeljDrveneSobe ds;
	ENUMDizajner ediz;

	cout << endl;

	Soba* s1 = diz.napraviSobu(&ds);
	s1->opisi();

	cout << endl;

	Soba* s2 = ediz.kreirajSobu(StilSobe::MODERNA);
	s2->opisi();

	delete s1;
	delete s2;

	return 0;
}


