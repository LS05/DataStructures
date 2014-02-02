#ifndef ESALBERO_H
#define ESALBERO_H

#include "TreePT.h"
#include "CodaPT.h"

template<class T>
class EsAlbero{
public:
    typedef typename TreePT<T>::node nodo;

    EsAlbero(TreePT<T> &);
    ~EsAlbero();

    int profondita(nodo);
    void foglieK(int, int, nodo);
    double mediaLivello(TreePT<T> &, int);
    double mediaLivello2(TreePT<T> &, int);
private:
    TreePT<T> *tree;
    double mediaSupp(nodo, int, int, TreePT<T> &);
    void mediaLivello2Supp(nodo, CodaPT<T> &, int, int);
};

template<class T>
EsAlbero<T>::EsAlbero(TreePT<T> &albero){
    this->tree = &albero;
}

template<class T>
EsAlbero<T>::~EsAlbero(){
    this->tree.~TreePT<T>();
}

template<class T>
int EsAlbero<T>::profondita(nodo n){
    int max, temp;
    if(tree->leaf(n)){
        return 0;
    }else{
        nodo v = tree->firstChild(n);
        max = 0;
        while(!tree->lastSibling(v)){
            temp = profondita(v);
            if(max <= temp)
                max = temp;
            v = tree->nextSibling(v);
        }
        return ++max;
    }
}

template<class T>
void EsAlbero<T>::foglieK(int val, int somma, nodo n){
    nodo temp;
    if(tree.leaf(n)){
        if((somma += tree.readNode(n)) == val){
            tree.removeSubTree(n);
        }
    } else{
        somma += tree.readNode(n);
        nodo v = tree.firstChild(n);
        while(!tree.lastSibling(v)){
            if(tree.leaf(v)){
                temp = v->getNextBro();
            }
            foglieK(val, somma, v);
            if(tree.leaf(temp))
                v = temp;
            else
                v = tree.nextSibling(v);
        }
    }
}
template<class T>
double EsAlbero<T>::mediaSupp(nodo n, int liv, int curr, TreePT<T> &tree){
//    CodaPT<nodo> q;
//    int el = 0;
//    double media = 0;
//    double somma = 0;
//
//    if(curr != liv - 1){
//        media = mediaSupp(tree.firstChild(n), liv, ++curr, tree);
//    } else{
//        q.inCoda(n);
//        while(!q.codaVuota()){
//            nodo v = q.leggiCoda();
//            q.fuoriCoda();
//            nodo m = tree.firstChild(v);
//            while (!tree.lastSibling(m)){
//                    somma += m->getEtichetta();
//                    el++;
//                    m = tree.nextSibling(m);
//            }
//            somma += m->getEtichetta();
//            el++;
//            if(!tree.lastSibling(v))
//                q.inCoda(tree.nextSibling(v));
//        }
//        media = somma / el;
//    }
//
//    return media;
}

template<class T>
double EsAlbero<T>::mediaLivello(TreePT<T> &tree, int liv){
//    double res = mediaSupp(tree.root(), liv, 0, tree);
//    return res;
}

template<class T>
void EsAlbero<T>::mediaLivello2Supp(nodo n, CodaPT<T> &ls, int lev, int curr){
    if(n != NULL && curr <= lev){
        while (n != NULL){
                if(lev == curr)
                    ls.inCoda(n->getEtichetta());
                mediaLivello2Supp(this->tree->firstChild(n), ls, lev, curr + 1);
                n = this->tree->nextSibling(n);
        }
    }
}

template<class T>
double EsAlbero<T>::mediaLivello2(TreePT<T> &tree, int liv){
    CodaPT<T> coda;
    double somma = 0.0, med = 0.0;
    int el = 0;
    mediaLivello2Supp(tree.root(), coda, liv, 1);
    while(!coda.codaVuota()){
        somma += coda.leggiCoda();
        el++;
        coda.fuoriCoda();
    }
    med = somma / el;
    return med;
}

#endif
