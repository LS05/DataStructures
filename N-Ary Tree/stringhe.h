//
//  stringhe.h
//  AlberoNArioX
//
//  Created by Luca Suriano on 11/09/13.
//  Copyright (c) 2013 Luca Suriano. All rights reserved.
//

#ifndef AlberoNArioX_stringhe_h
#define AlberoNArioX_stringhe_h
#include "StringES.h"
#include "PrioriCoda.h"

class stringhe {
public:
    /* inserisce una stringa nella collezione */
	void inserisci(StringES &a);
	/* restituisce il numero di stringhe nella collezione*/
	int lunghezza();
    /* visualizza le stringhe in S ordinate rispetto alla loro lunghezza */
    void visualizza_lunghezza();
    /* visualizza l'istogramma dei caratteri utilizzati in S */
    void istogramma();
private:
    CodaP<StringES> mainCol;
};

void stringhe::inserisci(StringES &a){
    this->mainCol.inserisci(a);
}

#endif
