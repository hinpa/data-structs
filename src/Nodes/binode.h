#ifndef HINPA_BNODE_H
#define HINPA_BNODE_H
template<typename Type>
struct BNode {
    Type data;
    BNode *next;
    BNode *prev;
};

#endif
