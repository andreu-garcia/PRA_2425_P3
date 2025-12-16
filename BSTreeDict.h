#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>*tree;
    public:
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>();
        }
        ~BSTreeDict(){
            delete tree;
        }
    
        void insert(const std::string key, V value) override {
            TableEntry<V> entry(key, value);
            tree->insert(entry);
        }
        V search(const std::string key) override {
            TableEntry<V> entry(key);
            TableEntry<V> foundEntry = tree->search(entry);
            return foundEntry.value;
        }
        V remove(const std::string key) override {
            TableEntry<V> entry(key);
            TableEntry<V> foundEntry = tree->search(entry);
            tree->remove(entry);
            return foundEntry.value;
        }
        int entries() override {
            return tree->size();
        }
        V operator[](std::string key) {
            return search(key);
        }
        friend std::ostream& operator<<(std::ostream &out,const BSTreeDict<V> &bd){
            out<<bd.tree;
            return out;
        }

        
};

#endif