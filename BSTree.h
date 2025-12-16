#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"
#include <functional>

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T>*root;
        BSNode<T>*search(BSNode<T>*n, T e){
            if (n == nullptr){
                return nullptr;
            }
            if (e == n -> elem){
                return n;
            } else if (e < n -> elem){
                return search(n -> left, e);
            } else {
                return search(n -> right, e);
            }
        }
        BSNode<T>* insert(BSNode<T>* n, T e) {

        if (n == nullptr) {
            return new BSNode<T>(e, nullptr, nullptr);
        }

        else if(e == n->elem) {
            throw std::runtime_error("Ja esta l'element, perro");
        }
        else if (e < n->elem) {
            n->left = insert(n->left, e);
        }
        else {
            n->right = insert(n->right, e);
        }

        return n;
        }
    

        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            if (n != nullptr){
                print_inorder(out, n -> left);
                out << n -> elem << " ";
                print_inorder(out, n -> right);
            }
        }
        BSNode<T>* remove(BSNode<T>* n, T e){
            if (n == nullptr){
                throw std::runtime_error("L'element no esta en l abre troll");
            }
            if (e < n -> elem){
                n -> left = remove(n -> left, e);
            } else if (e > n -> elem){
                n -> right = remove(n -> right, e);
            } else {
                if (n -> left == nullptr){
                    BSNode<T>* temp = n -> right;
                    delete n;
                    return temp;
                } else if (n -> right == nullptr){
                    BSNode<T>* temp = n -> left;
                    delete n;
                    return temp;
                }
                BSNode<T>* temp = n -> right;
                n -> elem = temp -> elem;
                n -> right = remove(n -> right, temp -> elem);
            }
            return n;
        }
        T max(BSNode<T>* n) const{
            if (n == nullptr){
                throw std::runtime_error("L'element no esta en l abre troll");
            }
            while (n -> right != nullptr){
                n = n -> right;
            }
            return n -> elem;
        }
        BSNode<T>* remove_max(BSNode<T>* n){
            if (n == nullptr){
                throw std::runtime_error("L'element no esta en l abre troll");
            }
            if (n -> right == nullptr){
                BSNode<T>* temp = n -> left;
                delete n;
                return temp;
            }
            n -> right = remove_max(n -> right);
            return n;
        }
        void delete_cascade(BSNode<T>* n){
            if (n != nullptr){
                delete_cascade(n -> left);
                delete_cascade(n -> right);
                delete n;
            }
        }
        


    public:
        BSTree(){
            nelem = 0;
            root = nullptr;
        }

        int size() const{
            return nelem;
        }

        T search(T e){
            BSNode<T>* result = search(root, e);
            if (result == nullptr){
                throw std::runtime_error("L'element no esta en l abre troll");
            }
            return result -> elem;

        }
        T operator[](T e){
            return search(e);
        }
        void insert(T e){
            root = insert(root, e);
            nelem++;
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;
        }
        void remove(T e){
            root = remove(root, e);
        }
        ~BSTree(){
            delete_cascade(root);
        }

    
};

#endif