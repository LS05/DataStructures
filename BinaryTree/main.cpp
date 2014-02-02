#include <iostream>

#include "BinTreeC.h"
#include "BinTreePT.h"
#include "UtilTree.h"
#include "OETList.h"

using namespace std;

typedef int tipoelem;

typedef BinTreePT<tipoelem> BinAlbero;
typedef BinTreePT<tipoelem>::Nodo nodo;

bool sameNodes(BinAlbero &treeOne, BinAlbero &treeTwo, nodo n1, nodo n2){
    bool flag = true;
    if (n1 == NULL && n2 == NULL){
        return true;
    }else if(n1 != NULL && n2 != NULL){
        return (
                treeOne.read(n1) == treeOne.read(n2) &&
                sameNodes(treeOne, treeTwo, treeOne.sx(n1), treeTwo.sx(n2)) &&
                sameNodes(treeOne, treeTwo, treeOne.dx(n1), treeTwo.dx(n2))
        );
    }
    return flag;
}

bool sameTree(BinAlbero&treeOne, BinAlbero&treeTwo){
    return sameNodes(treeOne, treeTwo, treeOne.root(), treeTwo.root());
}

int numberOfLeavesNodes(BinAlbero &tree, nodo n){
    int count = 0;
    if (n != NULL){
        if(tree.isleaf(n)){
            count ++;
        }
        if (!tree.sx_empty(n))
            count += numberOfLeavesNodes(tree, tree.sx(n));

        if (!tree.dx_empty(n))
            count += numberOfLeavesNodes(tree, tree.dx(n));
    }
    return count;
}

bool isFull(BinAlbero &tree, nodo n){
    bool flag = true;
    if (n != NULL && (!tree.isleaf(n))){
        if (!tree.sx_empty(n))
			flag = isFull(tree, tree.sx(n));
        else
            flag = false;
		if (!tree.dx_empty(n) && flag != false)
			flag = isFull(tree, tree.dx(n));
        else
            flag = false;
	}
    return flag;
}


int somma(BinAlbero &T, nodo n){
    int s = T.read(n);

    if(!T.sx_empty(n))
        s += somma(T, T.sx(n));
    if(!T.dx_empty(n))
        s += somma(T, T.dx(n));

    return s;
}

int somma(BinAlbero &T){
    return somma(T, T.root());
}

int sommaLivello(BinAlbero &T, nodo n, int lev){
    if(lev == 0){
        return T.read(n);
    }else{
        return (sommaLivello(T, T.sx(n), lev - 1) + sommaLivello(T, T.dx(n), lev - 1));
    }
}

int sommaLivello(BinAlbero &T, int lev){
    return sommaLivello(T, T.root(), lev);
}

int sumTree(BinAlbero &T, nodo n){
    if( n == NULL )
        return 0;
    else
        return (T.read(n) + sumTree(T, T.sx(n)) + sumTree(T, T.dx(n)));

}

void setValue(BinAlbero &T, nodo n){
    if( n == NULL )
        return;
    else{
        int a = sumTree(T, n);
        T.write(n, a);
        setValue(T, T.sx(n));
        setValue(T, T.dx(n));
    }
}

BinAlbero specchia(BinAlbero &T, nodo n){
    BinAlbero res;
    res.ins_root(n);
}

void specchia(BinAlbero &T){
    specchia(T, T.root());
}



void pesa(BinAlbero &T){
    setValue(T, T.root());
}

int contaNodi(BinAlbero &T, nodo n, int lev){
    if ( lev == 0 )
        return 1;
    else{
        int s = (contaNodi(T, T.sx(n), lev - 1) + contaNodi(T, T.dx(n), lev - 1));
        return s;
    }
}


int contaNodi(BinAlbero &T, int lev){
    return contaNodi(T, T.root(), lev);
}

void nodi_livello(BinAlbero &T, nodo n, int lev, ListaPT<int> &ls){
    if ( lev == 0 )
        ls.inslista(T.read(n), ls.primolista());
    else{
        nodi_livello(T, T.sx(n), lev - 1, ls);
        nodi_livello(T, T.dx(n), lev - 1, ls);
    }
}

