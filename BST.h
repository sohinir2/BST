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
    template<class T>
    class BST {
    private:
        void traversingInOrder(BSTNode<T> *node, std::vector<T>& v);
        void traversingPreOrder(BSTNode<T> *node, std::vector<T>& v);
        void traversingPostOrder(BSTNode<T> *node, std::vector<T>& v);
        BSTNode<T>* getMin(BSTNode<T> *node);
        BSTNode<T>* getMax(trees::BSTNode<T> *node);
        int getHeight(BSTNode<T>* nd);
        int getOneChild(trees::BSTNode<T> *current);
        int getLeafCount(trees::BSTNode<T> *nd);
        int getSize(BSTNode<T>* nd);

    public:
        BSTNode<T> *root;
        BST<T>();
        BST<T>(std::initializer_list<T> initializerList);
        BST(vector<T>preOrdList, vector<T>inOrdLst);
        int findDistance(T first, T second);
        //~BST();
        bool isLeaf(trees::BSTNode<T> *nd);
        int size();
        int height();
        int leafCount();
        int oneChild();
        void add(const T value);
        BSTNode<T>* find(const T value);
        BSTNode<T>* successor(const T value);
        BSTNode<T>* predecessor(const T value);
        BSTNode<T>* min();
        BSTNode<T>* max();
        void leftRotate(const T value);
        void rightRotate(const T value);
        void deleteNode(T value);
        vector<T> preOrderTraverse();
        vector<T> inOrderTraverse();
        vector<T> postOrderTraverse();
        vector<T> levelOrderTraverse();
        T lessThan(const T value);
        int kThSmallest(int K, trees::BST<T> tree);
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
        add(x);
    }
}

template<class T>
trees::BST<T>::BST(vector<T> preOrdList, vector<T> inOrdLst) {
    preOrdList = preOrderTraverse();
    inOrdLst = inOrderTraverse();
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
bool trees::BST<T>::isLeaf(trees::BSTNode<T> *nd) {
    return nd != nullptr &&
        nd->right == nullptr &&
        nd->left == nullptr;
}

template<class T>
int trees::BST<T>::findDistance(T first, T second) {
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
int trees::BST<T>::oneChild() {
    return getOneChild(root);
}

template<class T>
int trees::BST<T>::getOneChild(BSTNode<T> *current) {
    int count = 0;
    if (current == nullptr) {
        return 0;
    }
    queue<BSTNode<T>*> q;
    q.push(current);
    while (!q.empty()) {
        BSTNode<T>* temp = q.front();
        q.pop();

        if ((!temp->left && temp->right) ||
            (temp->left && !temp->right)) {
            count++;
        }

        if (temp->left != nullptr) {
            q.push(temp->left);
        }
        if (temp->right != nullptr) {
            q.push(temp->right);
        }
    }
    return count;
}

template<class T>
T trees::BST<T>::lessThan(const T value) {
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
int trees::BST<T>::kThSmallest(int K, trees::BST<T> tree) {
    BSTNode<T>* minimum = tree.min();
    for (int i = 0; i < K - 1; i++) {
        minimum = successor(minimum->data);
    }
    return minimum->data;
}


#endif //TREES_BST_H