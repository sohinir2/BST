//
// Created by Sohini Roy on 6/13/20.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../BSTExtras.h"
#include "../BST.h"
#include "../BSTNode.h"


TEST_CASE("Sanity check", "[sanity]") {
    REQUIRE((1 + 1) == 2);
}

TEST_CASE("Predecessor", "[predecessor]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    int res = ex2.predecessor(2)->data;
    REQUIRE(res == 1);
}

TEST_CASE("Successor", "[successor]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    int res = ex2.successor(1)->data;
    REQUIRE(res == 2);
}

TEST_CASE("Find", "[find]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    int res = ex2.find(5)->data;
    REQUIRE(res == 5);
}

TEST_CASE("Minimum", "[min-max]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    int res = ex2.min()->data;
    REQUIRE(res == 1);
}

TEST_CASE("Maximum", "[min-max]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    int res = ex2.max()->data;
    REQUIRE(res == 25);
}

TEST_CASE("Size", "[size]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    int res = ex2.size();
    REQUIRE(res == 9);
}

TEST_CASE("Leaf count", "[leaf-count]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    trees::BSTExtras<int> ex3(&ex2);
    int res = ex3.leafCount();
    REQUIRE(res == 5);
}

TEST_CASE("Find distance (same subtree)", "[dist]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    trees::BSTExtras<int> ex3(&ex2);
    int res = ex3.findDistance(2, 3);
    REQUIRE(res == 1);
}

TEST_CASE("Find distance (different subtree)", "[dist]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    trees::BSTExtras<int> ex3(&ex2);
    int res = ex3.findDistance(2, 21);
    REQUIRE(res == 3);
}

TEST_CASE("One child", "[one-child]") {
    trees::BST<int> ex2 = {5, 2, 12, 1, 3, 9, 21, 19, 25};
    trees::BSTExtras<int> ex3(&ex2);
    int res = ex3.oneChild();
    REQUIRE(res == 0);
}
