//
// Created by Sohini Roy on 5/29/20.
//

#ifndef TREES_BST_H
#define TREES_BST_H

#include <iostream>
#include <vector>
#include "BSTNode.h"

using namespace std;
namespace trees {
    template<class T>
    class BST {
    private:
        void traversingInOrder(BSTNode<T> *node, std::vector<T>& v);
        void traversingPreOrder(BSTNode<T> *node, std::vector<T>& v);
        void traversingPostOrder(BSTNode<T> *node, std::vector<T>& v);
        BSTNode<T>* getMin(BSTNode<T> *node);
        BSTNode<T>* getMax(trees::BSTNode<T> *node);
        int getHeight(BSTNode<T>* nd);

    public:
        BSTNode<T> *root;
        BST<T>();
        BST<T>(std::initializer_list<T> initializerList);
        //~BST();
        int size();
        int height();
        int leafCount();
        int getLeafCount(trees::BSTNode<T> *nd);
        void add(const T value);
        BSTNode<T>* find(const T value);
        BSTNode<T>* successor(const T value);
        BSTNode<T>* predecessor(const T value);
        BSTNode<T>* min();
        BSTNode<T>* max();
        //void leftRotate(const T value);
        //void rightRotate(const T value);
        void deleteNode(T value);
        vector<T> preOrderTraverse();
        vector<T> inOrderTraverse();
        vector<T> postOrderTraverse();
        //void deleteTree(BSTNode<T> *node);
        int getSize(BSTNode<T>* nd);
    };
}
template<class T>
trees::BST<T>::BST() {
    root = nullptr;
}

template<class T>
trees::BST<T>::BST(initializer_list<T> initializerList) {
    root = nullptr;
    for (auto x : initializerList) {
        add(x);
    }
}

