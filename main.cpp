#include <iostream>
#include "BSTNode.h"
#include "BST.h"
#include <vector>

using namespace std;

int main() {
    trees::BST<int> num {15, 5, 3, 12, 10, 6, 7, 13, 16, 20, 18, 23};
    vector<int> v = {3, 6, 7, 10, 12, 13, 15, 16, 18, 20, 23};
    num.deleteNode(5);
    vector<int> v2 = num.inOrderTraverse();
    cout << (v == v2);
}
