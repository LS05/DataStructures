#ifndef HASH_H_
#define HASH_H_
#include <iostream>
#include <string>

using namespace std;
typedef unsigned int hashval;

class Hash{
public:
	static hashval hashFunc(const string the_key){
        unsigned long hash_value = 0;
        int length = (int) the_key.length();
        for (int i=0; i<length; i++)
            hash_value = 5 * hash_value + the_key.at(i);
        return size_t(hash_value);
	}
//DA FINIRE
	static hashval hashFunc(int the_key);
};

#endif
