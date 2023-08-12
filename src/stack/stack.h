#ifndef HINPA_STACK_H
#define HINPA_STACK_H
#include <cstddef>
#include <stdexcept>
#include <iostream>



template<typename Type>
class Stack {
    // Do I need to encapsulate Node struct?  
    struct Node {
        Type data;
        Node *next;
    };
    Node *HEAD = NULL;
    size_t size = 0;
public:
    Type pop();
    Stack& push(Type data);
    Type& top();
    void free();
    ~Stack()
    {
        free();
    }
    Stack() {};
    Stack(const Stack &copy);
    Stack &operator= (const Stack &copy);
    size_t sz() { return size; }
    void stdoutPrint();
};
template<typename Type>
Stack<Type>::Stack(const Stack &copy)
{
    *this = copy;
}

template<typename Type>
Stack<Type>& Stack<Type>::operator=(const Stack &copy)
{
    free();
    Node *copy_iterator = copy.HEAD;
    while (copy_iterator != NULL)
    {
        push(copy_iterator->data);
        copy_iterator = copy_iterator->next;
    }
    return *this;
}

template<typename Type>
Type Stack<Type>::pop()
{
    if (HEAD == NULL)
    {
        throw std::out_of_range("Popping an empty stack!");
    }
    Node *next_element = HEAD->next;
    Type retval = HEAD->data;
    delete HEAD;
    HEAD = next_element;
    --size;
    return retval;
}

template<typename Type>
inline Type& Stack<Type>::top()
{
    return HEAD->data;
}

template<typename Type>
Stack<Type> &Stack<Type>::push(Type data)
{
    Node *new_node = new Node;
    new_node->data = data;
    new_node->next = HEAD;
    HEAD = new_node;
    ++size;
    return *this;
}

template<typename Type>
void Stack<Type>::free()
{
    while (HEAD != NULL)
        pop();
}
template<typename Type>
void Stack<Type>::stdoutPrint()
{
    Node *temp = HEAD;
    while (temp != NULL) {
        std::cout << temp->data << "\n";
        temp = temp->next;
    }
}
#endif
