template< class T >
class Nodo{
public:

	typedef T tipoelem;

	Nodo();
	~Nodo();

	tipoelem getElemento() const;
	void setElemento(const tipoelem);

private:
	tipoelem elemento;
};

template< class T>
Nodo<T>::Nodo(){}

template< class T>
Nodo<T>::~Nodo(){}

template< class T>
typename Nodo<T>::tipoelem Nodo<T>::getElemento() const
{
	return this->elemento;
}


template< class T>
void Nodo<T>::setElemento(const tipoelem e){
	this->elemento = e;
}
