#include "TreePT.h"
#include "NodoPtr.h"
#include "CodaPT.h"
#include "linear_list.h"
#include "ListaPT.h"
#include "MediaTree.h"

#include <vector>

using namespace std;

typedef TreePT<int> albero;

typedef TreePT<int>::node nodo;

/*
 getHeight
 - Restituisce l'altezza del nodo n
 */

int getHeight(albero &tree, nodo n){
    int max = 0, temp = 0;
    if(tree.leaf(n))
        return 0;
    else{
        nodo v = tree.firstChild(n);
        max = 0;
        while(!tree.lastSibling(v)){
            temp = getHeight(tree, v);
            if(max <= temp)
                max = temp;
            v = tree.nextSibling(v);
        }
        return max + 1;
    }

}

/*
 larghezza
 - Restituisce la larghezza dell'albero
 */

void getLevelWidth(albero &tree, nodo n, int levelFreqs[], int depth) {
    if (n == NULL)
        return;

    levelFreqs[depth]++;


    while (n != NULL){
        getLevelWidth(tree, tree.firstChild(n), levelFreqs, depth + 1);
        n = tree.nextSibling(n);
        if(n != NULL)
            levelFreqs[depth]++;
    }

}

//int larghezza(albero &tree, nodo n){
//    int h = getHeight(tree, tree.root());
//    int* maxLev = new int[h]();
//
//    getLevelWidth(tree, tree.root(), maxLev, 0);
//
//    return *max_element(maxLev, maxLev + h + 1);
//}

int larghezza(albero &tree, nodo n, int lev){
    int largh = 0;

    if(lev == 0)
        largh = 1;
    else{
        n = tree.firstChild(n);

        while(!tree.lastSibling(n)){
            largh += larghezza(tree, n, lev - 1);
            n = tree.nextSibling(n);
        }

        largh += larghezza(tree, n, lev - 1);
    }

    return largh;
}


int larghezza(albero &tree, nodo n){
    int h = getHeight(tree, tree.root());
    int max = 0, temp = 0;

    for(int i = 0; i <= h; i++){
        temp = larghezza(tree, tree.root(), i);
        if(max < temp)
            max = temp;
    }

    return max;
}
/* -------- fine larghezza --------- */

/*
 somma
 - Effettua la somma dell'albero
 */

int somma(albero &tree, nodo n){
    int sum = 0;

    if( tree.leaf(n) ){
        return tree.readNode(n);
    }else{
        sum += tree.readNode(n);
        n = tree.firstChild(n);
        while (!tree.lastSibling(n)){
            sum += somma(tree, n);
            n = tree.nextSibling(n);
        }
        sum += somma(tree, n);
    }

    return sum;
}

int somma(albero &tree){
    return somma(tree, tree.root());
}

/*
 sommaLev
 - Restituisce la somma dei nodi a livello lev
 */

int sommaLevSup(albero &tree, nodo n, int lev){
    int sum = 0;

    if( lev == 0 )
        return tree.readNode(n);
    else{
        n = tree.firstChild(n);
        while ( !tree.lastSibling(n) ){
            sum += sommaLevSup(tree, n, lev - 1);
            n = tree.nextSibling(n);
        }

        sum += sommaLevSup(tree, n, lev - 1);
    }

    return sum;
}

int sommaLev(albero &tree, int lev){
    return sommaLevSup(tree, tree.root(), lev);
}

/* -------------- sommaLev --------------- */

/*
 pesa
 - Restituisce una albero T', ottenuto da T, eliminando tutti i nodi che sono radici di
 sottoalberi contenti l'intero k.
 */

int sumTree(albero &tree, nodo n, nodo root){
    int sum = 0;
    bool rad = false;

    if( n == NULL )
        return 0;
    else{
        while ( n != NULL && !rad){
            sum += tree.readNode(n);
            sum += sumTree(tree, tree.firstChild(n), root);
            if(n != root)
                n = tree.nextSibling(n);
            else
                rad = true;
        }
    }

    return sum;
}

void pesaSupp(albero &tree, nodo n){
    if( n == NULL )
        return;
    else{
        while (n != NULL){
            int val = sumTree(tree, n, n);
            tree.writeNode(n, val);
            pesaSupp(tree, tree.firstChild(n));
            n = tree.nextSibling(n);
        }
    }
}

