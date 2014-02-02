#include <iostream>
#include <stdlib.h>

#include "InsiemeLista.h"
#include "InsiemeIter.h"

using namespace std;

typedef int tipoelem;

void riempiInsieme(InsiemeLst<int> &a){
    int j = 0;
    for(j = 0; j < 9; j++){
        int output = rand() % 10;
        a.inserisci(output);
	}
}

int main(int argc, char *argv[]){
	InsiemeLst<int> i, k;
	InsiemeLst<int> *m;

    riempiInsieme(i);
    riempiInsieme(k);

    cout << "Insieme I: ";
    i.stampaInsieme();
    cout << "Insieme K: ";
    k.stampaInsieme();

    m = i.unione(k);
    cout << "Risultato unione: ";
    m->stampaInsieme();

    m = i.intersezione(k);
    cout << "Risultato intersezione: ";
    m->stampaInsieme();

    m = i.differenza(k);
    cout << "Risultato differenza: ";
    m->stampaInsieme();

	return 0;
}
