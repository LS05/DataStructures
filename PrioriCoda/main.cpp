#include <stdlib.h>
#include <iostream>

#include "PrioriCoda.h"

using namespace std;

int main()
{
	CodaP<char> miacoda;
	miacoda.creaPrioriCoda();
	miacoda.inserisci('a');
	miacoda.inserisci('d');
	miacoda.inserisci('b');
	miacoda.inserisci('t');
	miacoda.inserisci('c');

	cout << miacoda;

	cout << miacoda.min() << endl;

	miacoda.cancellaMin();

	cout << miacoda.min();

	return 0;
}