int media_livello(BinAlbero &T, int lev){
    int sum = 0;
    ListaPT<int> listaNodi;
    nodi_livello(T, T.root(), lev, listaNodi);
    ListaPT<int>::posizione p = listaNodi.primolista();
    while (!listaNodi.finelista(p)){
        sum += listaNodi.leggilista(p);
        p = listaNodi.succlista(p);
    }

    return sum / listaNodi.size();
}

typedef int somma_elementi;
typedef int conta_elementi;

pair<somma_elementi, conta_elementi> mediaLivello(BinAlbero &T, nodo n, int lev){
    if( lev == 0 )
        return (make_pair(T.read(n), 1));
    else{
        pair<int, int> sx = mediaLivello(T, T.sx(n), lev - 1);
        pair<int, int> dx = mediaLivello(T, T.dx(n), lev - 1);
        return (make_pair(sx.first + dx.first, sx.second + dx.second));
    }
}

double mediaLivello(BinAlbero &T, int lev){
    pair<int, int> res = mediaLivello(T, T.root(), lev);
    return res.first / res.second;
}

pair<somma_elementi, conta_elementi> mediaFoglie(BinAlbero &T, nodo n){
    if( T.sx_empty(n) && T.dx_empty(n) )
        return (make_pair(T.read(n), 1));
    else{
        pair<int, int> sx(0, 0), dx(0, 0);
        if( !T.sx_empty(n) )
            sx = mediaFoglie(T, T.sx(n));
        if( !T.dx_empty(n) )
            dx = mediaFoglie(T, T.dx(n));
        return (make_pair(sx.first + dx.first, sx.second + dx.second));
    }
}

double mediaFoglie(BinAlbero &T){
    pair<int, int> res = mediaFoglie(T, T.root());
    return res.first / res.second;
}

int altezza(BinAlbero &tree, nodo n){
    int lh = 0, rh = 0;
    if ( tree.isleaf(n) ) {
        return 0;
    } else {
        if(!tree.sx_empty(n))
            lh = altezza(tree, tree.sx(n));
        if(!tree.dx_empty(n))
            rh = altezza(tree, tree.dx(n));
        return 1 + max( lh, rh);
    }
}

//ListaOrdinata esListe(){
//    ListaOrdinata ls;
//    ls.inserisci(10);
//    ls.inserisci(5);
//    ls.inserisci(29);
//    ls.inserisci(2);
//    ls.inserisci(1);
//    ls.inserisci(8);
//    ls.inserisci(58);
//
//    ListaOrdinata ls2;
//    ls2.inserisci(1);
//    ls2.inserisci(54);
//    ls2.inserisci(29);
//    ls2.inserisci(43);
//    ls2.inserisci(81);
//    ls2.inserisci(1);
//    ls2.inserisci(58);
//
//    cout << "Lista 1: " << ls;
//    cout << "Lista 2: " << ls2;
//
//    ListaOrdinata ls3;
//    ls3 = ls.elementiComuni(ls, ls2);
//
//    cout << "Lista 3: " << ls3;
//
//    return ls3;
//}

int odd(BinAlbero &tree, nodo n, int lev){
    int sum = 0;

    if(lev == 0){
        if(tree.read(n) % 2 == 1)
            sum = 1;
        else
            sum = 0;
    } else {
        if(!tree.sx_empty(n))
            sum += odd(tree, tree.sx(n), lev - 1);
        if(!tree.dx_empty(n))
            sum += odd(tree, tree.dx(n), lev - 1);
    }

    return sum;
}

int odd(BinAlbero &tree, int k){
    return odd(tree, tree.root(), k);
}

int even_leafs(BinAlbero &tree, nodo n){
    int sum = 0;

    if( tree.isleaf(n) ){
        if( tree.read(n) % 2 == 0)
            sum = 1;
        else
            sum = 0;
    }else{
        if(!tree.sx_empty(n))
            sum += even_leafs(tree, tree.sx(n));
        if(!tree.dx_empty(n))
            sum += even_leafs(tree, tree.dx(n));
    }

    return sum;
}

