 #include <iostream>

#define MAX_VELICINA 10

template <typename T>
class Iterator;

template <typename T>
class Kolekcija {
public:
	virtual void dodajNaKraj(const T elem) = 0;
	virtual int velicina()const = 0;
	virtual bool prazna() const {
		return velicina() == 0;
	}
	virtual Iterator<T>* getIterator() = 0;
	virtual ~Kolekcija(){}
};

template <typename T>
class Iterator {
public:
	virtual T element()const = 0;
	virtual void sledeci() = 0;
	virtual bool kraj()const = 0;
	virtual ~Iterator(){}
};

template <typename T>
class Niz;

template <typename T>
class IteratorNiza : public Iterator<T> {
	Niz<T>* iterator_niza;
	int trenutna_pozicija;
public:
	IteratorNiza(Niz<T>* niz, int tren_pozicija = 0) : 
		iterator_niza(niz), trenutna_pozicija(tren_pozicija) {}
	T element()const override {
		return iterator_niza->niz[trenutna_pozicija];
	}
	void sledeci() override {
		trenutna_pozicija++;
	}
	bool kraj()const override {
		return trenutna_pozicija == iterator_niza->velicina();
	}
};

template <typename T>
class Niz : public Kolekcija<T> {
private:
	T niz[MAX_VELICINA];
	int trenutna_vel = 0;
public:
	void dodajNaKraj(const T elem) override {
		niz[trenutna_vel++] = elem;
	}
	int velicina()const override{
		return trenutna_vel;
	}
	Iterator<T>* getIterator() override {
		return new IteratorNiza<T>(this);
	}
	friend class IteratorNiza<T>;
	
};

template <typename T>
struct Cvor {
	T podatak;
	Cvor<T>* link;
	Cvor(T podatak, Cvor<T>* link = nullptr) :
		podatak(podatak), link(link) {}
};

template <typename T>
class JednostrukaLancanaLista;

template <typename T>
class IteratorJednostrukeLancaneListe : public Iterator<T> {
	JednostrukaLancanaLista<T>* lista;
	Cvor<T>* temp_cvor;
public:
	IteratorJednostrukeLancaneListe(JednostrukaLancanaLista<T>* lista) : lista(lista) {
		temp_cvor = lista->head;
	}
	T element()const override {
		return temp_cvor->podatak;
	}
	void sledeci() override {
		temp_cvor = temp_cvor->link;
	}
	bool kraj()const override {
		return temp_cvor == nullptr;
	}
};

template <typename T>
class JednostrukaLancanaLista : public Kolekcija<T> {
	Cvor<T>* head = nullptr;
public:
	void dodajNaKraj(const T elem) override {
		if (head == nullptr) {
			head = new Cvor<T>(elem);
			return;
		}
		Cvor<T>* temp = head;
		while (temp->link)
			temp = temp->link;
		temp->link = new Cvor<T>(elem);
	}
	int velicina()const override {
		if (!head)
			return 0;
		int velicina = 0;
		Cvor<T>* temp = head;
		while (temp) {
			temp = temp->link;
			velicina++;
		}
		return velicina;
	}
	Iterator<T>* getIterator() override {
		return new IteratorJednostrukeLancaneListe<T>(this);
	}
	friend class IteratorJednostrukeLancaneListe<T>;
	~JednostrukaLancanaLista() {
		if (head) {
			Cvor<T>* temp = head;
			Cvor<T>* sled;
			while (temp) {
				sled = temp->link;
				delete temp;
				temp = sled;
			}
		}
	}
};

template<typename T>
void testirajKolekciju(Kolekcija<T>* kolekcija) {
	Iterator<T>* iterator = kolekcija->getIterator();
	for (; !iterator->kraj(); iterator->sledeci()) {
		std::cout << iterator->element() << "\t";
	}
	std::cout << std::endl;
}

int main() {
	using T = int;

	Kolekcija<T>* niz = new Niz<T>();
	niz->dodajNaKraj(1);
	niz->dodajNaKraj(3);
	niz->dodajNaKraj(2);

	Kolekcija<T>* lista = new JednostrukaLancanaLista<T>();
	lista->dodajNaKraj(1);
	lista->dodajNaKraj(2);
	lista->dodajNaKraj(3);

	testirajKolekciju(niz);
	testirajKolekciju(lista);

	delete niz;
	delete lista;

	return 0;
}

template <typename T>
class Kolekcija {
public:
	virtual void dodajNaKraj(T*) = 0;
	virtual int velicina() = 0;
	virtual bool empty() {
		if (this->velicina() == 0)
			return 0;
		else return 1;
	}

};

template <typename T>
class Niz;

