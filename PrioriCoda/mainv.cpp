#include <iostream>
using namespace std;
#include "codap.h"

typedef int tipoelem;

int main()
{
	CodaP<int> miacoda;
	tipoelem x;
	int sc = 0;
	miacoda.creaPrioriCoda();
	while (sc<9)
	{
		cout << "(1) inserisci" << endl;
		cout << "(2) mostra minimo" << endl;
		cout << "(3) cancella minimo " << endl;
		cout << "(9) esci\n" << endl;
		cin >> sc;

		switch (sc)
		{
		case 1:
			cout << "che elemento? "; cin >> x; cout << endl;
			miacoda.inserisci(x);
			break;
		case 2:
			cout << "il minimo e' :" << miacoda.min() << endl;
			break;
		case 3:
			miacoda.cancellaMin();
			break;
		};
	};

	system("pause");
	return 0;

}
