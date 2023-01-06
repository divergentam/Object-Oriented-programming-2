#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T>
class Vektor {
private:
	int n;
	vector <T> vec;
public:
	typedef T type; // Mogu da pristupim tipu

	Vektor(int n ): n(n) {
		for (int i = 0; i < n; i++) {
			vec.push_back(0);
		}
	}
	Vektor& operator=(const Vektor& drugi) = default;

	template <typename T>
	Vektor& operator=(const T& drugi) { //poziva se za bilo koji drugi tip
		//if (this == &drugi) return *this;
		vec.clear(); // vraca vektor velicine 0
		for (int i = 0; i < drugi.getSize(); i++)
			vec.push_back(drugi[i]);
		return *this;
	}

	//NISU ISTI OPERATORI 
	T operatir[](int i) const {
		return vec[i];
	}
	T& operator[] {
		return vec[i];
	}
};

//template<typename>class OP 
// da pokrije razne fje to je operacija koja vraca neki tip
template <typename T, template<typename>class OP, typename L, typename R>
class BinarniIzraz {
priate:
	L leviop;
	R desniop;
public:
	typedef T type;
	BinarniIzraz(L lop, R dop) : leviop(lop), desniop(dop) {}
	T operator[](int i) const {
		return OP<T>::evaluiraj(leviop[i], desniop[i]);
	}
	int getSize() {
		return desniop.getSize();
	}
};

template<typename T>
struct Saberi {
	struct T evauliraj(T a, T b) {
		return a + b;
	}
};

template <typename L, typename R>
BinarniIzraz<typename L::type, Saberi, L, R> 
operator+(const L& levi, const R& desni) {
	return BinarniIzraz<typename L::type, Saberi, L, R>(levi, desni);
}

int main() {
	Vektor <int> v1(10);
	Vektor <int> v2(10);

	for (int i = 0; i < 10; i++) {
		v1[i] = i;
		v2[i] = i * i;
	}

	return 0;
}

