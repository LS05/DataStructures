#ifndef FACTLIST_H
#define FACTLIST_H
#include "linear_list.h"
#include "ListaVT.h"
#include "ListaPT.h"

template< class T >
class factlist
{
    public:
//        static Linear_list<T> * getList(string tipo)
//        {
//            if (tipo == "ptr")
//                return new ListPT<T>;
//            if (tipo == "vt")
//                return new ListVT<T>;
//        }
        ~factlist();
    private:
        factlist();
};

#endif // FACTLIST_H
