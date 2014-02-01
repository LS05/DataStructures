#ifndef _GRAFOMATAD_H
#define _GRAFOMATAD_H
#include "Grafo.h"
#include "ListaAdiacenti.h"
#define MAXLUNG 10

class NodoMD{
public:
    NodoMD(int i){ nodoId = i; }
    NodoMD(){ }
    int getId(){ return nodoId; }
    void setId(int id) {nodoId = id;}
    bool operator== (NodoMD &);
    bool operator!= (NodoMD &);
private:
    int nodoId;
};

bool NodoMD::operator== (NodoMD &n)
{
    return (this->nodoId == n.nodoId);
}

bool NodoMD::operator!= (NodoMD &n)
{
    return (this->nodoId != n.nodoId);
}

template<class P>
class InfoMArco {
public:
	P peso;
	bool vuoto;
    
	InfoMArco(){
		vuoto = true;
	}
};


template<class T, class P>
class InfoMNodo {
public:
	T   etichetta;
	bool vuoto;
	void* info;
	InfoMArco<P>* archi;
    
	InfoMNodo(){
		info = 0;
		vuoto = true;
	}
    
	~InfoMNodo(){
		if (!vuoto)
			delete [] archi;
	}
};

template< class T, class P>
class GrafoMatAd:public Grafo< T, NodoMD, P> {
public:
    
    typedef T tipoelem;
    typedef P peso;
    typedef NodoMD nodo;
    
    typedef Arco_<peso, nodo> Arco;
    typedef Grafo<T, NodoMD, P> Graph;

    typedef typename Graph::listaNodi listaNodi;
    typedef typename Graph::posListaNodi posLista;

    GrafoMatAd(int = MAXLUNG);
    GrafoMatAd(const GrafoMatAd &);
    ~GrafoMatAd();
    
    bool vuoto() const;
    void insNodo(nodo&);
    void insArco(nodo, nodo, peso);
    bool cancNodo(nodo);
    void cancArco(nodo, nodo);
    bool esisteNodo(nodo) const;
    bool esisteArco(Arco) const;
    listaNodi adiacenti(nodo) const;
    listaNodi listNodi() const;
    tipoelem leggiNodo(nodo) const;
    bool scriviNodo(nodo, tipoelem);
    peso leggiPeso(nodo, nodo) const;
    bool scriviPeso(nodo, nodo, peso);
    int numNodi();
    int numArchi();
    
    GrafoMatAd< T, P >& operator= (const GrafoMatAd< T, P > &);
//    bool operator== (const GrafoMatAd< T, P > &);
    
    template <class Y, class M>
	friend ostream& operator<< (ostream &out, GrafoMatAd<Y, M> &gr);
private:
    int dimensione;
    int nodi;
    int archi;
    InfoMNodo<T, P> *matAdiacenza;
};

template< class T , class P>
GrafoMatAd< T, P >::GrafoMatAd(int n) {
	dimensione = n;
	nodi = 0;
	archi = 0;
	matAdiacenza = new InfoMNodo< T, P >[dimensione];
	for (int i=0; i < dimensione; i++)
		matAdiacenza[i].archi = new InfoMArco<P>[dimensione];
}

template< class T , class P>
GrafoMatAd< T, P >::GrafoMatAd(const GrafoMatAd &gr) {
    this->dimensione = gr.dimensione;
    this->nodi = gr.nodi;
    this->archi = gr.archi;
    this->matAdiacenza = new InfoMNodo< T, P >[dimensione];
    for (int i=0; i < this->dimensione; i++){
        matAdiacenza[i].vuoto = gr.matAdiacenza[i].vuoto;
		matAdiacenza[i].archi = new InfoMArco<P>[dimensione];
        for( int j = 0; j < dimensione; j++ ){
            matAdiacenza[i].archi[j].peso = gr.matAdiacenza[i].archi[j].peso;
            matAdiacenza[i].archi[j].vuoto = gr.matAdiacenza[i].archi[j].vuoto;
        }
    }
}

template< class T , class P>
GrafoMatAd< T, P >::~GrafoMatAd() {
   delete [] matAdiacenza;
}

template< class T, class P>
bool GrafoMatAd< T, P >::vuoto() const {
   return (nodi==0);
}

template< class T, class P>
void GrafoMatAd< T, P >::insNodo(nodo &u) {
	int n = 0;
	if (nodi < dimensione){
		while (matAdiacenza[n].vuoto == false)
			n++;
		nodi++;
		matAdiacenza[n].vuoto = false;
	}
	u.setId(n);
}

template< class T, class P>
void GrafoMatAd< T, P >::insArco(nodo u, nodo v, peso p) {
    Arco a(u ,v);
   if (esisteNodo(u) && esisteNodo(v) && !esisteArco(a)) {
       matAdiacenza[u.getId()].archi[v.getId()].peso = p;
       matAdiacenza[u.getId()].archi[v.getId()].vuoto = false;
       archi++;
   } else {
      if (esisteArco(a))
         cout << "ARCO GIA' PRESENTE\n";
      else
         cout << "UNO O ENTRAMBI I NODI NON SONO PRESENTI\n";
   }
}

