#ifndef GRAFOLISADIACENTI_H
#define GRAFOLISADIACENTI_H

#include "Grafo.h"
#include "ListaAdiacenti.h"
#include "CodaPT.h"

#define MAXNODI 100
#define NIL -1

class NodoAD{
public:
    NodoAD(int i){ nodoId = i; }
    NodoAD(){ }
    int getId(){ return nodoId; }
    void setId(int id) {nodoId = id;}
    bool operator== (const NodoAD &) const;
    bool operator!= (const NodoAD &) const;
private:
    int nodoId;
};

bool NodoAD::operator== (const NodoAD &n) const
{
    return (this->nodoId == n.nodoId);
}

bool NodoAD::operator!= (const NodoAD &n) const
{
    return (this->nodoId != n.nodoId);
}

template<class P>
class InfoArco {
public:
    P peso;
    NodoAD _to;
    bool operator== (const InfoArco< P > &) const;
    bool operator!= (const InfoArco< P > &) const;
};

template<class P>
bool InfoArco< P >::operator== (const InfoArco< P > &n) const
{
    return (this->_to == n._to);
}

template<class P>
bool InfoArco< P >::operator!= (const InfoArco< P > &n) const
{
    return (this->_to != n._to);
}

template< class T, class P>
class InfoNodo {
public:
    T etichetta;
    bool presente;
    bool visitato;
    ListaAdiacenti< InfoArco<P> > vicini;
    
    InfoNodo(){
        presente = false;
        visitato = false;
    }
};

template< class T, class P>
class GrafoAdiacenti : Grafo< T, NodoAD, P>{
public:
    typedef T tipoelem;
    typedef P peso;
    typedef NodoAD nodo;
    
    typedef Arco_<peso, nodo> Arco;
    typedef Grafo<T, NodoAD, P> Graph;
    typedef typename Graph::listaNodi listaNodi;
    typedef typename Graph::posListaNodi posAdi;
    
    GrafoAdiacenti(int = MAXNODI);
    GrafoAdiacenti(const GrafoAdiacenti &);
    ~GrafoAdiacenti();

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

    bool getVisitato(nodo);
    void setVisitato(bool, nodo);
    void azzeraVisitato();
    
    GrafoAdiacenti< T, P >& operator= (const GrafoAdiacenti< T, P > &);
    bool operator== (const GrafoAdiacenti< T, P > &);
    
	template <class Y, class M>
	friend ostream& operator<< (ostream &out, GrafoAdiacenti< Y, M > &graph);
private:
    int dimensione;
    int nodi;
    int archi;
    InfoNodo< T, P > *grafo;
};

template< class T, class P>
GrafoAdiacenti< T, P >::GrafoAdiacenti(int n) {
    dimensione = n;
    nodi = 0;
    archi = 0;
    this->grafo = new InfoNodo< T, P >[dimensione];
    for (int i = 0; i<dimensione; i++) {
        grafo[i].presente = false;
        grafo[i].visitato = false;
        grafo[i].vicini.crealista();
    }
}

template< class T, class P>
GrafoAdiacenti< T, P >::GrafoAdiacenti(const GrafoAdiacenti &gro) {
    this->dimensione = gro.dimensione;
    this->nodi = gro.nodi;
    this->archi = gro.archi;
    this->grafo = new InfoNodo< T, P >[dimensione];
    for(int i = 0; i < this->dimensione; i++){
        this->grafo[i].presente = gro.grafo[i].presente;
        this->grafo[i].visitato = gro.grafo[i].visitato;
        this->grafo[i].vicini = gro.grafo[i].vicini;
        this->grafo[i].etichetta = gro.grafo[i].etichetta;
    }
}

template< class T, class P>
GrafoAdiacenti< T, P >::~GrafoAdiacenti() { delete [] grafo; };

template< class T, class P>
bool GrafoAdiacenti< T, P >::vuoto() const{
   bool vuoto = true;
   for (int i = 0; (i<dimensione && vuoto); i++)
      vuoto = (vuoto && (!grafo[i].presente));

   return (vuoto);
}

template< class T, class P>
bool GrafoAdiacenti< T, P >::esisteNodo(nodo u) const{
    int nodeID = u.getId();
    if (nodeID >= 0 && nodeID < dimensione)
        return (grafo[u.getId()].presente);
    else
        return (false);
}

template< class T, class P>
bool GrafoAdiacenti< T, P >::esisteArco(Arco a) const{
    nodo u = a.nodo1;
    nodo v = a.nodo2;
   if (esisteNodo(u) && esisteNodo(v)) {
       typename ListaAdiacenti< InfoArco<P> >::posizione p;
       p = grafo[u.getId()].vicini.primolista();
       bool trovato = false;
       while (!(grafo[u.getId()].vicini.finelista(p)) && !trovato) {
           if (grafo[u.getId()].vicini.leggilista(p)._to == v)
               trovato = true;
           else
               p = grafo[u.getId()].vicini.succlista(p);
       }
       return (trovato);
   } else {
      return (false);
   }
}

