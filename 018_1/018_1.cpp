/*
 Implementirati klase Račun, DinarskiRačun, DevizniRačun, IBanka, BankaA, BankaB.
Banke imaju listu računa, a imaju i listu blokiranih računa. Sa računa se, posredstvom
banke, može zatražiti transakcija na neki drugi račun. Krus evra je 119/117
(prodajni/kupovni). Kada se zatraži transakcija sa računa, dobija se povratna informacija
o tome koliko zaista novca treba skinuti sa računa. Naime, konkretne banke računaju
različite provizije za transakcije. Rezultat 0 znači da transakcija nije uspela.
*/

#include <iostream>

class Banka;

class Racun {
	std::string valuta;
	std::string brRacuna;
	int trenutnoStanje;
	Banka* banka;
public:
	Racun(Banka* banka, std::string brRacuna, int trenutno) : banka(banka), brRacuna(brRacuna), trenutnoStanje(trenutno) {}
	virtual void posaljiNovac(std::string saRacuna, float iznos) {
		std::cout << "Sa racuna " << saRacuna << " uplaceno " << iznos << this->valuta;
	}
};

class DinarskiRacun : public Racun {
	std::string valuta= "din";
public:
	using Racun::Racun;

};

class DevizniRacun : public Racun {
	std::string valuta = "evro";
public:
	using Racun::Racun;
};