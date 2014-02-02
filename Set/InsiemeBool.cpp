#include <iostream>
#include <cstdlib>
#include "InsiemeBool.h"

using namespace std;

InsiemeBool::InsiemeBool(){
	creaInsieme();
}
InsiemeBool::~InsiemeBool(){
	for (int i = 0; i < MAXLUNG; i++){
		insieme[i] = false;
	}
	delete [] insieme;
}

void InsiemeBool::creaInsieme(){
	insieme = new bool[MAXLUNG];
	for (int i = 0; i < MAXLUNG; i++){
		insieme[i] = false;
	}
}

bool InsiemeBool::insiemeVuoto(){
	bool flag = false;

	for (int i = 0; ((i < MAXLUNG) && (!flag)); i++){
		flag = insieme[i];
	}
	return !flag;
}

bool InsiemeBool::appartiene(tipoelem a){
	return insieme[a];
}

void InsiemeBool::inserisci(tipoelem a){
	insieme[a - 1] = true;
}

void InsiemeBool::cancella(tipoelem a){
	insieme[a] = false;
}

InsiemeBool* InsiemeBool::unione(InsiemeBool a){
	InsiemeBool *c = new InsiemeBool();

	for (int i = 0; i < MAXLUNG; i++){
		if ((insieme[i] || a.appartiene(i)))
			c->inserisci(i + 1);
	}

	return c;
}

InsiemeBool* InsiemeBool::intersezione(InsiemeBool a){
//	InsiemeBool *c = new InsiemeBool();

	for (int i = 0; i < MAXLUNG; i++){
		//if (insieme[i] && a.appartiene(i))
			//c->inserisci(i + 1);
			cout << "intersezione";
	}

	return NULL;
}
InsiemeBool* InsiemeBool::differenza(InsiemeBool a){
	InsiemeBool *c = new InsiemeBool();

	for (int i = 0; i < MAXLUNG; i++){
		if ((insieme[i] && (!a.appartiene(i))))
			c->inserisci(i + 1);
	}

	return c;
}

void InsiemeBool::stampaInsieme(){
	cout << "{ ";

	for(int indice = 0; indice< MAXLUNG; indice++){
		int elem = indice + 1;
		if(appartiene(indice))
			cout << elem  << " ";
	}

	cout << "}" << endl;
}