template< class T, class P>
void GrafoAdiacenti< T, P >::insNodo(nodo &u) {
    int i = 0;
    
    if( nodi < dimensione ){
        while( grafo[i].presente == true )
            i++;
        nodi++;
        grafo[i].presente = true;
    }
    
    u.setId(i);
}

template< class T, class P>
void GrafoAdiacenti< T, P >::insArco(nodo u, nodo v, peso p) {
    InfoArco<P> I;
    I.peso = p;
    I._to = v;
    grafo[u.getId()].vicini.inslista(I, grafo[u.getId()].vicini.primolista());
    archi++;
}

template< class T, class P>
bool GrafoAdiacenti< T, P >::cancNodo(nodo u) {
    if (grafo[u.getId()].presente){
      if (grafo[u.getId()].vicini.listavuota()) {
         bool trovato = false;
          for (int i = 0; ((i < dimensione) && (!trovato)); i++){
              Arco a(i, u);
            if (esisteArco(a))
               trovato = true;
          }
         if (!trovato)
            grafo[u.getId()].presente = false;
         nodi--;
         return (true);
      }
      else
         return (false);
   }
   else
      return (false);
}

template< class T, class P>
void GrafoAdiacenti< T, P >::cancArco(nodo n1 , nodo n2) {
    typename ListaAdiacenti<InfoArco<P>>::posizione p;
    p = grafo[n1.getId()].vicini.primolista();
    bool trovato = false;
    while (!grafo[n1.getId()].vicini.finelista(p) && !trovato){
        if (grafo[n1.getId()].vicini.leggilista(p)._to.getId() == n2.getId())
            trovato = true;
        else
            p = grafo[n1.getId()].vicini.succlista(p);
    }
    if (trovato)
        grafo[n1.getId()].vicini.canclista(p);
    archi--;
}

template< class T, class P>
typename::GrafoAdiacenti<T,P>::listaNodi GrafoAdiacenti< T, P >::adiacenti(nodo u) const {
    listaNodi ls;
    typename ListaAdiacenti<InfoArco<P>>::posizione p;
    p = grafo[u.getId()].vicini.primolista();
    while(!grafo[u.getId()].vicini.finelista(p)){
        InfoArco<P> inf = grafo[u.getId()].vicini.leggilista(p);
        ls.inslista(&inf._to, ls.primolista());
        p = grafo[u.getId()].vicini.succlista(p);
    }
    
    return ls;
}

template< class T, class P>
bool GrafoAdiacenti< T, P >::scriviNodo(nodo u, tipoelem a) {
   if (esisteNodo(u)) {
      grafo[u.getId()].etichetta = a;
      return (true);
   }
   else
      return (false);
}

template< class T, class P>
typename GrafoAdiacenti< T, P >::tipoelem GrafoAdiacenti< T, P >::leggiNodo(nodo u) const{
   if (esisteNodo(u))
      return (grafo[u.getId()].etichetta);
}

template< class T, class P>
bool GrafoAdiacenti< T, P >::scriviPeso(nodo u, nodo v, peso w) {
    typename ListaAdiacenti< InfoArco<P> >::posizione p;
    bool trovato = false;
    p = grafo[u.getId()].vicini.primolista();
    while (!grafo[u.getId()].vicini.finelista(p) && !trovato){
        if(grafo[u.getId()].vicini.leggilista(p)._to == v)
            trovato = true;
        else
            p = grafo[u.getId()].vicini.succlista(p);
    }
    if(trovato)
        grafo[u.getId()].vicini.leggilista(p).peso = w;
}

template< class T, class P>
typename GrafoAdiacenti< T, P>::peso GrafoAdiacenti< T, P >::leggiPeso(nodo u, nodo v) const{
    typename ListaAdiacenti< InfoArco<P> >::posizione p;
    bool trovato = false;
    p = grafo[u.getId()].vicini.primolista();
    while (!grafo[u.getId()].vicini.finelista(p) && !trovato)
        if( grafo[u.getId()].vicini.leggilista(p)._to == v)
            trovato = true;
        else
            p = grafo[u.getId()].vicini.succlista(p);
    if(trovato)
        return grafo[u.getId()].vicini.leggilista(p).peso;
}

template< class T, class P>
bool GrafoAdiacenti< T, P >::getVisitato(nodo u) {
   return (grafo[u.getId()].visitato);
}

template< class T, class P>
void GrafoAdiacenti< T, P >::setVisitato(bool b, nodo u) {
   grafo[u.getId()].visitato = b;
}

template< class T, class P>
void GrafoAdiacenti< T, P >::azzeraVisitato() {
   for (int i = 0; i < dimensione; i++)
      grafo[i].visitato = false;
}

template< class T, class P>
typename GrafoAdiacenti< T, P >::listaNodi GrafoAdiacenti<T, P>::listNodi() const{
    listaNodi res;
    for (int i = 0; i < dimensione & grafo[i].presente; i++){
        res.inslista(new NodoAD(i), res.primolista());
    }
    
    return res;
}

template< class T, class P>
int GrafoAdiacenti< T, P >::numNodi(){
    return nodi;
}

