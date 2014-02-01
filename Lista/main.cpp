#include <iostream>

#include "ListaVT.h"
#include "ListaPT.h"

using namespace std;

ListaPT<int> addLista(){
    ListaPT<int> temp;
    temp.inslista(70, temp.primolista());
    return temp;
}

template < class T >
class listaOrdinata{
public:
    typedef T tipoelem;
    typedef typename ListaPT<T>::posizione pos;

    listaOrdinata();
    listaOrdinata(const listaOrdinata<T> &);

    void inserisci(tipoelem);
    void rimuovi(tipoelem);
    listaOrdinata<T> fondi(listaOrdinata<T> &ls2);
    listaOrdinata<T> elementiComuni(listaOrdinata<T> &ls2);

    template <class Y>
	friend ostream& operator<< (ostream &out, listaOrdinata<Y> &lista);
private:
    ListaPT<T> lista;
};

template < class T >
listaOrdinata<T>::listaOrdinata(){

}

template < class T >
listaOrdinata<T>::listaOrdinata(const listaOrdinata<T> &ls){
    this->lista = ls.lista;
}

template < class T >
void listaOrdinata<T>::inserisci(tipoelem e){
    pos p = this->lista.primolista();
    bool flag = true;

    while(!this->lista.finelista(p) && flag){
        tipoelem el = lista.leggilista(p);
        if ( el > e)
            flag = false;
        if(flag)
            p = this->lista.succlista(p);
    }

    this->lista.inslista(e, p);
}

template < class T >
void listaOrdinata<T>::rimuovi(tipoelem e){
    pos p = this->lista.primolista();
    bool flag = false;

    while(!this->lista.finelista(p) && !flag){
        tipoelem el = lista.leggilista(p);
        if ( el == e)
            flag = true;
        p = this->lista.succlista(p);
    }

    if(flag)
        this->lista.canclista(e, p);
}

template < class T >
listaOrdinata<T> listaOrdinata<T>::fondi(listaOrdinata<T> &ls2){
    listaOrdinata<T> ls;

    pos p = this->lista.primolista();

    while(!this->lista.finelista(p)){
        tipoelem el = this->lista.leggilista(p);
        ls.inserisci(el);
        p = this->lista.succlista(p);
    }

    p = ls2.lista.primolista();

    while(!ls2.lista.finelista(p)){
        tipoelem el = ls2.lista.leggilista(p);
        ls.inserisci(el);
        p = ls2.lista.succlista(p);
    }


    return ls;
}


template < class T >
listaOrdinata<T> listaOrdinata<T>::elementiComuni(listaOrdinata<T> &ls2){
    listaOrdinata<T> ls;
    pos p = this->lista.primolista();
    pos p2 = ls2.lista.primolista();
    bool flag = false;

    while(!this->lista.finelista(p)){
        tipoelem el = this->lista.leggilista(p);

        while(!ls2.lista.finelista(p2) && !flag){
            if(el == ls2.lista.leggilista(p2))
                flag = true;
            p2 = ls2.lista.succlista(p2);
        }

        if(flag){
            ls.inserisci(el);
            flag = false;
        }

        p = this->lista.succlista(p);
        p2 = ls2.lista.primolista();
    }

    return ls;
}

template <class Y>
ostream& operator<< (ostream &out, listaOrdinata<Y> &ls){
    out << ls.lista;
}


void testOrdinata(){
    listaOrdinata<int> ls1, ls2;

    ls1.inserisci(4);
    ls1.inserisci(2);
    ls1.inserisci(1);
    ls1.inserisci(5);
    ls1.inserisci(9);

    ls2.inserisci(4);
    ls2.inserisci(2);
    ls2.inserisci(0);
    ls2.inserisci(5);
    ls2.inserisci(9);

    cout << "LS1: " << ls1;
    cout << "LS2: " << ls2;

    listaOrdinata<int> ls3 = ls1.elementiComuni(ls2);

    cout << "LS3: " << ls3;
}


void split(ListaPT<char> &mlista, int k, ListaPT<char> &S1, ListaPT<char> &S2){
    typedef ListaPT<char>::posizione pos;
    pos p = mlista.primolista();
    int i = 0;

    while(i < k && !mlista.finelista(p)){
        S1.inslista(mlista.leggilista(p), S1.primolista());
        i++;
        p = mlista.succlista(p);
    }

    while(!mlista.finelista(p)){
        S2.inslista(mlista.leggilista(p), S2.primolista());
        p = mlista.succlista(p);
    }
}

ListaPT<char> crossover(ListaPT<char> &S1, ListaPT<char> &S2, int k, int t){
    int i = 0, j = 0;
    ListaPT<char> res;
    ListaPT<char>::posizione p = S1.primolista();
    ListaPT<char>::posizione q = S2.ultimolista();

    while(i < k && !S1.finelista(p)){
        res.inslista(S1.leggilista(p), res.primolista());
        i++;
        p = S1.succlista(p);
    }

    while(j < t && !S2.finelista(q)){
        res.inslista(S2.leggilista(q), res.primolista());
        j++;
        q = S2.predlista(q);
    }

    return res;
}

void esSplit(){
    ListaPT<char> mainList, S1, S2;
    char alph[5] = { 'a', 'b', 'c', 'd', 'e' };

    for(int i = 0; i < 20; i++){
        char c = alph[rand() % 5];
        mainList.inslista(c, mainList.primolista());
    }

    cout << mainList;

    split(mainList, 5, S1, S2);

    cout << "S1: " << S1;
    cout << "S2: " << S2;

    ListaPT<char> crov;

    crov = crossover(S1, S2, 4, 6);

    cout << "Crossover" << crov;
}


int main() {
    testOrdinata();
    esSplit();
    ListaVT<int> list1, list2, list3;
//  ListaVT<int> list1;

    int x;

    x = 1;
    list1.inslista(x, list1.primolista());
    x = 2;
    list1.inslista(x, list1.primolista());
    x = 3;
    list1.inslista(x, list1.primolista());
    x = 4;
    list1.inslista(x, list1.primolista());

    cout << list1;

    cout << "Dimensione della lista: " << list1.size() << endl;

    cout << "ultimo elemento: " << list1.ultimolista();

    x = 1;
    list2.inslista(x, list2.primolista());
    x = 2;
    list2.inslista(x, list2.primolista());
    x = 3;
    list2.inslista(x, list2.primolista());
    x = 5;
    list2.inslista(x, list2.primolista());

    list3 = list1;
    (list1 == list2) ? cout << "true" : cout << "false" << endl;


}
