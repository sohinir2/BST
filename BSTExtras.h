//
// Created by Sohini Roy on 6/13/20.
//

#ifndef BST_BSTEXTRAS_H
#define BST_BSTEXTRAS_H
#include <iostream>
#include <vector>
#include <queue>
#include "BST.h"
#include "BSTNode.h"
#include <initializer_list>

using namespace std;
namespace trees {
    template<class T>
    class BSTExtras {
    private:
        int getOneChild(trees::BSTNode<T> *current);
        int getLeafCount(trees::BSTNode<T> *nd);

    public:
        BSTNode<T> *root;
        BSTExtras<T>(BST<T>* ref);

        BSTExtras<T>();

        BSTExtras<T>(initializer_list<T> initializerList);

        int findDistance(T first, T second);

        //~BST();
        //bool isLeaf(trees::BSTNode<T> *nd);

        int leafCount();

        int oneChild();

        T lessThan(const T value);

        int kThSmallest(int K, trees::BST<T> tree);
        //vector<T> zigzagLevelOrderTraverse();
        //void deleteTree(BSTNode<T> *node);
    };
}
template<class T>
trees::BSTExtras<T>::BSTExtras(trees::BST<T> *ref) {
    root = ref->root;
}

template<class T>
int trees::BSTExtras<T>::getLeafCount(trees::BSTNode<T> *nd) {
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
int trees::BSTExtras<T>::leafCount() {
    return getLeafCount(root);
}

template<class T>
int trees::BSTExtras<T>::findDistance(T first, T second) {
    int firstCount = 0;
    int secondCount = 0;

    BSTNode<T>* firstCurrent = root;
    BSTNode<T>* secondCurrent = root;
    if (firstCurrent == nullptr) {
        return 0;
    }
    if (secondCurrent == nullptr) {
        return 0;
    }
    while (firstCurrent != nullptr) {
        if (firstCurrent->data < first) {
            firstCurrent = firstCurrent->right;
            firstCount++;
        } else if (firstCurrent->data > first) {
            firstCurrent = firstCurrent->left;
            firstCount++;
        } else {
            break;
        }
    }
    while (secondCurrent != nullptr) {
        if (secondCurrent->data < second) {
            secondCurrent = secondCurrent->right;
            secondCount++;
        } else if (secondCurrent->data > second) {
            secondCurrent = secondCurrent->left;
            secondCount++;
        } else {
            break;
        }
    }
    if ((first > root->data && second > root->data) ||
        (first < root->data && second < root->data)) {
        return abs(firstCount-secondCount);
    } else {
        return firstCount+secondCount;
    }
}

template<class T>
int trees::BSTExtras<T>::oneChild() {
    return getOneChild(root);
}

template<class T>
int trees::BSTExtras<T>::getOneChild(BSTNode<T> *current) {
    int count = 0;
    if (current == nullptr) {
        return 0;
    }
    queue<BSTNode<T>*> q;
    q.push(current);
    while (!q.empty()) {
        BSTNode<T>* nd = q.front();
        q.pop();

        if ((!nd->left && nd->right) ||
            (nd->left && !nd->right)) {
            count++;
        }

        if (nd->left != nullptr) {
            q.push(nd->left);
        }
        if (nd->right != nullptr) {
            q.push(nd->right);
        }
    }
    return count;
}

template<class T>
T trees::BSTExtras<T>::lessThan(const T value) {
    BSTNode<T>* current = root;

    if (current == nullptr) {
        return -1;
    }
    if (current->data == value) {
        return current->data;
    } else {
        if (current->data < value) {
            current = current->right;
            if (current->right->data > value) {
                if (current->data <= value) {
                    return current->data;
                } else {
                    current = current->left;
                    return current->data;
                }
            } else {
                current = current->right;
                if (current->data <= value) {
                    return current->data;
                } else {
                    current = current->left;
                    return current->data;
                }
            }
        } else if (current->data > value) {
            current = current->left;
            if (current->right != nullptr) {
                current = current->right;
                return current->data;
            }
        }
    }
}

template<class T>
int trees::BSTExtras<T>::kThSmallest(int K, trees::BST<T> tree) {
    BSTNode<T>* minimum = tree.min();
    for (int i = 0; i < K - 1; i++) {
        minimum = successor(minimum->data);
    }
    return minimum->data;
}


#endif //TREES_BST_H
