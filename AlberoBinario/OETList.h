//
//  OETList.h
//  AlberoBinarioX
//
//  Created by Luca Suriano on 10/09/13.
//  Copyright (c) 2013 Luca Suriano. All rights reserved.
//

#ifndef AlberoBinarioX_OETList_h
#define AlberoBinarioX_OETList_h
#include "BinTree.h"
#include "ListaPT.h"

using namespace std;

template<class T, class N>
class OETList{
public:
    typedef T tipoelem;
    typedef N tiponodo;
    
    void analyze(Bin_tree<T, N> &);
    void showLists();
    
private:
    void analyze(Bin_tree<T, N> &tree, tiponodo n);
    ListaPT<N> S;
    ListaPT<N> D;
};

template<class T, class N>
void OETList<T, N>::analyze(Bin_tree<T, N> &tree){
    analyze(tree, tree.root());
}

template<class T, class N>
void OETList<T, N>::analyze(Bin_tree<T, N> &tree, tiponodo n){
	if (!(tree.sx_empty(n) && tree.dx_empty(n))){
        tipoelem a = tree.read(n);
        
        if( (a % 2) == 0){
            if(!tree.sx_empty(n))
                S.inslista(tree.sx(n), S.primolista());
            if(!tree.dx_empty(n))
                D.inslista(tree.dx(n), D.primolista());
        }
        
        
		if (!tree.sx_empty(n))
			analyze(tree, tree.sx(n));
		if (!tree.dx_empty(n))
			analyze(tree, tree.dx(n));
	}
    
    return;
}

template<class T, class N>
void OETList<T, N>::showLists(){
    cout << S;
    cout << D;
}

#endif
