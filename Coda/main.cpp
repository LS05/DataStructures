#include <iostream>

#include "CodaPT.h"
#include "CodaVT.h"

using namespace std;

int main() {
	CodaVT<int> c, b;

	c.inCoda(2);
	c.inCoda(20);
	c.inCoda(72);
	c.inCoda(11);
	c.inCoda(40);

	cout << c;

	b = c;

	(b == c) ? cout << "VERO" : cout << "FALSO";

    cout << endl;

	CodaPT<string> cs;
	cs.inCoda("luca");
	cs.inCoda("e'");
	cs.inCoda("di");
	cs.inCoda("andria");

	cs.fuoriCoda();

	cout << cs;

	return 0;
}
