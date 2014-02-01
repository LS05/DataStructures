#include <iostream>
#include <string>
#include "pair.h"
#include "dizionario.h"

using namespace std;

int main() {
	Dizionario<string, int> ht(51);
    ht.inserisci("luca", 20);
    ht.inserisci("luca", 30);
    ht.stampa();
	return 0;
}
