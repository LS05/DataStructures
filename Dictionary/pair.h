#ifndef MY_PAIR_H_
#define MY_PAIR_H_

template<class K, class E>
class mypair {
public:
    typedef K key;
    typedef E value;

    mypair(){}
    mypair(key, value);
    mypair(const mypair<K,E> &);

    void setKey(key);
    void setValue(const value);
    key getKey();
    value getValue();
private:
    key first;
    value second;
};

template<class K, class E>
mypair<K, E>::mypair(const mypair<K,E> &the_pair){
    this->first = the_pair.first;
    this->second = the_pair.second;
}

template<class K, class E>
mypair<K, E>::mypair(key k, value val){
    this->first = k;
    this->second = val;
}

template<class K, class E>
void mypair<K, E>::setKey(key k){
    this->first = k;
}

template<class K, class E>
void mypair<K, E>::setValue(const value val){
    this->second = val;
}

template<class K, class E>
typename mypair<K, E>::key mypair<K, E>::getKey(){
    return this->first;
}

template<class K, class E>
typename mypair<K, E>::value mypair<K, E>::getValue(){
    return this->second;
}

#endif // PAIR_H_INCLUDED
