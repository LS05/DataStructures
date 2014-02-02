#include <iostream>

using namespace std;

#include "PilaVT.h"
#include "PilaPT.h"

int main() {
	PilaVT<string> p, p3;
	PilaPT<int> p_int;

	p.inPila("luca");
	p.inPila("e'");
	p.inPila("di");
	p.inPila("Andria");
	p.inPila("ciao");
	cout << p;
	p_int.inPila(10);
	p_int.inPila(20);
	p_int.inPila(30);
	cout<< p_int;

	PilaVT<string> p2;
	p2.inPila("luca");
    p2.inPila("e'");
	p2.inPila("di");
	p2.inPila("Andria");
	p2.inPila("ciao");

	p3 = p;

	(p3 == p) ? cout << "VERO" : cout << "FALSO";
	return 0;
}
