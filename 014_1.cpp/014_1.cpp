#include "014_1.h"

template <typename LevaFormula,  typename DesnaFormula>
auto AND(const LevaFormula leva, const DesnaFormula desna) {
	if constexpr (std::is_same<LevaFormula, bool>::value) {
		if constexpr (std::is_same<DesnaFormula, bool>::value)
			return LogickoI<Konstanta, Konstanta>(Konstanta(leva), Konstanta(desna));
		else if constexpr (std::is_same<DesnaFormula, const char*>::value)
			return LogickoI<Konstanta, Promenljiva>(Konstanta(leva), Promenljiva(desna));
		else
			return LogickoI<Konstanta, DesnaFormula>(Konstanta(leva), desna);
	}
	else if constexpr (std::is_same<LevaFormula, const char*>::value) {
		if constexpr (std::is_same<DesnaFormula, bool>::value)
			return LogickoI<Promenljiva, Konstanta>(Promenljiva(leva), Konstanta(desna));
		else if constexpr (std::is_same<DesnaFormula, const char*>::value)
			return LogickoI<Promenljiva, Promenljiva>(Promenljiva(leva), Promenljiva(desna));
		else
			return LogickoI<Promenljiva, DesnaFormula>(Promenljiva(leva), desna);
	}
	else {
		if constexpr (std::is_same<DesnaFormula, bool>::value)
			return LogickoI<LevaFormula, Konstanta>(leva, Konstanta(desna));
		else if constexpr (std::is_same<DesnaFormula, const char*>::value)
			return LogickoI<LevaFormula, Promenljiva>(leva, Promenljiva(desna));
		else
			return LogickoI<LevaFormula, DesnaFormula>(leva, desna);
	}
}


template<typename LevaFormula, typename DesnaFormula>
auto OR(const LevaFormula leva, DesnaFormula desna) {
	if constexpr (std::is_same<LevaFormula, bool>::value) {
		if constexpr (std::is_same<DesnaFormula, bool>::value)
			return LogickoIli<Konstanta, Konstanta>(Konstanta(leva), Konstanta(desna));
		else if constexpr (std::is_same<DesnaFormula, const char*>::value)
			return LogickoIli<Konstanta, Promenljiva>(Konstanta(leva), Promenljiva(desna));
		else
			return LogickoIli<Konstanta, DesnaFormula>(Konstanta(leva), desna);
	}
	else if constexpr (std::is_same<LevaFormula, const char*>::value) {
		if constexpr (std::is_same<DesnaFormula, bool>::value)
			return LogickoIli<Promenljiva, Konstanta>(Promenljiva(leva), Konstanta(desna));
		else if constexpr (std::is_same<DesnaFormula, const char*>::value)
			return LogickoIli<Promenljiva, Promenljiva>(Promenljiva(leva), Promenljiva(desna));
		else
			return LogickoIli<Promenljiva, DesnaFormula>(Promenljiva(leva), desna);
	}
	else {
		if constexpr (std::is_same<DesnaFormula, bool>::value)
			return LogickoIli<LevaFormula, Konstanta>(leva, Konstanta(desna));
		else if constexpr (std::is_same<DesnaFormula, const char*>::value)
			return LogickoIli<LevaFormula, Promenljiva>(leva, Promenljiva(desna));
		else
			return LogickoIli<LevaFormula, DesnaFormula>(leva, desna);
	}
}

template<typename Izraz>
auto NOT(Izraz izraz) {
	if constexpr (std::is_same<Izraz, bool>::value)
		return Negacija<Konstanta>(Konstanta(izraz));
	else if constexpr (std::is_same<Izraz, const char*>::value)
		return Negacija<Promenljiva>(Promenljiva(izraz));
	else
		return Negacija<Izraz>(izraz);
}


int main() {
	// ubacivanje vr u unordered mapu
	Kontekst k1;
	k1["x"] = true;
	k1["y"] = true;
	k1["z"] = false;

	Kontekst k2;
	k2["x"] = true;
	k2["y"] = false;
	k2["z"] = false;

	auto izraz = AND(OR(AND(AND(true, NOT("z")), "x"), "x"), "y");

	bool v1 = izraz.interpretiraj(k1);
	bool v2 = izraz.interpretiraj(k2);

	std::cout << "Vrednost izraza " << izraz << " = " << v1 << " u kontekstu: \n" << k1 << std::endl;
	std::cout << "Vrednost izraza " << izraz << " = " << v2 << " u kontekstu: \n" << k2 << std::endl;

	return 0;
}