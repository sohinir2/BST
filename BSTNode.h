//
// Created by Sohini Roy on 5/29/20.
//

#ifndef TREES_BSTNODE_H
#define TREES_BSTNODE_H

#include <iostream>

using namespace std;
namespace trees {
    template<class T>
    class BSTNode {
    public:
        BSTNode *parent;
        BSTNode *left;
        BSTNode *right;
        T data;

    public:
        BSTNode<T>();

        BSTNode<T>(T data);

        BSTNode<T>(const BSTNode<T> &n);

        //BSTNode<T>(BSTNode<T>&& n);
        BSTNode<T> &operator=(const BSTNode<T> &n);
    };
}

template<class T>
trees::BSTNode<T>::BSTNode(){}

template<class T>
trees::BSTNode<T>::BSTNode(T value){
    if(value == NULL)
        throw std::invalid_argument("BSTNode value cannot be null");
    data = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<class T>
trees::BSTNode<T>::BSTNode(const BSTNode<T>& n){
    data = n->data;
    parent = n->parent;
    left = n->left;
    right = n->right;
}

template<class T>
trees::BSTNode<T>& trees::BSTNode<T>::operator=(const BSTNode<T>& n){
    data = n->data;
    parent = n->parent;
    left = n->left;
    right = n->right;
    return *this;
}

#endif //TREES_BSTNODE_H