template< class T, class P>
bool GrafoMatAd< T, P >::esisteNodo(nodo u) const {
   if (u.getId() < dimensione && !matAdiacenza[u.getId()].vuoto)
      return (true);
   else
      return (false);
}

template< class T, class P>
bool GrafoMatAd< T, P >::esisteArco(Arco a) const {
    bool esiste = false;
    nodo u = a.nodo1;
    nodo v = a.nodo2;
    if (esisteNodo(u) && esisteNodo(v))
        esiste = !(matAdiacenza[u.getId()].archi[v.getId()].vuoto);

   return esiste;
}

template< class T, class P>
bool GrafoMatAd< T, P >::cancNodo(nodo u) {
   listaNodi insiemeAdiacenza = adiacenti(u);
   if (esisteNodo(u) && insiemeAdiacenza.listavuota()) {
      matAdiacenza[u.getId()].vuoto = true;
      nodi--;
   } else {
      if (!esisteNodo(u))
         cout << "NODO NON PRESENTE\n";
      else
         cout << "IL NODO E' ADIACENTE AD ALTRI NODI\n";
   }
}

template< class T, class P>
void GrafoMatAd< T, P >::cancArco(nodo u, nodo v) {
    Arco a(u, v);
    if (esisteNodo(u) && esisteNodo(v) && esisteArco(a)) {
        matAdiacenza[u.getId()].archi[v.getId()].vuoto = true;
        archi--;
   } else {
      if (!esisteArco(a))
         cout << "L'ARCO CHE SI VUOLE CANCELLARE NON E' PRESENTE\n";
      else
         cout << "UNO O ENTRAMBI I NODI NON SONO PRESENTI\n";
   }
}

template< class T, class P>
typename GrafoMatAd< T, P >::listaNodi GrafoMatAd< T, P >::adiacenti(nodo u) const {
    listaNodi list;
    
	for (int i = 0; i < dimensione; i++) {
		if (!matAdiacenza[u.getId()].archi[i].vuoto) {
			list.inslista(new NodoMD(i), list.primolista());
		}
	}
	return list;
}
template< class T, class P>
typename GrafoMatAd< T, P>::listaNodi GrafoMatAd< T, P >::listNodi() const{
    listaNodi list;
    
    for (int i = 0; i < dimensione; i++)
        if (!matAdiacenza[i].vuoto)
            list.inslista(new NodoMD(i), list.primolista());
    
    return list;
}

template< class T, class P>
typename GrafoMatAd< T, P >::tipoelem GrafoMatAd< T, P>::leggiNodo(nodo u) const {
   return (matAdiacenza[u.getId()].etichetta);
}

template< class T, class P>
bool GrafoMatAd< T, P >::scriviNodo(nodo u, tipoelem a) {
    if(esisteNodo(u)){
        matAdiacenza[u.getId()].etichetta = a;
        return true;
    } else {
        return false;
    }
}

template< class T, class P>
typename GrafoMatAd< T, P >::peso GrafoMatAd< T, P >::leggiPeso(nodo u, nodo v) const{
    Arco a(u, v);
    if( esisteArco(a) ){
        return matAdiacenza[u.getId()].archi[v.getId()].peso;
    }
}

template< class T, class P>
bool GrafoMatAd< T, P >::scriviPeso(nodo u, nodo v, peso p){
    Arco a(u, v);
    if( esisteArco(a) ){
        this->matAdiacenza[u.getId()].archi[v.getId()].peso = p;
        return true;
    } else {
        return false;
    }
}

template< class T, class P>
int GrafoMatAd< T, P >::numNodi(){
    return nodi;
}

template< class T, class P>
int GrafoMatAd< T, P >::numArchi(){
    return archi;
}

template <class Y, class M>
ostream& operator<< (ostream &out, GrafoMatAd<Y, M> &gr){
    out << "Nodi \t Archi" << endl;
    
    for (int i = 0; i <= gr.nodi; i++){
        NodoMD n(i);
        if(gr.esisteNodo(n)){
            out << n.getId() << " - > ";
            
            for(int j = 0; j <= gr.archi; j++){
                NodoMD m(j);
                typename GrafoMatAd<Y, M>::Arco a(n , m);
                if(gr.esisteArco(a))
                   out << j << " - ";
            }
            
            out << endl;
        }
    }
    
    return out;
}

template< class T, class P>
GrafoMatAd< T, P >& GrafoMatAd<T, P>::operator= (const GrafoMatAd< T, P > &gr){
    
    if (this == &gr)
        return *this;
    
    this->dimensione = gr.dimensione;
    this->nodi = gr.nodi;
    this->archi = gr.archi;
    InfoMNodo< T, P > *res = new InfoMNodo< T, P >[gr.dimensione];
    
    for(int i = 0; i < gr.dimensione; i++){
        res[i].vuoto = gr.matAdiacenza[i].vuoto;
		res[i].archi = new InfoMArco<P>[dimensione];
        for( int j = 0; j < dimensione; j++ ){
            res[i].archi[j].peso = gr.matAdiacenza[i].archi[j].peso;
            res[i].archi[j].vuoto = gr.matAdiacenza[i].archi[j].vuoto;
        }
    }
    
    delete [] this->matAdiacenza;
    
    this->matAdiacenza = res;
    
    return *this;
}

#endif
