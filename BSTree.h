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
        BSNode<T>*insert(BSNode<T>*n, T e){

            if(e==n->elem){
                throw std::runtime_error("Ja esta l'element perro");
            }
            if (n == nullptr){
                n = new BSNode<T>(e);
            } else if (e < n -> elem){
                n -> left = insert(n -> left, e);
            } else {
                n -> right = insert(n -> right, e);
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
                BSNode<T>* temp = minValueNode(n -> right);
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
            throw std::runtime_error("L'element no esta en l abre troll");

        }
        T operator[](T e){
            return search(e);
        }
        void insert(T e){
            BSNode<T>* newNode = new BSNode<T>(e);
            if (root == nullptr){
                root = newNode;
            } else {
                BSNode<T>* current = root;
                BSNode<T>* parent = nullptr;
                while (true){
                    parent = current;
                    if (e < current -> elem){
                        current = current -> left;
                        if (current == nullptr){
                            parent -> left = newNode;
                            break;
                        }
                    } else {
                        current = current -> right;
                        if (current == nullptr){
                            parent -> right = newNode;
                            break;
                        }
                    }
                }
            }
            nelem++;
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            std::function<void(BSNode<T>*)> inOrder = [&](BSNode<T>* node) {
                if (node != nullptr) {
                    inOrder(node->left);
                    out << node->elem << " ";
                    inOrder(node->right);
                }
            };
            inOrder(bst.root);
            return out;
        }
        void remove(T e){
            root = removeRec(root, e);
        }
        ~BSTree(){}

    
}

#endif