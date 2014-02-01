/***************************************************************************
 *   Copyright (C) 2005 by Nicola Di Mauro                                 *
 *   ndm@di.uniba.it                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *																           *
 ***************************************************************************/

#ifndef _Bin_treecC_H_
#define _Bin_treecC_H_

#include "BinTree.h"

#include <iostream>

using namespace std;

template <class T>
class Bin_treec : public Bin_tree<T, int>{
	static const int NIL = -1;

public:

	typedef typename Bin_tree<T, int>::value_type value_type;
	typedef typename Bin_tree<T, int>::Nodo Nodo;

	struct _cella{
		Nodo genitore;
		Nodo sinistro;
		Nodo destro;
		value_type valore;
	};

	typedef struct _cella Cella;

	Bin_treec();
	Bin_treec(int);
	~Bin_treec();

	void create();
	bool empty() const;

	Nodo root() const;
	Nodo parent(Nodo) const;
	Nodo sx(Nodo) const;
	Nodo dx(Nodo) const;
	bool sx_empty(Nodo) const;
	bool dx_empty(Nodo) const;

	void erase(Nodo);

	value_type read(Nodo) const;
	void write(Nodo , value_type );

	void ins_root(Nodo);
	void ins_sx(Nodo);
	void ins_dx(Nodo);

	void preorder(Nodo);
	void postorder(Nodo);
	void inorder(Nodo);

private:
	int MAXLUNG;
	Cella *spazio;
	int nNodi;
	Nodo inizio;
	Nodo libera;
};

template <class T>
Bin_treec<T>::Bin_treec()
{
	MAXLUNG = 100;
	spazio = new Cella[MAXLUNG];
	create();
}

template <class T>
Bin_treec<T>::Bin_treec(int nNodi): MAXLUNG(nNodi)
{
	spazio = new Cella[nNodi];
	create();
}


template <class T>
Bin_treec<T>::~Bin_treec()
{
	erase(inizio);
	delete[] spazio;
}

template <class T>
void Bin_treec<T>::create()
{
	inizio = NIL;
	for (int i = 0; i < MAXLUNG; i++)
	{
		spazio[i].sinistro = (i+1) % MAXLUNG;
	}

	libera = 0;
	nNodi = 0;
}

template <class T>
bool Bin_treec<T>::empty() const
{
	return(nNodi == 0);
}

template <class T>
typename Bin_treec<T>::Nodo Bin_treec<T>::root() const
{
	return(inizio);
}

template <class T>
typename     Bin_treec<T>::Nodo Bin_treec<T>::parent(Nodo n) const
{
	if (n != inizio)
		return (spazio[n].genitore);
	else
		return(n);
}

template <class T>
typename     Bin_treec<T>::Nodo Bin_treec<T>::sx(Nodo n) const
{
	if (!sx_empty(n))
		return (spazio[n].sinistro);
	else
		return(NIL);
};

template <class T>
typename     Bin_treec<T>::Nodo Bin_treec<T>::dx(Nodo n) const
{
	if (!dx_empty(n))
		return (spazio[n].destro);
	else
		return(NIL);
}

template <class T>
bool Bin_treec<T>::sx_empty(Bin_treec<T>::Nodo n) const
{
	return (spazio[n].sinistro == NIL);
}

template <class T>
bool Bin_treec<T>::dx_empty(Bin_treec<T>::Nodo n) const
{
	return (spazio[n].destro == NIL);
}

template <class T>
void Bin_treec<T>::ins_root(Bin_treec<T>::Nodo n)
{
	if (inizio == NIL)
	{
		inizio = libera;
		libera = spazio[libera].sinistro;
		spazio[inizio].sinistro = NIL;
		spazio[inizio].destro = NIL;
		nNodi++;
	}
	else
		cout << "La Radice esiste";
}


template <class T>
void Bin_treec<T>::ins_sx(Nodo n)
{
	if (inizio == NIL)
		cout << "Albero vuoto";
	if (n == NIL)
		cout << "Nodo Nullo";
	if (spazio[n].sinistro != NIL)
		cout << "Nodo già esistente";
	if (nNodi >= MAXLUNG)
		cout << "Capacità massima raggiunta";
	else
	{
		Nodo q = libera;
		libera = spazio[libera].sinistro;
		spazio[n].sinistro = q;
		spazio[q].sinistro = NIL;
		spazio[q].genitore = n;
		spazio[q].destro = NIL;
		nNodi++;
	}
}

template <class T>
void Bin_treec<T>::ins_dx(Nodo n)
{
	if (inizio == NIL)
		cout << "Albero vuoto";
	if (n == NIL)
		cout << "Nodo Nullo";
	if (spazio[n].destro != NIL)
		cout << "Nodo già esistente";
	if (nNodi >= MAXLUNG)
		cout << "Capacità massima raggiunta";
	else
	{
		Nodo q = libera;
		libera = spazio[libera].sinistro;
		spazio[n].destro = q;
		spazio[q].genitore = n;
		spazio[q].sinistro = NIL;
		spazio[q].destro = NIL;
		nNodi++;
	}
}

template <class T>
void Bin_treec<T>::erase(Nodo n)
{
	if (n != NIL) {
		if (!sx_empty(n))
			erase(spazio[n].sinistro);
		if (!dx_empty(n))
			erase(spazio[n].destro);
		if (n != inizio) {
			Nodo p = parent(n);
			if (spazio[p].sinistro == n)
				spazio[p].sinistro = NIL;
			else
				spazio[p].destro = NIL;
		}
		else
			inizio = NIL;
		nNodi--;
		spazio[n].sinistro = libera;
		libera = n;
	}
	else
		cout << "Nodo Nullo";
}

template <class T>
typename Bin_treec<T>::value_type Bin_treec<T>::read(Nodo n) const
{
	if (n != NIL)
		return (spazio[n].valore);
	else
		cout << "Nodo Nullo";
}

template <class T>
void Bin_treec<T>::write(Nodo n, value_type a)
{
	if (n != NIL)
		spazio[n].valore = a;
	else
		cout << "Nodo Nullo";
}

template <class T>
void Bin_treec<T>::postorder(Nodo p){
	if (p == NIL) {
		return;
	} else {
		postorder( this->sx(p) );
		postorder( this->dx(p) );
		cout << this->read(p) << " ";
	}
}

template <class T>
void Bin_treec<T>::preorder(Nodo p){
	if (p != NIL){
      value_type a;
      a = read(p);
    	cout << a << " ";
		if (!sx_empty(p))
			preorder(sx(p));
		if (!dx_empty(p))
			preorder(dx(p));
	}
}

template <class T>
void Bin_treec<T>::inorder(Nodo p){
	if (p != NIL){
    	if (!sx_empty(p))
			inorder(sx(p));
		value_type a = read(p);
    	cout << a << " ";
		if (!dx_empty(p))
			inorder(dx(p));
	}
}
#endif
