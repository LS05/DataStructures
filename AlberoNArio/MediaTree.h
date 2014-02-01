//
//  MediaTree.h
//  AlberoNArioX
//
//  Created by Luca Suriano on 11/09/13.
//  Copyright (c) 2013 Luca Suriano. All rights reserved.
//

#ifndef AlberoNArioX_MediaTree_h
#define AlberoNArioX_MediaTree_h

#include "Tree.h"

template<class I, class N>
class MediaTree {
public:
	typedef I item;
	typedef N node;
    
    MediaTree();

    double mediaLivello(Tree<I, N> &tree, int lev);
    double media(Tree<I, N> &tree);
private:
    double sumLevel(Tree<I, N> &tree, node n, int lev);
    int getHeight(Tree<I, N> &tree, node n);
    double nele;
};

template<class I, class N>
MediaTree<I, N>::MediaTree(){
    this->nele = 0;
}

template<class I, class N>
double MediaTree<I, N>::mediaLivello(Tree<I, N> &tree, int lev){
    double sumL = sumLevel(tree, tree.root(), lev);
    double media = sumL / this->nele;
    this->nele = 0;
    return media;
}

template<class I, class N>
double MediaTree<I, N>::sumLevel(Tree<I, N> &tree, node n, int lev){
    int sum = 0;
    
    if( lev == 0 ){
        this->nele++;
        return tree.readNode(n);
    } else {
        n = tree.firstChild(n);
        while(!tree.lastSibling(n)){
            sum += sumLevel(tree, n, lev - 1);
            n = tree.nextSibling(n);
        }
        sum += sumLevel(tree, n, lev - 1);
    }
    
    return sum;
}

template<class I, class N>
int MediaTree<I, N>::getHeight(Tree<I, N> &tree, node n){
    int max = 0, temp = 0;
    if(tree.leaf(n))
        return 0;
    else{
        node v = tree.firstChild(n);
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

template<class I, class N>
double MediaTree<I, N>::media(Tree<I, N> &tree){
    int maxLev = getHeight(tree, tree.root());
    double sum = 0, media = 0;
    
    for(int i = 0; i <= maxLev; i++){
        sum += sumLevel(tree, tree.root(), i);
    }
    
    media = sum / this->nele;
    this->nele = 0;
    return media;
}

#endif
