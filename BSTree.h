#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T>*root;
    public:
        T search(T e){
            BSNode<T>* current = root;
            while (current != nullptr){
                if (e == current -> elem){
                    return current -> elem;
                } else if (e < current -> elem){
                    current = current -> left;
                } else {
                    current = current -> right;
                }
            }
            throw std::runtime_error("El elemento no está en el árbol");

        }
    
};

#endif