int even_leafs(BinAlbero &tree){
    return even_leafs(tree, tree.root());
}

int leafs_with_even_parent(BinAlbero &tree, nodo n){
    int sum = 0;

    if(tree.isleaf(n)){
        if(tree.read(tree.parent(n)) % 2 == 0)
            sum = 1;
        else
            sum = 0;
    }else{
        if(!tree.sx_empty(n))
            sum += leafs_with_even_parent(tree, tree.sx(n));
        if(!tree.dx_empty(n))
            sum += leafs_with_even_parent(tree, tree.dx(n));
    }

    return sum;
}

int leafs_with_even_parent(BinAlbero &tree){
    return leafs_with_even_parent(tree, tree.root());
}


/*
    You have a binary tree.
    Print node values starting from the root going level by level,
    i.e. first line has root node's value, second line has two child
    node's values, third line - left and right child nodes values of
    the root's left child then left and right child nodes values of
    the root's right child, and so on.
 */

void printLev(BinAlbero &tree, nodo n, int lev){
    if( lev == 0 ){
        cout << tree.read(n) << " ";
    } else {
        if( !tree.sx_empty(n) )
            printLev(tree, tree.sx(n), lev - 1);
        if( !tree.dx_empty(n) )
            printLev(tree, tree.dx(n), lev - 1);
    }
}

void printLev(BinAlbero &tree){
    int h = altezza(tree, tree.root());
    for(int i = 0; i <= h; i++){
        cout << "Livello " << i << ": ";
        printLev(tree, tree.root(), i);
        cout << endl;
    }
}

class Paziente{
public:
    Paziente(){ }
    Paziente(int nProg){
        this->nProg = nProg;
    }
private:
    int nProg;
};

class Visita{
public:
    Visita();
    void insPaziente(string tipoInt, Paziente &paz);
    int getTotal();
    int getTotaleTipologia(string tipoInt);
private:
    ListaPT<Paziente> *vetPaz[3];
};


Visita::Visita(){
    for(int i = 0; i < 3; i++){
        vetPaz[i] = new ListaPT<Paziente>();
    }
}

void Visita::insPaziente(string tipoInt, Paziente &paz){
    if( tipoInt == "medicazione" ){
        vetPaz[0]->inslista(paz, vetPaz[0]->primolista());
    }
    if( tipoInt == "intervento" ){
        vetPaz[1]->inslista(paz, vetPaz[1]->primolista());
    }
    if( tipoInt == "generica" ){
        vetPaz[2]->inslista(paz, vetPaz[2]->primolista());
    }
}


int Visita::getTotal(){
    int s = 0;
    for(int i = 0; i < 3; i++){
        s += vetPaz[i]->size();
    }
    return s;
}
int Visita::getTotaleTipologia(string tipoInt){
    if( tipoInt == "medicazione" ){
        return vetPaz[0]->size();
    }
    if( tipoInt == "intervento" ){
        return vetPaz[1]->size();
    }
    if( tipoInt == "generica" ){
        return vetPaz[2]->size();
    }
}

void esercizioMedici(){
Visita medico1;
    Visita medico2;
    Visita medico3;

    Visita * vetMed[3] {&medico1, &medico2, &medico3};
    string tipoInt[3] { "medicazione", "intervento", "generica"};
    int j = 0;

    for(int i = 0; i < 200; i++){
        int med = rand() % 3;
        int motivo = rand() % 3;
        Paziente paz(i);
        vetMed[med]->insPaziente(tipoInt[motivo], paz);
    }

    for(j = 0; j < 3; j++)
        cout << "Numero pazienti medico " << j + 1 << ": " << vetMed[j]->getTotal() << endl;

    for(j = 0; j < 3; j++){
        cout << endl << "Medico" << j + 1 << endl;
        for(int k = 0; k < 3; k++){
            cout << "Tipo Intervento: " << tipoInt[k];
            cout << " Totale: " << vetMed[j]->getTotaleTipologia(tipoInt[k]);
            cout << endl;
        }
    }

    cout << endl;

    for(j = 0; j < 3; j++){
        int s = 0;
        cout << "Tipo Intervento: " << tipoInt[j];
        for(int k = 0; k < 3; k++){
            s += vetMed[k]->getTotaleTipologia(tipoInt[j]);
        }
        cout << " Totale: " << s << endl;
    }
}

