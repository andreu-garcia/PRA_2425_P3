#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "ListLinked.h"  

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;
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
            table = new ListLinked<TableEntry<V>>[max];
            
        }
        ~HashTable(){
            delete[]table;
        }
        int capacity(){
            return max;
        }

        friend std::ostream& operator<<(std::ostream &out,const HashTable<V> &th){
            
            for (int i=0;i<th.max;i++){
                out<<i<<" : "<<th.table[i]<<std::endl;
            }
            return out;
        }
        V search(const std::string key)override{

            int index= h(key);
            int pos = table[index].search(key);
            if (pos == -1){
                throw std::runtime_error("La key no existix perro");
            }
            return table[index].get(pos).value;
        }

        V remove(const std::string key) override{

            int index = h(key);
            TableEntry<V>te(key);
            int pos = table[index].search(te);
            if (pos != -1){
                TableEntry<V> removedEntry = table[index].get(pos);
                table[index].remove(pos);
                n--;
                return te.value;
            }
            throw std::runtime_error("La key no existix perro");   
        }
    
        

        V operator[](const std::string  &key){

            return (this->search(key));
        }

        void insert(const std::string key,V value)override{
            int index = h(key);
            TableEntry<V>te(key,value);
            int pos = table[index].search(te);
            if (pos != -1){
                throw std::runtime_error("Esta clau ja existix puto troll");
            }
            table[index].append(te);
            n++;
        }
        int entries(){
            
            return n;

        }


        
};

#endif