void pesa(albero &tree){
    pesaSupp(tree, tree.root());
}

/*
 mediaLivello
 - Calcola e restituisce la media a livello k dell'albero
 */

typedef pair<double, int> sommamedia;

sommamedia mediaLivello(albero &tree, nodo n, int lev){
    pair<double, int> mlvl, res;

    if( lev == 0 ){
        return make_pair(tree.readNode(n), 1);
    } else {
        n = tree.firstChild(n);
        while(!tree.lastSibling(n)){
            res = mediaLivello(tree, n, lev - 1);
            mlvl.first += res.first;
            mlvl.second += res.second;
            n = tree.nextSibling(n);
        }
        res = mediaLivello(tree, n, lev - 1);
        mlvl.first += res.first;
        mlvl.second += res.second;
    }

    return mlvl;
}

double mediaLivello(albero &tree, int lev){
    pair<double, int> mlvl;
    mlvl = mediaLivello(tree, tree.root(), lev);
    return mlvl.first / mlvl.second;
}

/*--------------- fine mediaLivello ------------ */


int sommaAlbero(albero &tree, nodo n){
    int sum = tree.readNode(n);

    if( tree.leaf(n) )
        return sum;
    else{
        n = tree.firstChild(n);
        while (! tree.lastSibling(n) ){
            sum += sommaAlbero(tree, n);
            n = tree.nextSibling(n);
        }
        sum += sommaAlbero(tree, n);
    }
    return sum;
}

/*
 dispari
 - Restituisce tutti i nodi radici di sottoalberi la cui somma è dispari.
 */

void dispari(albero &tree, nodo n, CodaPT<nodo> &coda){
    if( tree.leaf(n) ){
        if(tree.readNode(n) % 2 == 1)
            coda.inCoda(n);
    } else {
        int sum = sommaAlbero(tree, n);

        if( sum % 2 == 1 )
            coda.inCoda(n);

        n = tree.firstChild(n);

        while(!tree.lastSibling(n) ){
            dispari(tree, n, coda);
            n = tree.nextSibling(n);
        }

        dispari(tree, n, coda);
    }
}

CodaPT<nodo> dispari(albero &tree){
    CodaPT<nodo> cn;
    if( !tree.empty() )
        dispari(tree, tree.root(), cn);
    cout << endl << cn;
    return cn;
}

/* ---------------- fine dispari -------------- */

/*
 pota
 - Restituisce una albero T', ottenuto da T, eliminando tutti i nodi che sono radici di
   sottoalberi contenti l'intero k.
 */

bool findNode(albero &tree, nodo n, int k){
    bool flag = false;

    if( tree.leaf(n) )
        return (tree.readNode(n) == k);
    else if( tree.readNode(n) == k )
        return true;
    else {
        n = tree.firstChild(n);
        while( !tree.lastSibling(n) && !flag){
            flag = findNode(tree, n, k);
            n = tree.nextSibling(n);
        }
        if( !flag )
            flag = findNode(tree, n, k);
    }

    return flag;
}

void pota(albero &tree, nodo n, int k){
    while(n != NULL){
        if(findNode(tree, n, k))
            tree.removeSubTree(n);
        pota(tree, tree.firstChild(n), k);
        n = tree.nextSibling(n);
    }
}


void pota(albero &tree, int k){
    pota(tree, tree.root(), k);
}

/* ---------------- fine pota -------------- */

/*
 media
 - Restituisce la media per ogni livello dell'albero
 */

pair<int, int> media(albero &tree, nodo n, int lev){
    if( lev == 0 )
        return make_pair(tree.readNode(n), 1);
    else{
        n = tree.firstChild(n);
        pair<int, int> ms, res;
        while( !tree.lastSibling(n) ){
            ms = media(tree, n, lev - 1);
            res.first += ms.first;
            res.second += ms.second;
            n = tree.nextSibling(n);
        }
        ms = media(tree, n, lev - 1);
        res.first += ms.first;
        res.second ++;
        return res;
    }
}

double media(albero &tree, int lev){
    pair<int, int> res = media(tree, tree.root(), lev);
    double med = (double)res.first / (double)res.second;
    return med;
}