template< class T, class P>
int GrafoAdiacenti< T, P >::numArchi(){
    return archi;
}

template< class T, class P>
GrafoAdiacenti< T, P >& GrafoAdiacenti< T, P >::operator= (const GrafoAdiacenti< T, P > &gr){
    
    if (this == &gr)
        return *this;
    
    this->dimensione = gr.dimensione;
    this->nodi = gr.nodi;
    this->archi = gr.archi;
    InfoNodo< T, P > *res = new InfoNodo< T, P >[gr.dimensione];
    
    for(int i = 0; i < gr.dimensione; i++){
        res[i].presente = gr.grafo[i].presente;
        res[i].visitato = gr.grafo[i].visitato;
        res[i].vicini = gr.grafo[i].vicini;
        res[i].etichetta = gr.grafo[i].etichetta;
    }
    
    delete [] this->grafo;
    
    this->grafo = res;
    
    return *this;
}

template< class T, class P>
bool GrafoAdiacenti< T, P >::operator== (const GrafoAdiacenti< T, P > &gr){
    bool check = true;
    if(this->archi == gr.archi && this->nodi == gr.nodi){
        for (int i = 0; i < this->nodi && check; i++){
            if (this->grafo[i].presente && gr.grafo[i].presente){
                if ( !(this->grafo[i].vicini == gr.grafo[i].vicini) )
                    check = false;
            } else {
                check = false;
            }
        }
    } else {
        check = false;
    }
    
    return check;
}

template <class Y, class M>
ostream& operator<< (ostream &out, GrafoAdiacenti<Y, M> &gr){
    out << "Nodi \t Archi" << endl;
    
    for (int i = 0; i < gr.nodi; i++){
        NodoAD n(i);
        if(gr.esisteNodo(n)){
            out << n.getId() << " - > ";
            
            for(int j = 0; j <= gr.archi; j++){
                NodoAD m(j);
                typename GrafoAdiacenti<Y, M>::Arco a(n , m);
                if(gr.esisteArco(a))
                    out << j << " - ";
            }
            
            out << endl;
        }
    }
    
    return out;
}


template< class T, class P>
void DFS(NodoAD &u, GrafoAdiacenti< T, P > &g) {
//    if ((!g.grafoVuoto() && g.esisteNodo(u))) {
//        NodoAD v;
//        adiacente<P> temp;
//        ListaAdiacenti< adiacente<P> > l;
//        typename ListaAdiacenti< adiacente<P> >::posizione p;
//        T a = g.leggiNodo(u);
//        cout << a << " ";
//        
//        g.setVisitato(true, u);
//        g.adiacenti(u, l);
//        p = l.primolista();
//        while (!l.finelista(p)) {
//            temp = l.leggilista(p);
//            v = temp.punto;
//            if (!g.getVisitato(v))
//                DFS(v, g);
//            p = l.succlista(p);
//        }
//    } else{
//      cout << "DFS NON APPLICABILE" << endl;
//    }
}

bool copiaCoda(CodaPT< NodoAD > &q, CodaPT< NodoAD > &r) {
   if (!q.codaVuota()) {
      CodaPT< NodoAD > s;
      NodoAD a;
      while (!q.codaVuota()) {
         a = q.leggiCoda();
         r.inCoda(a);
         s.inCoda(a);
         q.fuoriCoda();
      }
      while (!s.codaVuota()) {
         a = s.leggiCoda();
         q.inCoda(a);
         s.fuoriCoda();
      }
      return (true);
   }
   else
      return (false);
}

bool ricercaCoda(NodoAD &a, CodaPT< NodoAD > &q) {
   bool trovato = false;
   if (!q.codaVuota()) {
      CodaPT< NodoAD > r;
      copiaCoda(q, r);
      NodoAD b;
      while (!(r.codaVuota() || trovato)) {
         b = r.leggiCoda();
         if (b==a)
            trovato = true;
         else
            r.fuoriCoda();
      }
   }

   return (trovato);
}

template< class T, class P>
void BFS(NodoAD &u, GrafoAdiacenti< T, P > &g) {
//   if ((!g.grafoVuoto() && g.esisteNodo(u))) {
//       CodaPT< NodoAD > q;
//       T a;
//       adiacente<P> temp;
//       NodoAD v;
//       typename ListaAdiacenti< adiacente<P> >::posizione p;
//       
//       q.inCoda(u);
//       while (!q.codaVuota()) {
//           u = q.leggiCoda();
//           a = g.leggiNodo(u);
//           cout << a << " ";
//           g.setVisitato(true, u);
//           q.fuoriCoda();
//           ListaAdiacenti< adiacente<P> > l;
//           g.adiacenti(u, l);
//           p = l.primolista();
//           while (!l.finelista(p)) {
//               temp = l.leggilista(p);
//               v = temp.punto;
//               if (!(g.getVisitato(v) || ricercaCoda(v, q)))
//                   q.inCoda(v);
//               p = l.succlista(p);
//           }
//       }
//       g.azzeraVisitato();
//       cout << endl;
//   } else {
//      cout << "BFS NON APPLICABILE" << endl;
//   }
}

#endif
