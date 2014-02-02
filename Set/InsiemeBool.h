#ifndef INSIEMEBOOL_H
#define INSIEMEBOOL_H

#define MAXLUNG 20
#include <iostream>

using namespace std;

typedef int tipoelem;

class InsiemeBool{
public:

	InsiemeBool();
	InsiemeBool(const InsiemeBool&);
	~InsiemeBool();

	void creaInsieme();
	bool insiemeVuoto();
	bool appartiene(tipoelem);
	void inserisci(tipoelem);
	void cancella(tipoelem);
	InsiemeBool intersezione(InsiemeBool &);
	InsiemeBool unione(InsiemeBool &);
	InsiemeBool differenza(InsiemeBool &);

	void stampaInsieme();

	InsiemeBool& operator=(const InsiemeBool &);

private:
	bool *insieme;
};

InsiemeBool& InsiemeBool::operator=(const InsiemeBool& s){
    this->insieme = new bool[MAXLUNG];
    for(int i = 0; i < MAXLUNG; i++)
        this->insieme[i] = s.insieme[i];
    return *this;
};

InsiemeBool::InsiemeBool(){
	creaInsieme();
}

void InsiemeBool::creaInsieme(){
	insieme = new bool[MAXLUNG];
	for (int i = 0; i < MAXLUNG; i++){
		insieme[i] = false;
	}
}

InsiemeBool::InsiemeBool(const InsiemeBool& set){
    this->insieme = new bool[MAXLUNG];
    for(int i = 0; i < MAXLUNG; i++)
        this->insieme[i] = set.insieme[i];
}

InsiemeBool::~InsiemeBool(){
	for (int i = 0; i < MAXLUNG; i++){
		insieme[i] = false;
	}
	delete [] insieme;
}

bool InsiemeBool::insiemeVuoto(){
	bool flag = false;

	for (int i = 0; ((i < MAXLUNG) && (!flag)); i++){
		flag = insieme[i];
	}
	return !flag;
}

bool InsiemeBool::appartiene(tipoelem a){
    if(a > 0)
        return insieme[a - 1];
    else
        return false;
}

void InsiemeBool::inserisci(tipoelem a){
    if(a > 0)
        insieme[a - 1] = true;
}

void InsiemeBool::cancella(tipoelem a){
	insieme[a] = false;
}

InsiemeBool InsiemeBool::unione(InsiemeBool &a){
	InsiemeBool c;

	for (int i = 1; i < MAXLUNG; i++){
		if ((insieme[i - 1] || a.appartiene(i)))
			c.inserisci(i);
	}

	return c;
}

InsiemeBool InsiemeBool::intersezione(InsiemeBool &a){
	InsiemeBool c;

	for (int i = 1; i < MAXLUNG; i++){
		if (insieme[i - 1] && a.appartiene(i))
			c.inserisci(i);
	}

	return c;
}

InsiemeBool InsiemeBool::differenza(InsiemeBool &a){
	InsiemeBool c;

	for (int i = 1; i < MAXLUNG; i++){
		if ((insieme[i - 1] && (!a.appartiene(i))))
			c.inserisci(i);
	}

	return c;
}

void InsiemeBool::stampaInsieme(){
	cout << "{ ";

	for(int indice = 1; indice <= MAXLUNG; indice++){
		if(appartiene(indice))
			cout << indice  << " ";
	}

	cout << "}" << endl;
}

#endif