double media(albero &tree){
    int maxLev = getHeight(tree, tree.root());
    cout << endl;
    for(int i = 0; i <= maxLev; i++){
        double med = media(tree, i);
        cout << "Media a livello " << i << ": " << med << endl;
    }
}

/* -------------- fine media ------------- */

/*
 pari
 - Restituisce tutti i nodi radici di sottoalberi la cui somma è pari
 */
void pari(albero &tree, nodo n, CodaPT<nodo> &cn){
    if( tree.leaf(n) ){
        if(tree.readNode(n) % 2 == 0)
            cn.inCoda(n);
    }else{
        int s = somma(tree, n);
        if( s % 2 == 0)
            cn.inCoda(n);

        n = tree.firstChild(n);

        while( !tree.lastSibling(n) ){
            pari(tree, n, cn);
            n = tree.nextSibling(n);
        }

        pari(tree, n, cn);
    }
}


void pari(albero &tree){
    CodaPT<nodo> cn;
    pari(tree, tree.root(), cn);

    cout << "Nodi radici di sottoalberi con somma pari: ";

    while (! cn.codaVuota()){
        cout << tree.readNode(cn.leggiCoda()) << " ";
        cn.fuoriCoda();
    }

    cout << endl;
}

/* ---------------- fine pari -------------- */

/*
 even_leafs
 - calcola e restituisce il numero di foglie il cui valore e' pari.
*/

int even_leafs(albero &tree, nodo n){
    int sum = 0;

    if( tree.leaf(n) ){
        if (tree.readNode(n) % 2 == 0)
            sum = 1;
        else
            sum = 0;
    } else {
        n = tree.firstChild(n);
        while (!tree.lastSibling(n)){
            sum += even_leafs(tree, n);
            n = tree.nextSibling(n);
        }
        sum += even_leafs(tree, n);
    }

    return sum;
}

int even_leafs(albero &tree){
    return even_leafs(tree, tree.root());
}

/* ------------------- fine even_leafs -------------------- */


/*
 leafs_with_even_parent

 - Calcola e restituisce il numero di foglie che hanno come genitore un nodo il
   cui valore e' pari.
*/

int leafs_with_even_parent(albero &tree, nodo n){
    int sum = 0;

    if( tree.leaf(n) ){
        if( tree.readNode(tree.parent(n)) % 2 == 0)
            sum = 1;
        else
            sum = 0;
    } else {
        n = tree.firstChild(n);
        while (!tree.lastSibling(n)){
            sum += leafs_with_even_parent(tree, n);
            n = tree.nextSibling(n);
        }
        sum += leafs_with_even_parent(tree, n);
    }

    return sum;
}

int leafs_with_even_parent(albero &tree){
    return leafs_with_even_parent(tree, tree.root());
}

/* ------------------- fine leafs_with_even_parent -------------------- */

/*
 odd
 - calcola e restituisce il numero di nodi di livello k il cui valore e' dispari;
 */

int odd(albero &tree, nodo n, int lev){
    int sum = 0;

    if (lev == 0){
        if ( tree.readNode(n) % 2 == 1)
            sum = 1;
        else
            sum = 0;
    } else {
        n = tree.firstChild(n);
        while (!tree.lastSibling(n)){
            sum += odd(tree, n, lev - 1);
            n = tree.nextSibling(n);
        }
        sum += odd(tree, n, lev - 1);
    }

    return sum;
}

int odd(albero &tree, int k){
    return odd(tree, tree.root(), k);
}

/* ------------------- fine odd -------------------- */

/*
    Given a Tree (not binary Tree), print only leaf nodes with it's path from Root
 */

void printPath(albero &tree, nodo n, ListaPT<nodo> path){

    if(tree.leaf(n)){
        ListaPT<nodo>::posizione p = path.primolista();
        cout << "Foglia: " << tree.readNode(n) << " - Percorso: ";
        while(!path.finelista(p)){
            cout << tree.readNode(path.leggilista(p)) << " ";
            p = path.succlista(p);
        }

        cout << tree.readNode(n) << endl;
    } else {
        path.inslista(n, path.succlista(path.primolista()));
        n = tree.firstChild(n);
        while (!tree.lastSibling(n)){
            printPath(tree, n, path);
            n = tree.nextSibling(n);
        }
        printPath(tree, n, path);
    }

}

