//
// Created by Sohini Roy on 5/29/20.
//

#ifndef TREES_BST_H
#define TREES_BST_H

#include <iostream>
#include <vector>
#include <queue>
#include "BSTNode.h"

using namespace std;
namespace trees {
    enum Direction {
        Left,
        Right,
    };
    template<class T>
    class BST {
    private:
        void traversingInOrder(BSTNode<T> *node, std::vector<T>& v);
        void traversingPreOrder(BSTNode<T> *node, std::vector<T>& v);
        void traversingPostOrder(BSTNode<T> *node, std::vector<T>& v);
        trees::BSTNode<T> *findParentforAdd(const T value);
        BSTNode<T>* getMin(BSTNode<T> *node);
        BSTNode<T>* getMax(trees::BSTNode<T> *node);
        int getHeight(BSTNode<T>* nd);
        int getSize(BSTNode<T>* nd);

    public:
        BSTNode<T> *root;
        BST<T>();
        BST<T>(std::initializer_list<T> initializerList);
        BST(vector<T>preOrdList, vector<T>inOrdLst);
        //~BST();
        int size();
        int height();
        bool isLeaf(BSTNode<T> *nd);
        bool isLeftChild(BSTNode<T>* nd);
        bool isRightChild(BSTNode<T>* nd);
        void addNode(const T value);
        virtual void addNode(BSTNode<T> *node);
        BSTNode<T>* find(const T value);
        BSTNode<T>* successor(const T value);
        BSTNode<T>* predecessor(const T value);
        BSTNode<T>* min();
        BSTNode<T>* max();
        void leftRotate(const T value);
        void rightRotate(const T value);
        void rotateNode(T value, Direction dir);
        void deleteNode(T value);
        vector<T> preOrderTraverse();
        vector<T> inOrderTraverse();
        vector<T> postOrderTraverse();
        vector<T> levelOrderTraverse();
        //T lessThan(const T value);
        //int kThSmallest(int K, trees::BST<T> tree);
        //vector<T> zigzagLevelOrderTraverse();
        //void deleteTree(BSTNode<T> *node);
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
        addNode(x);
    }
}

template<class T>
trees::BST<T>::BST(vector<T> preOrdList, vector<T> inOrdLst) {
    preOrdList = preOrderTraverse();
    inOrdLst = inOrderTraverse();
}
template<class T>
bool trees::BST<T>::isLeaf(trees::BSTNode<T> *nd) {
    return nd != nullptr &&
           nd->right == nullptr &&
           nd->left == nullptr;
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

template <class T>
trees::BSTNode<T> *trees::BST<T>::findParentforAdd(const T value) {
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
    return par;
}

template<class T>
void trees::BST<T>::addNode(const T value) {
    if (root == nullptr) {
        root = new BSTNode<T>(value);
    } else {
        BSTNode<T> *current = root;
        BSTNode<T> *par = findParentforAdd(value);
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
void trees::BST<T>::addNode(BSTNode <T> *node) {
    if (root == nullptr) {
        root = node;
    } else {
        BSTNode<T> *current = root;
        BSTNode<T> *par = findParentforAdd(node->data);
        if (par->data < node->data) {
            par->right = node;
            par->right->parent = par;
        } else if (par->data > node->data) {
            par->left = node;
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
        traversingInOrder(node->left, v);
        v.push_back(node->data);
        traversingInOrder(node->right, v);
    }
}
template<class T>
void trees::BST<T>::traversingPreOrder(trees::BSTNode<T> *node, vector<T> &v) {
    if (node != nullptr) {
        v.push_back(node->data);
        traversingPreOrder(node->left, v);
        traversingPreOrder(node->right, v);
    }
}

template<class T>
void trees::BST<T>::traversingPostOrder(trees::BSTNode<T> *node, vector<T> &v) {
    if (node != nullptr) {
        traversingPostOrder(node->left, v);
        traversingPostOrder(node->right, v);
        v.push_back(node->data);
    }
}

template<class T>
vector<T> trees::BST<T>::levelOrderTraverse() {
    queue<BSTNode<T>*> Q;
    Q.push(root);
    vector<T> v;

    while (Q.size() != 0) {
        BSTNode<T>* current = Q.front();
        Q.pop();
        v.push_back(current->data);
        if (current->left != nullptr) {
            Q.push(current->left);
        }
        if (current->right != nullptr) {
            Q.push(current->right);
        }
    }
    return v;
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

template<class T>
void trees::BST<T>::rightRotate(const T value) {
    BSTNode<T> *node = find(value);
    if (node == nullptr) {
        return;
    }
    if (isLeaf(node)) {
        return;
    }   else {
        BSTNode<T> *par = node->parent;
        if (par == nullptr) {
            if (node->left != nullptr) {
                BSTNode<T> *leftNode = node->left;
                node->left = leftNode->right;
                root = leftNode;
                root->right = node;
                node->parent = root;
            }
        }
    }
}

template<class T>
void trees::BST<T>::leftRotate(const T value) {
    BSTNode<T> *node = find(value);
    if (node == nullptr) {
        return;
    }
    if (isLeaf(node)) {
        return;
    }   else {
        BSTNode<T> *par = node->parent;
        if (par == nullptr) {
            if (node->right != nullptr) {
                BSTNode<T> *rightNode = node->right;
                node->right = rightNode->left;
                root = rightNode;
                root->left = node;
                node->parent = root;
            }
        }
    }
}
template<class T>

void trees::BST<T>::rotateNode(T value, Direction dir){
    //Find the node corresponding to the value supplied
    BSTNode<T>* nodeToRotate = find(value);
    //Can't do much if value is not found in the tree

    if(nodeToRotate == nullptr) {
        return;
    }
    if((dir == Right && nodeToRotate->left == nullptr) || (dir == Left && nodeToRotate->right == nullptr)) {
        return;
    }

    BSTNode<T>* newParent = (dir == Left)?nodeToRotate->right:nodeToRotate->left;
    BSTNode<T>* grandParent = nodeToRotate->parent;

    if(grandParent) {
        if(isLeftChild(nodeToRotate)) {
            grandParent->left = newParent;
        }
        else {
            grandParent->right = newParent;
        }
        newParent->parent = grandParent;
    }

    else {
        root = newParent;
    }
    if(dir == Left){
        nodeToRotate->right = newParent->left;
        newParent->left = nodeToRotate;

    }
    else {
        nodeToRotate->left = newParent->right;
        newParent->right = nodeToRotate;
    }
    nodeToRotate->parent = newParent;

    if(newParent != nullptr)
        newParent->parent = grandParent;
    return;
}

template<class T>
bool trees::BST<T>::isLeftChild(trees::BSTNode<T> *nd) {
    return (nd != nullptr && (nd->parent->left == nd));
}

template<class T>
bool trees::BST<T>::isRightChild(trees::BSTNode<T> *nd) {
    return (nd != nullptr && (nd->parent->right == nd));
}


#endif //TREES_BST_H