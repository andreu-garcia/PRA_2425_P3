#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../"  

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        listLinked<TableEntry<V>>* table;
        int h(std::string key){

            int suma=0;

            for (char c : key){
                suma += c;
            }
            return (suma%max);
        }

    public:
        HashTable(int size){
            
            this ->n =0;
            this -> max = size;
            tabla = new listLinked<TableEntry<V>>[max];
            
        }
        ~HashTable(){
            delete[]tabla;
        }
        int capacity(){
            return n;
        }
        friend std::ostream& operator<<(std::ostram &out,const HashTable<V> &th){
            
            for (int i=0;i<th.n;i++){
                out<<i<<" : "<<th.table[i]<<std::endl;
            }
            return out;
        }
        V search(std::strink key){

            for (int i=0 ; i<th.max ; i++){
                if (th.table[i].key==h(key)){
                    return th.table[i].value;

                }
            }
            throw std::runetime_error("La key no existix perro"):
        }

        V operator[](std::string key){

            return (this->search(key));
        }

        void insert(std::string &key, V &value){

            if (n<max){
                int index = h(key);
                if (this->search(key)==key){

                    throw std::runetime_error("Esta clau ja existix puto troll");
                }
                else{
                    
                    TableEntry<V>te(key,value);
                    tabla[index].append(te);
                }

            }

        }
        
};

#endif