#ifndef HINPA_BLIST_H
#define HINPA_BLIST_H
#include <cstddef>
#include <iostream>
#include "../Nodes/binode.h"


template<typename Type>
class BList {
    BNode<Type> *HEAD = NULL;
    BNode<Type> *TAIL = NULL;
    size_t size = 0;
    /*
     * UB if pos is the other end of the list. Most likely to cause segfault
     * Substitute with fetch element (from back and front)!
     * Consider list as an array [0...n]
     * fetch_from_any_direction(pos) will have to return pos element
     */
    BNode<Type> *fetch_from_back(size_t pos);
    BNode<Type> *fetch_from_front(size_t pos);
public:
    ~BList() { free(); }
    BList() {};
    BList(const BList &copy); // yet to be implemented
    BList& operator= (const BList &copy); // yet to be implemented
    BList& push_front(const Type& element); // implemented
    BList& insert(const Type& element, size_t position = 0); // implemented
    BList& push_back(const Type& element); // implemented
    Type pop_front(); // implemented
    Type pop_back(); // implemented
    Type erase(size_t position = 0); // implemented
    void free(); // implemented
    Type& get(size_t position); // implemented
    inline Type& top() { return HEAD->data; }
    inline Type& bottom() { return TAIL->data; }
    size_t sz() { return size; }
    void stdout(); 
};



template<typename Type>
BNode<Type> *BList<Type>::fetch_from_back(size_t pos)
{
    BNode<Type> *it = TAIL;
    for (int i = 0; i != pos; ++i)
        it = it->prev;
    return it;
}

template<typename Type>
BNode<Type> *BList<Type>::fetch_from_front(size_t pos)
{
    BNode<Type> *it = HEAD;
    for (int i = 0; i != pos; ++i)
        it = it->next;
    return it;
}

template<typename Type>
BList<Type>& BList<Type>::push_front(const Type& element)
{
    BNode<Type> *new_node = new BNode<Type>;
    new_node->data = element;
    new_node->next = HEAD;
    new_node->prev = NULL;
    HEAD = new_node;
    if (TAIL == NULL)
        TAIL = new_node;
    ++size;
    return *this;
}



template<typename Type>
BList<Type>& BList<Type>::insert(const Type& elem, size_t pos)
{
    // two guards so that insert doesn't handle TAIL and HEAD changes
    if (pos == 0)
        return push_front(elem);
    if (pos == size)
        return push_back(elem);
    // is_second_half is true if pos lays between [n/2+1;n]
    bool is_second_half = pos > size / 2; 
    BNode<Type> *new_node = new BNode<Type>;
    new_node->data = elem;
    BNode<Type> *el_after_new;
    if (is_second_half) 
        el_after_new = fetch_from_back(size - pos);
    else
        el_after_new = fetch_from_front(pos);
    // before ... [] <-> [] <-> [] ...
    // before ... [prev] <-> NEW <-> [after] <-> [] ...
    new_node->next = el_after_new; // link to [after] for [new]
    new_node->prev = el_after_new->prev; // link to [prev] for [new]
    el_after_new->prev->next = new_node; // for [prev] create link to [new]
    el_after_new->prev = new_node; // for [after] create link to [new]
    ++size;
    return *this;
}

template<typename Type>
BList<Type>& BList<Type>::push_back(const Type& elem)
{
    BNode<Type> *new_node = new BNode<Type>;
    new_node->data = elem;
    new_node->next = NULL;
    new_node->prev = TAIL;
    if (TAIL)
        TAIL->next = new_node;
    if (HEAD == NULL)
        HEAD = new_node;
    TAIL = new_node;
    ++size;
    return *this;
}


template<typename Type>
Type BList<Type>::pop_front()
{
    BNode<Type> *delem = HEAD;
    HEAD = HEAD->next;
    Type retval = delem->data;
    delete delem;
    if (HEAD)
        HEAD->prev = NULL;
    else
        TAIL = NULL;
    --size;
    return retval;
}

template<typename Type>
Type BList<Type>::pop_back()
{
    BNode<Type> *delem = TAIL;
    TAIL = TAIL->prev;
    Type retval = delem->data;
    delete delem;
    if (TAIL)
        TAIL->next = NULL;
    else
        HEAD = NULL;
    --size;
    return retval;
}

template<typename Type>
Type BList<Type>::erase(size_t pos)
{
    if (pos == 0)
        return pop_front();
    if (pos == size - 1)
        return pop_back();
    bool is_second_half = pos > size / 2;
    BNode<Type> delem;
    if (is_second_half)
        delem = fetch_from_back(size - pos);
    else
        delem = fetch_from_front(pos);
    // ... [] <-> [delem] <-> []
    delem->prev->next = delem->next;
    delem->next->prev = delem->prev;
    Type retval = delem->data;
    delete delem;
    --size;
    return retval;
}


template<typename Type>
void BList<Type>::free()
{
    while (HEAD)
        pop_front();
}

template<typename Type>
Type& BList<Type>::get(size_t pos)
{
    bool is_second_half = pos > size / 2;
    BNode<Type> *elem;
    if (is_second_half)
        elem = fetch_from_back(size - pos);
    else
        elem = fetch_from_front(pos);
    return elem->data;
}

#endif
