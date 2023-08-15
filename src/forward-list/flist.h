#ifndef HINPA_FLIST_H
#define HINPA_FLIST_H
#include <cstddef>
#include <iostream>
// Necessary functions:
// Top(), push(), Insert, Push_back(),Delete(),Pop_back(), Pop_front()


template<typename Type>
class FList {
    struct Node {
        Type data;
        Node *next;
    };

    Node *HEAD = NULL;
    size_t size = 0;

public:
    ~FList() { free(); }
    FList() {};
    FList(const FList &copy);
    FList& operator= (const FList &copy);
    FList& push(const Type& element);
    FList& insert(const Type& element, size_t position = 0);
    FList& append(const Type& element) { return insert(element,size); } 
    Type pop();
    Type pop_back() { return erase(size-1); }
    Type erase(size_t position = 0);
    void free();
    Type& get(size_t position);
    inline Type& top() { return HEAD->data; }
    size_t sz() { return size; }
    void stdout();
};

template<typename Type>
FList<Type>::FList(const FList &copy)
{
    *this = copy;
}

template<typename Type>
FList<Type>& FList<Type>::operator=(const FList &copy)
{
    if (copy.HEAD == NULL) 
    {
        free();
        return *this;
    }
    if (HEAD == NULL)
        HEAD = new Node;
    Node *copy_iterator = copy.HEAD;
    Node *it = HEAD;
    size = copy.size;
    while (it->next && copy_iterator->next)
    {
        it->data = copy_iterator->data;
        it = it->next;
        copy_iterator = copy_iterator->next;
    }
    it->data = copy_iterator->data;
    copy_iterator = copy_iterator->next;
    Node *free_it = it->next;
    while (free_it)
    {
        Node *delem = free_it;
        free_it = free_it->next;
        delete delem;
    }
    while (copy_iterator)
    {
        it->next = new Node;
        it = it->next; 
        it->data = copy_iterator->data;
        copy_iterator = copy_iterator->next;
    }
    it->next = NULL;
    return *this;
}

template<typename Type>
FList<Type>& FList<Type>::push(const Type& elem)
{
    Node *new_elem = new Node;
    new_elem->data = elem;
    new_elem->next = HEAD;
    HEAD = new_elem;
    ++size;
    return *this;
}



// inserts before pos element
template<typename Type>
FList<Type>& FList<Type>::insert(const Type& elem, size_t pos)
{    if (pos == 0)
        return push(elem);
    Node *it = HEAD; // will iterate to prev element for new element
    for (size_t i = 0; i < pos - 1; ++i)
        it = it->next;
    Node *next_elem = it->next;
    Node *new_elem = new Node;
    new_elem->data = elem;
    new_elem->next = next_elem;
    it->next = new_elem;
    ++size;
    return *this;
 }


template<typename Type>
Type FList<Type>::pop()
{
    Node *next = HEAD->next;
    Type retval = HEAD->data;
    delete HEAD;
    HEAD = next;
    --size;
    return retval;
}

template<typename Type>
Type FList<Type>::erase(size_t pos)
{
    if (pos == 0)
        return pop();
    Node *it = HEAD;
    for (size_t i = 0; i < pos - 1; ++i)
        it = it->next;
    Node *delem = it->next;
    Node *after_delem = delem->next;
    it->next = after_delem;
    Type retval = delem->data;
    delete delem;
    --size;
    return retval;
}

template<typename Type>
void FList<Type>::free()
{
    while (HEAD)
        pop();
}

template<typename Type>
Type& FList<Type>::get(size_t pos)
{
    Node *it = HEAD;
    for (int i = 0; i != pos; ++i)
        it = it->next;
    return it->data;
}

template<typename Type>
void FList<Type>::stdout()
{
    Node *temp = HEAD;
    while (temp != NULL) {
        std::cout << temp->data << "\n";
        temp = temp->next;
    }
}

#endif