template<class T>
trees::BSTNode<T> *trees::BST<T>::find(const T value) {
    BSTNode<T> *current = root;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        } else if (current->data > value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

template<class T>
void trees::BST<T>::add(const T value) {
    if (root == nullptr) {
        root = new BSTNode<T>(value);
    } else {
        BSTNode<T> *current = root;
        BSTNode<T> *par = nullptr;
        while (current != nullptr) {
            if (current->data > value) {
                par = current;
                current = current->left;
            } else if (current->data < value) {
                par = current;
                current = current->right;
            }
        }
        if (par->data < value) {
            par->right = new BSTNode<T>(value);
            par->right->parent = par;
        } else if (par->data > value) {
            par->left = new BSTNode<T>(value);
            par->left->parent = par;
        } else {
            cout << "Cannot handle duplicate values" << endl;
        }
    }
}

template<class T>
trees::BSTNode<T> *trees::BST<T>::getMin(trees::BSTNode<T> *node) {
    BSTNode<T> *current = node;
    while (current != nullptr) {
        if (current->left == nullptr) {
            return current;
        } else {
            current = current->left;
        }
    }
    return nullptr;
}

template<class T>
trees::BSTNode<T> *trees::BST<T>::getMax(trees::BSTNode<T> *node) {
    BSTNode<T> *current = node;
    while (current != nullptr) {
        if (current->right == nullptr) {
            return current;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

template<class T>
trees::BSTNode<T> *trees::BST<T>::min() {
    return getMin(root);
}

template<class T>
trees::BSTNode<T> *trees::BST<T>::max() {
    return getMax(root);
}

template<class T>
vector<T> trees::BST<T>::preOrderTraverse() {
    std::vector<T> v;
    traversingPreOrder(root, v);
    return v;
}



template<class T>
vector<T> trees::BST<T>::inOrderTraverse() {
    std::vector<T> v;
    traversingInOrder(root, v);
    return v;
}

template<class T>
vector<T> trees::BST<T>::postOrderTraverse() {
    std::vector<T> v;
    traversingPostOrder(root, v);
    return v;
}

template<class T>
void trees::BST<T>::traversingInOrder(trees::BSTNode<T> *node, vector<T> &v) {
    if (node != nullptr) {
        traversingInOrder(node->left, v );
        v.push_back(node->data);
        traversingInOrder(node->right, v);
    }
}
template<class T>
void trees::BST<T>::traversingPreOrder(trees::BSTNode<T> *node, vector<T> &v) {
    if (node != nullptr) {
        v.push_back(node->data);
        traversingPreOrder(node->left, v );
        traversingPreOrder(node->right, v);
    }
}

template<class T>
void trees::BST<T>::traversingPostOrder(trees::BSTNode<T> *node, vector<T> &v) {
    if (node != nullptr) {
        traversingPostOrder(node->left, v );
        traversingPostOrder(node->right, v);
        v.push_back(node->data);
    }
}

template<class T>
trees::BSTNode<T> *trees::BST<T>::predecessor(const T value) {
    BSTNode<T> *node = find(value);
    if (node == nullptr) {
        return node;
    }
    if (node->left != nullptr) {
        return getMin(node->left);
    } else {
        while (node != nullptr && node->parent != nullptr && node->parent->left == node) {
            node = node->parent;
        }
    }
    return node->parent;
}

template<class T>
trees::BSTNode<T> *trees::BST<T>::successor(const T value) {
    BSTNode<T> *node = find(value);
    if (node == nullptr) {
        return node;
    }
    if (node->right != nullptr) {
        return getMin(node->right);
    } else {
        while (node != nullptr && node->parent != nullptr && node->parent->right == node) {
            node = node->parent;
        }
    }
    return node->parent;
}

template<class T>
int trees::BST<T>::getSize(trees::BSTNode<T>* nd) {
    BSTNode<T>* current = nd;
    if (current == nullptr) {
        return 0;
    } else {
        return getSize(current->left) + getSize(current->right) + 1;
    }
}

template<class T>
int trees::BST<T>::size() {
    return getSize(root);
}

template<class T>
int trees::BST<T>::getHeight(trees::BSTNode<T> *nd) {
    BSTNode<T>* current = nd;
    if (current == nullptr) {
        return 0;
    } else {
        int left = getHeight(current->left);
        int right = getHeight(current->right);
        if (left > right) {
            return left + 1;
        } else {
            return right + 1;
        }
    }
}

template<class T>
int trees::BST<T>::height() {
    return getHeight(root) - 1;
}

template<class T>
int trees::BST<T>::getLeafCount(trees::BSTNode<T> *nd) {
    BSTNode<T>* current = nd;
    if (current == nullptr) {
        return 0;
    } else if (current->left == nullptr && current->right == nullptr) {
        return 1;
    } else {
        int leafcount = getLeafCount(current->left) + getLeafCount(current->right);
        return leafcount;
    }
}

template<class T>
int trees::BST<T>::leafCount() {
    return getLeafCount(root);
}

template<class T>
void trees::BST<T>::deleteNode(T value) {
    BSTNode<T>* current = find(value);
    if (current == nullptr) {
        return;
    }
    if (current->left == nullptr && current->right == nullptr) {
        if (current == current->parent->right) {
            current->parent->right = nullptr;
        } else {
            current->parent->left = nullptr;
        }
        delete current;
    } else if ((current->left == nullptr && current->right != nullptr) ||
            (current->left != nullptr && current->right == nullptr)) {
        if (current->left == nullptr && current->right != nullptr) {
            if (current == current->parent->right) {
                current->parent->right = current->right;
            }
            else {
                current->parent->left = current->right;
            }
        } else {
            if (current == current->parent->left) {
                current->parent->left = current->left;
            } else {
                current->parent->right = current->left;
            }
        }
        delete current;
    } else {
        BSTNode<T>* success = successor(current->data);
        if (success->left == nullptr && success->right == nullptr) {
            current->data = success->data;
            current->right = nullptr;
        } else {
            if (success == success->parent->right) {
                success->parent->right = success->right;
            } else {
                success->parent->left = success->right;
            }
            current->data = success->data;
        }
    }
}


#endif //TREES_BST_H