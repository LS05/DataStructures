#include <iostream>
#include "hashtable.h"
#include <string>

using namespace std;

int main() {
	mypair<string, int> mp, mp3;
	mypair<string, int> *mp2;
	hashtable<string, int> ht(51);

	mp.first = "ciao";
	mp.second = 22;

	mp3.first = "prova";
	mp3.second = 22;

	ht.inserisci(mp3);
	ht.inserisci(mp);

    ht.stampa();
	return 0;
}
