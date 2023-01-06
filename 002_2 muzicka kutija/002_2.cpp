#include <iostream>

using std::cout;
using std::cin;
using std::endl;

enum class Zanr {ROK, BALADA, POP};

class Melodija {
public:
	virtual void sviraj() = 0;
};

class RokMelodija : public Melodija {
public:
	void sviraj() {
		cout << "Pogledaj dom svoj andjele ... " << endl;
	}
};

class BaladaMelodija : public Melodija {
public:
	void sviraj() {
		cout << "Bila je tako lepaaa ... " << endl;
	}
};

class PopMelodija : public Melodija {
public:
	void sviraj() {
		cout << "Ispred teatra Baljsoj ja sam je cekao ... " << endl;
	}
};

class MuzickaKutija {
public:
	virtual Melodija* dajMelodiju(Zanr zanr) = 0;
};

class DomacaMuzickaKutija : public MuzickaKutija {
public:
	Melodija* dajMelodiju(Zanr zanr) {
		switch (zanr) {
		case Zanr::ROK: return new RokMelodija();
		case Zanr::POP: return new PopMelodija();
		case Zanr::BALADA: return new BaladaMelodija();
		default: return NULL;
		}
	}
};

int main() {
	MuzickaKutija* muzickaKutija = new DomacaMuzickaKutija();

	Melodija* rokMelodija = muzickaKutija->dajMelodiju(Zanr::ROK);
	rokMelodija->sviraj();
	Melodija* popMelodija = muzickaKutija->dajMelodiju(Zanr::POP);
	popMelodija->sviraj();

	cout << "Unesi vrstu melodije koju hoces da sviram (R-Rok, P-Pop, B-Balada)" << endl;
	char tip;
	cin >> tip;
	Melodija* mojaMelodija;
	switch (toupper(tip)) {
	case 'R':mojaMelodija = muzickaKutija->dajMelodiju(Zanr::ROK); break;
	case 'P':mojaMelodija = muzickaKutija->dajMelodiju(Zanr::POP); break;
	case 'B':mojaMelodija = muzickaKutija->dajMelodiju(Zanr::BALADA); break;
	default: mojaMelodija = NULL;
	}

	if (mojaMelodija != NULL) {
		mojaMelodija->sviraj();
	}
	else {
		cout << "Greska u unosu- nepostojeca vrsta melodije" << endl;
	}

	delete mojaMelodija;
	delete muzickaKutija;
	delete popMelodija;
	delete rokMelodija;

	return 0;
}