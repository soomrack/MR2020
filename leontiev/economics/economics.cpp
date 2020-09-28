#include <iostream>
#include <math.h>

int main() {
	int dohod;
	std::cout << "Vvedite dohod: ";
	std::cin >> dohod;
	float ipoteka;
	std::cout << "\nVvedite ipoteku: ";
	std::cin >> ipoteka;
	int month;
	std::cout << "\nVvedite kol-vo mesyatsev: ";
	std::cin >> month;
	int nachkap;
	std::cout << "\nVvedite nachalniy kapital: ";
	std::cin >> nachkap;
	float procVk;
	std::cout << "\nVvedite procent vklada: ";
	std::cin >> procVk;
	procVk = procVk / 100;
	float procIp;
	std::cout << "\nVvedite procent Ipoteki: ";
	std::cin >> procIp;
	procIp = procIp / 100;
	float procKv;
	std::cout << "\nVvedite procent rosta kvartiri: ";
	std::cin >> procKv;
	procKv = procKv / 100;
	int kvart;
	kvart = nachkap + ipoteka;
	float dohodVk; float dohodKv; float kap1; float kap2;
	kap1 = nachkap;
	for (int i = 1; i <= month; i++) {
		kap1 = kap1 * (1 + procVk);
		kap1 = kap1 + dohod;
	}
	dohodVk = kap1 - nachkap;
	std::cout << "Dohod s vklada - " << dohodVk<<", ";
	kap2 = kvart;
	kap2 = kap2 *pow( (1 + procKv) ,month);
	ipoteka = ipoteka * pow((1 + procIp) , month);
	dohodKv = kap2 - ipoteka + dohod * month;
	std::cout << "Dohod s kvartiri - " << dohodKv<<".";
	if (dohodVk > dohodKv) std::cout << "Vklad vigodnee";
	else std::cout << "Pokupka kvartiri vigodnee";

	return 0;
}