#include <cstdlib>
#include <iostream>
#include "NAlbero.h"


using namespace std;

void inserisciNAlbero(nodoN n, NAlbero &t){
   tipoelem a;
   if (t.nAlberoVuoto()){
      cout << "Inserisci radice: ";
      cin >> a;
      if (n == NULL)
         n = new NodoNPtr();
      t.scriviNodo(n, a);
      t.insRadice(n);
      inserisciNAlbero(n, t);
   } else{
      int i, j;
      cout << "Quanti figli ha " << t.leggiNodo(n) << "? ";
      cin >> j;
      if (j > 0){
         for (i = 1; i <= j; i++){
            nodoN m = new NodoNPtr();
            cout << "Inserisci " << i << "^ figlio di " << t.leggiNodo(n) <<": ";
            cin >> a;
            t.scriviNodo(m, a);
            if (i == 1)
               t.insPrimoSottoAlbero(n, m);
            else{
               nodoN p = t.primoFiglio(n);
               while (!(t.ultimoFratello(p)))
                  p = t.succFratello(p);
               t.insSottoAlbero(p, m);
            }
            cout << endl;
            inserisciNAlbero(m, t);
         }
      } else cout << endl;
   } 
}


void inserNAlbero(NAlbero &t){
   nodoN n = new NodoNPtr();
   t.insRadice(n);
   t.scriviNodo(n,1);

   nodoN m = new NodoNPtr();
   t.insPrimoSottoAlbero(n, m);
   t.scriviNodo(m, 2);

   nodoN p = new NodoNPtr();
   t.insSottoAlbero(m, p);
   t.scriviNodo(p, 3);

   nodoN k = new NodoNPtr();
   t.insSottoAlbero(p, k);
   t.scriviNodo(k, 4);

   nodoN z = new NodoNPtr();
   t.insPrimoSottoAlbero(m, z);
   t.scriviNodo(z, 5);

}

void stampaNAlbero(nodoN n, NAlbero &t){
   if (n != NULL){
      while (n != NULL){
         cout << "(" << t.leggiNodo(n);
         stampaNAlbero(t.primoFiglio(n), t);
         cout << ")";
         n = t.succFratello(n);
      }
	} else cout << "()";
}

void preVisita(nodoN n, NAlbero &t){
   if (n != NULL){
      while (n != NULL){
         cout << t.leggiNodo(n) << " "; 
         preVisita(t.primoFiglio(n), t);
         n = t.succFratello(n);
      }
	} 

}

void postVisita(nodoN n, NAlbero &t){
   if (n != NULL){
      while (n != NULL){
         postVisita(t.primoFiglio(n), t);
         cout << t.leggiNodo(n) << " ";
         n = t.succFratello(n);
      }
	}
}

void inVisita(nodoN n, NAlbero &t){
   if (n != NULL){
      if (!t.foglia(n)){
         inVisita(t.primoFiglio(n), t);
         cout << t.leggiNodo(n) << " ";
         n = t.primoFiglio(n);
         while (!t.ultimoFratello(n)){
            n = t.succFratello(n);
            inVisita(n, t);
         }
      } else cout << t.leggiNodo(n) << " ";
	}
}


/*void ampiezzaN(nodoN n, NAlbero &t){
   CodaPtr q;
   q.inCoda(n);
   while (!q.codaVuota()){
      q.leggiCoda(n);
		cout << t.leggiNodo(n) << " ";
		q.fuoriCoda();
		if (!t.foglia(n)){
         nodoN m = t.primoFiglio(n);
    	   while (!t.ultimoFratello(m)){
            q.inCoda(m);
            m = t.succFratello(m);
         }
         q.inCoda(m);
      }
   }
}
*/


int main(int argc, char *argv[])
{
   NAlbero t;
   tipoelem a;
      
   cout << "Inserimento dell'albero n-ario T" << endl<<endl;
        inserNAlbero(t);
        cout <<"T = ";
        stampaNAlbero(t.radice(), t);
   cout << endl << endl ;
   
   cout << "Visite:" << endl << endl ;
        cout<<"preVisita  -> T = ";
        preVisita(t.radice(), t);
        
        cout << endl <<endl<< "postVisita -> T = ";
        postVisita(t.radice(), t);
        
        cout << endl << endl<< "inVisita   -> T = ";
        inVisita(t.radice(), t);
        
        //cout << endl << "Ampiezza   -> T: ";
       //ampiezzaN(t.radice(), t);

   cout << endl << endl;
   
   system("PAUSE");
   return 0;
}