void printPath(albero &tree){
    ListaPT<nodo> ls;
    printPath(tree, tree.root(), ls);
}

void sbilancia(albero &tree, ListaPT<nodo> &c, nodo n, int lev){
    if (lev == 0){
        c.inslista(n, c.primolista());
    } else {
        n = tree.firstChild(n);
        while (!tree.lastSibling(n)){
            sbilancia(tree, c, n, lev - 1);
            n = tree.nextSibling(n);
        }
        sbilancia(tree, c, n, lev - 1);
    }
}

void sbLev(albero &tree, int lev){
    ListaPT<nodo> c;
    sbilancia(tree, c, tree.root(), lev);
    tree.removeSubTree(c.leggilista(c.primolista()));
}

void sbilancia(albero &tree){
    sbLev(tree, 2);
}

void sbilancia(albero &tree, int n){
    sbLev(tree, n);
}

void sbilancia(albero &tree, int p, int n){
    ListaPT<nodo> c;
    sbilancia(tree, c, tree.root(), n);
    int i = 1;

    ListaPT<nodo>::posizione pos = c.ultimolista();
    while ( i < p && !c.finelista(pos)){
        pos = c.predlista(pos);
        i++;
    }

    tree.removeSubTree(c.leggilista(pos));
}

int main(){

    TreePT<int> treeInt;
    TreePT<int>::node n;
    MediaTree<int, TreePT<int>::node> medT;

    treeInt.insRoot(n);
	treeInt.writeNode(treeInt.root(), 2);
	treeInt.insFirst(treeInt.root(), 7);
	treeInt.insFirst(treeInt.root(), 3);
	n = treeInt.firstChild(treeInt.root());
	treeInt.insFirst(n, 15);
	treeInt.insFirst(n, 30);
	treeInt.insFirst(n, 11);
	n = treeInt.firstChild(treeInt.root());
	n = treeInt.nextSibling(n);
	treeInt.insFirst(n, 22);
	cout << "Albero T: ";
	treeInt.print();

    printPath(treeInt);

    sbilancia(treeInt, 2, 2);

    /*
    cout << "Numero Foglie il cui valore è dispari: " << odd(treeInt, 2);

    cout << "Larghezza dell'albero è: " << larghezza(treeInt, treeInt.root());

    dispari(treeInt);


    somma(treeInt);

    media(treeInt);
    pari(treeInt);

	treeInt.bfs(treeInt.root());

    cout << "Media degli elementi a livello 2: " << mediaLivello(treeInt, 2);

    cout << endl << "Altezza: " << getHeight(treeInt, treeInt.root());

    cout << endl << "La larghezza dell'albero è: " << larghezza(treeInt, treeInt.root());


    cout << endl << "Media degli elementi a livello 2: " << medT.mediaLivello(treeInt, 0);

    cout << endl << "Media di tutti gli elementi: " << medT.media(treeInt);


    //pesa(treeInt);

    //cout << endl << "Albero Pesato: ";

    treeInt.print();

    dispari(treeInt);

    pota(treeInt, 15);*/

    ListaPT<double> ls;

    ls.inslista(2, ls.primolista());
    ls.inslista(9, ls.primolista());
    ls.inslista(9, ls.primolista());
    ls.inslista(3, ls.primolista());
    ls.inslista(4, ls.primolista());
    ls.inslista(8, ls.primolista());
    ls.inslista(3, ls.primolista());
    ls.inslista(7, ls.primolista());
    ls.inslista(4, ls.primolista());

    typedef ListaPT<double>::posizione pos;

    pos p = ls.primolista();
    bool flag = true;

    cout << ls;

    while(!ls.finelista(p)){
        double somma = 0.0;
        pos p1, p2;

        if(flag){
            p1 = ls.predlista(p);
            p2 = ls.predlista(p1);
        } else {
            p1 = ls.succlista(p);
            p2 = ls.succlista(p1);
        }

        if(!ls.finelista(p1) && !ls.finelista(p2))
            somma = ls.leggilista(p1) + ls.leggilista(p2);

        ls.scrivilista( somma, p );
        flag = !flag;

        cout << ls;

        p = ls.succlista(p);
    }

	return 0;
}
