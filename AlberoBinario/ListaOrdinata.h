//
//  ListaOrdinata.h
//  AlberoBinarioX
//
//  Created by Luca Suriano on 10/10/13.
//  Copyright (c) 2013 Luca Suriano. All rights reserved.
//

#ifndef AlberoBinarioX_ListaOrdinata_h
#define AlberoBinarioX_ListaOrdinata_h
#include "ListaPT.h"

typedef int elemento;

class ListaOrdinata{
public:
    typedef typename ListaPT<int>::posizione pos;

    ListaOrdinata();
    ListaOrdinata(const ListaOrdinata &);
    
    bool inserisci(elemento);
    bool rimuovi(elemento);
    ListaOrdinata fondi(ListaOrdinata &, ListaOrdinata &);
    ListaOrdinata elementiComuni(ListaOrdinata &, ListaOrdinata &);
    
    friend ostream& operator<< (ostream &out, ListaOrdinata &);
private:
    ListaPT<int> mainList;
};

ListaOrdinata::ListaOrdinata(){
    mainList.crealista();
}

ListaOrdinata::ListaOrdinata(const ListaOrdinata &lista){
    ListaPT<int> newList = lista.mainList;
    this->mainList = newList;
}

bool ListaOrdinata::inserisci(elemento e){
    pos p = mainList.primolista();
    if( e < mainList.leggilista(p) ){
        mainList.inslista(e, p);
        return true;
    }else{
        while( !mainList.finelista(p) && e > mainList.leggilista(p) )
            p = mainList.succlista(p);
        mainList.inslista(e, p);
        return true;
    }
}

bool ListaOrdinata::rimuovi(elemento e){
    pos p = mainList.primolista();
    if( mainList.leggilista(p) == e){
        mainList.canclista(p);
        return true;
    }else{
        bool del = false;
        p = mainList.succlista(p);
        while(!mainList.finelista(p) && !del){
            if(e == mainList.leggilista(p)){
                del = true;
                mainList.canclista(p);
            }
            p = mainList.succlista(p);
        }
        return del;
    }
}

ListaOrdinata ListaOrdinata::fondi(ListaOrdinata &S1, ListaOrdinata &S2){
    ListaOrdinata res;
    pos p1 = S1.mainList.primolista();
    pos p2 = S2.mainList.primolista();
    
    while(!S1.mainList.finelista(p1)){
        res.inserisci(S1.mainList.leggilista(p1));
        p1 = S1.mainList.succlista(p1);
    }
    
    while(!S2.mainList.finelista(p2)){
        res.inserisci(S2.mainList.leggilista(p2));
        p2 = S2.mainList.succlista(p2);
    }
    
    return res;
}


ListaOrdinata ListaOrdinata::elementiComuni(ListaOrdinata &S1, ListaOrdinata &S2){
    ListaOrdinata res;
    pos p1 = S1.mainList.primolista();
    pos p2 = S2.mainList.primolista();
    
    while ( !S1.mainList.finelista(p1) ){
        while ( !S2.mainList.finelista(p2) ){
            if( S1.mainList.leggilista(p1) == S2.mainList.leggilista(p2) )
                res.inserisci(S1.mainList.leggilista(p1));
            p2 = S2.mainList.succlista(p2);
        }
        p2 = S2.mainList.primolista();
        p1 = S1.mainList.succlista(p1);
    }
    
    return res;
}

ostream& operator<< (ostream &out, ListaOrdinata &list){
    return cout << list.mainList;
}

#endif