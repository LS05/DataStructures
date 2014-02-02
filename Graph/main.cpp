#include <iostream>

#include "GrafoMat.h"

using namespace std;

typedef string tipoelem;

typedef GrafoMatAd<tipoelem, tipoelem> Graph;
typedef Graph::listaNodi listaNodi;
typedef Graph::posLista posLSN;
typedef Graph::nodo nodo;
typedef Graph::Arco Arco;

listaNodi colorGraph(Graph &gr, string color){
    listaNodi ls = gr.listNodi();
    posLSN p = ls.primolista();
    
    while (!ls.finelista(p)){
        tipoelem e = gr.leggiNodo(*ls.leggilista(p));
        
        if(e != color){
            ls.canclista(p);
        }
        
        p = ls.succlista(p);
    }
    
    return ls;
}
//
void isolaNodo(Graph &gr, nodo n){
    listaNodi ls = gr.listNodi();
    posLSN p1 = ls.primolista();
    
    while (!ls.finelista(p1)) {
        nodo m = *ls.leggilista(p1);
        Arco a1(n, m);
        Arco a2(m, n);
        
        if(gr.esisteArco(a1))
            gr.cancArco(n, m);
            
        if(gr.esisteArco(a2))
            gr.cancArco(m, n);
        
        p1 = ls.succlista(p1);
    }
}

Graph MODGraph(Graph &gr, string color){
    Graph gRes;
    listaNodi res = colorGraph(gr, color);
    posLSN p = res.primolista();
    
    while (!res.finelista(p)) {
        nodo n = *res.leggilista(p);
        isolaNodo(gr, n);
        gr.cancNodo(n);
        cout << gr;
        p = res.succlista(p);
    }
    
    cout << gr;
    
    return gr;
}

Graph REDGraph(Graph &gr){
    MODGraph(gr, "BLUE");
}

Graph BLUEGraph(Graph &gr){
    MODGraph(gr, "RED");
}


pair<int, int> RBGraph(Graph &gr){
    pair<int, int> rbcount;
    listaNodi rNodes = colorGraph(gr, "RED");
    listaNodi bNodes = colorGraph(gr, "BLUE");
    
    rbcount.first = rNodes.size();
    rbcount.second = bNodes.size();
    
    return rbcount;
}

int inDeg(Graph &gr, nodo n, listaNodi &ls){
    listaNodi::posizione p = ls.primolista();
    int i = 0;
    
    while (!ls.finelista(p)){
        nodo m = *ls.leggilista(p);
        Arco a(m, n);
        if( gr.esisteArco(a) ){
            i++;
        }
        p = ls.succlista(p);
    }
    
    return i;
}

int outDeg(Graph &gr, nodo n, listaNodi &ls){
    listaNodi::posizione p = ls.primolista();
    int i = 0;
    
    while (!ls.finelista(p)){
        nodo m = *ls.leggilista(p);
        Arco a(n, m);
        if( gr.esisteArco(a) ){
            i++;
        }
        p = ls.succlista(p);
    }
    
    return i;
}

void allDeg(Graph &G){
    listaNodi ls = G.listNodi();
    listaNodi::posizione p = ls.primolista();
    
    while (!ls.finelista(p)){
        nodo n = *ls.leggilista(p);
        cout << "Nodo " << n.getId() << " - Peso Entrante: " << inDeg(G, n, ls) << " Peso Uscente: " << outDeg(G, n, ls) << endl;
        p = ls.succlista(p);
    }
}

bool well(Graph &G, nodo n, listaNodi &ls){
    return ( inDeg(G, n, ls) != 0 && outDeg(G, n, ls) == 0);
}

bool sorg(Graph &G, nodo n, listaNodi &ls){
    return ( inDeg(G, n, ls) == 0 && outDeg(G, n, ls) != 0);
}

void sorgWell(Graph &G){
    listaNodi ls = G.listNodi();
    listaNodi::posizione p = ls.primolista();
    
    while (!ls.finelista(p)){
        nodo n = *ls.leggilista(p);
        if( sorg( G, n, ls) )
            cout << "Nodo " << n.getId() << ": Sorgente" << endl;
        else if( well(G, n, ls) ){
            cout << "Nodo " << n.getId() << ": Pozzo" << endl;
        }
        p = ls.succlista(p);
    }
}

Graph deleteWell(Graph G){
    listaNodi ls = G.listNodi();
    listaNodi::posizione p = ls.primolista();
    
    while (!ls.finelista(p)){
        nodo n = *ls.leggilista(p);
        if( well(G, n, ls) ){
            isolaNodo(G, n);
            G.cancNodo(n);
        }
        
        p = ls.succlista(p);
    }
    
    return G;
}

int main() {
    Graph G, G1, G2;
    Graph::nodo n1, n2, n3, n4, n5;
    
    G.insNodo(n1);
    G.scriviNodo(n1, "RED");
    G.insNodo(n2);
    G.scriviNodo(n2, "RED");
    G.insNodo(n3);
    G.scriviNodo(n3, "BLUE");
    G.insNodo(n4);
    G.scriviNodo(n4, "BLUE");
    G.insNodo(n5);
    G.scriviNodo(n5, "BLUE");
    
    
    G.insArco(n1, n2, "");
    G.insArco(n1, n3, "");
    G.insArco(n1, n5, "");
    G.insArco(n1, n4, "");
    G.insArco(n3, n4, "");
    G.insArco(n3, n5, "");
    G.insArco(n4, n5, "");
    G.insArco(n5, n4, "");
    
    cout << G;
    
    allDeg(G);
    
    Graph res = deleteWell(G);
    
    cout << "Grafo Originale" << endl;
    cout << G;
    
    cout << "Grafo Nuovo" << endl;
    cout << res;
    
    G2 = G;
    
}