int main() {
	BinTreePT<int> alberoBin;
	BinTreePT<int>::Nodo n1, n2;
	UtilTree<int> utTree(alberoBin);

    OETList<int, BinTreePT<int>::Nodo> oetList;

    esercizioMedici();

//    ListaOrdinata res = esListe();
//
//    cout << "Lista Res: " << res;

	alberoBin.ins_root(n1);
	alberoBin.write(alberoBin.root(),1);
	n1 = alberoBin.root();
	alberoBin.ins_sx(n1);
	alberoBin.ins_dx(n1);
	alberoBin.write(alberoBin.sx(n1),2);
	n1 = alberoBin.dx(n1);
	alberoBin.write(n1, 3);
	alberoBin.ins_dx(n1);
	alberoBin.write(alberoBin.dx(n1), 7);
    n1 = alberoBin.sx(alberoBin.root());
    alberoBin.ins_sx(n1);
    alberoBin.write(alberoBin.sx(n1), 8);
    alberoBin.ins_dx(n1);
    alberoBin.write(alberoBin.dx(n1), 9);
	alberoBin.print();

    printLev(alberoBin);

    int lev = 2;

    cout << "Numero nodi dispari a livello " << lev << ": " << odd(alberoBin, lev) << endl;

    leafs_with_even_parent(alberoBin);


/*
    utTree.swapTree();

    mediaFoglie(alberoBin);

    cout << "La somma è: " << somma(alberoBin);

    oetList.analyze(alberoBin);

    oetList.showLists();

    cout << "Altezza albero: " << altezza(alberoBin, alberoBin.root()) << endl;

    BinTreePT<int> T2;

    T2.ins_root(n2);
	T2.write(T2.root(),1);
	n2 = T2.root();
	T2.ins_sx(n2);
	T2.ins_dx(n2);
	T2.write(T2.sx(n2),2);
	n2 = T2.dx(n2);
	T2.write(n2, 3);
    T2.ins_sx(n2);
	T2.write(T2.sx(n2), 7);
	T2.ins_dx(n2);
	T2.write(T2.dx(n2), 12);
    n2 = T2.sx(T2.root());
    T2.ins_sx(n2);
    T2.write(T2.sx(n2), 9);
    T2.ins_dx(n2);
    T2.write(T2.dx(n2), 8);
	T2.print();


//	cout << "Albero T: " << T << endl;

    cout << "Preoder: ";
    alberoBin.preorder(alberoBin.root());
    cout << endl;

    cout << "Postorder: ";
    alberoBin.postorder(alberoBin.root());
    cout << endl;

    cout << "Inorder: ";
    alberoBin.inorder(alberoBin.root());
    cout << endl;

    cout << "BFS: ";
    alberoBin.BFS(alberoBin.root());
    cout << endl;

//    cout << "Altezza: " << utTree.altezza(T.root()) << endl;
//
//    ListaPT<int> res = utTree.levelNodes(3);
//    cout << res;
//
//    bool r = isFull(T, T.root());
//
//    (r == true) ? cout << "vero\n" : cout << "falso\n";
//
//    cout << "Numero FOGLIE: " <<numberOfLeavesNodes(T, T.root()) << "\n";
//
//    bool r2 = sameTree(T, T2);
//    (r2 == true) ? cout << "vero: stesso albero\n" : cout << "falso: albero diverso\n";


    // cout << "Somma a livello 0: " << sommaLivello(alberoBin, 0) << endl;



    // pesa(alberoBin);

    cout << "Numero nodi a livello 2: " << contaNodi(alberoBin, 2) << endl;

    alberoBin.print();
 */


}
