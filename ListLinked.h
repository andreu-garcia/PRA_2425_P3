#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T>
{

private:
    Node<T> *first = nullptr;
    int n = 0;

public:
    ListLinked() = default;

    ~ListLinked()
    {
        while (first != nullptr)
        {
            Node<T> *aux = first->next;
            delete first;
            first = aux;
        }
        n = 0;
    }

    T operator[](int pos)
    {
        return this->get(pos);
    }
    friend std::ostream &operator<<(std::ostream &out, const ListLinked<T> &list)
    {
        Node<T> *current = list.first;
        out << "[";
        for (int i = 0; i < list.n; i++)
        {
            out << current->data;
            if (i < list.n - 1)
                out << ", ";
            current = current->next;
        }
        out << "]";
        return out;
    }

    void insert(int pos, T e) override
    {
        if (pos < 0 || pos > n)
            throw std::out_of_range("La posición no es válida (fuera del intervalo de la lista)");
        if (pos == 0)
        {
            first = new Node<T>(e, first);
        }
        else
        {
            Node<T> *current = first;
            for (int i = 0; i < pos - 1; i++)
            {
                current = current->next;
            }
            current->next = new Node<T>(e, current->next);
        }
        n++;
    }

    void append(T e) override { insert(n, e); }
    void prepend(T e) override { insert(0, e); }

    T remove(int pos) override
    {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("La posición no es válida (fuera del intervalo de la lista)");
        T elem;
        if (pos == 0)
        {
            Node<T> *toDelete = first;
            elem = first->data;
            first = first->next;
            delete toDelete;
        }
        else
        {
            Node<T> *current = first;
            for (int i = 0; i < pos - 1; i++)
            {
                current = current->next;
            }
            Node<T> *toDelete = current->next;
            elem = toDelete->data;
            current->next = toDelete->next;
            delete toDelete;
        }
        n--;
        return elem;
    }

    T get(int pos) override
    {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("La posición no es válida (fuera del intervalo de la lista)");
        Node<T> *current = first;
        for (int i = 0; i < pos; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    int search(T e) override
    {
        Node<T> *current = first;
        for (int i = 0; i < n; i++)
        {
            if (current->data == e)
                return i;
            current = current->next;
        }
        return -1;
    }

    bool empty() override { return n == 0; }
    int size() override { return n; }
};

#endif