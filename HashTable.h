#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>*table;
        int h;
        int h(std::string key);

    public:
        HashTable(int size);
        ~HashTable();
        int capacity;
        friend std::ostream& operator<<(std::ostram &out,const HashTable<V> &th);
        V operator[](std::string key);

        
};

#endif