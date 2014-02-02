#include <iostream>
#include <cstdlib> //Serve per poter usare le funzioni della libreria standard del C
#include "Insieme.h"

using namespace std;

Insieme::Insieme(){
   creaInsieme();
};

Insieme::~Insieme(){
   posizione q;
   while (insieme != NULL){
      q = insieme;
      insieme = insieme->getSuccessivo();
      delete q;
   }
};
   
void Insieme::creaInsieme(){
   insieme = NULL;
};

bool Insieme::insiemeVuoto(){
   return (insieme == NULL);
};

bool Insieme::appartiene(tipoelem a){
   posizione p = insieme;
   bool flag = false;
   while ((p != NULL) && (!flag)){
      flag = (a == p->getEtichetta());
      p = p->getSuccessivo();
   }
   return flag;
};

void Insieme::inserisci(tipoelem a){
   if (!appartiene(a))
      insieme = new NodoPtr(a, insieme);
      else
        cout<< "elemento già presente";  
};

void Insieme::cancella(tipoelem a){
   if (appartiene(a)){
      posizione p = insieme;
      posizione q = p;
	  	while ((p != NULL) && (p->getEtichetta()!=a)){
       	q = p;       		
       	p = p->getSuccessivo();
      }
      if(p==insieme){
      	if(p->getSuccessivo()==NULL)
      		insieme = NULL;
      	else
      		insieme = p->getSuccessivo();
      } else 
   	  	q->setSuccessivo(p->getSuccessivo());
      delete p;
      
   } else cout<<"elemento non presente";      
};

Insieme &Insieme::unione(Insieme &set){
   Insieme b;
   b = set;
   Insieme *c = new Insieme(); //creiamo un nuovo insieme c
   posizione p = insieme;
   tipoelem a;
   while (p != NULL){
      a = p->getEtichetta();
      if (b.appartiene(a)){
         b.cancella(a);
      }
      c->inserisci(a);
      p = p->getSuccessivo();
   }
   p = b.getInsieme();
   while (p != NULL){
      a = p->getEtichetta();
      c->inserisci(a);
      p = p->getSuccessivo();
   }
   return *c;
};

Insieme &Insieme::intersezione(Insieme &set){
   Insieme b;
   b = set;
   posizione p = b.getInsieme();
   Insieme *c = new Insieme();
   tipoelem a;
   while (p != NULL){         /*******************************************/
      a = p->getEtichetta();  /* Costrutto che toglie tutti gli elementi */
      if (!appartiene(a))     /* dall'insieme b che già sono presenti    */
         b.cancella(a);       /* nell'insieme iniziale.                  */
      p = p->getSuccessivo(); /*******************************************/
   }
   p = b.getInsieme();
   while (p != NULL){
      a = p->getEtichetta();
      c->inserisci(a);
      p = p->getSuccessivo();
   }
   return *c;
};

Insieme &Insieme::differenza(Insieme &set){
   Insieme b;
   b = set;
   Insieme *c = new Insieme();
   posizione p = insieme;
   tipoelem a;
   while (p != NULL){
      a = p->getEtichetta();
      if (!b.appartiene(a)){
         c->inserisci(a);
      }
      p = p->getSuccessivo();
   }   
   return *c;
};

Insieme &Insieme::operator=(Insieme &i){
	posizione p;
   while (insieme != NULL){
   	p = insieme;
      insieme = insieme->getSuccessivo();
      delete p;
   }
	p = i.getInsieme();
	while (p!=NULL){
		inserisci(p->getEtichetta());
		p = p->getSuccessivo();
	}
	return *this;
}

posizione Insieme::getInsieme(){
   return insieme;
};
