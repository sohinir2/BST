cmake_minimum_required(VERSION 3.15)
project(BST)

set(CMAKE_CXX_STANDARD 14)

add_executable(BST main.cpp BSTNode.h BST.h Catch_tests/BSTtest.cpp BSTExtras.h AVLNode.h AVL.h)
add_subdirectory(Catch_tests)