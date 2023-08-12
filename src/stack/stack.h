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
#include "stack.tpp"
#endif

