//
// Created by Pavel on 10.06.2022.
//

# pragma once
# include <iostream>
# include <vector>
#define MAX_VALUE 0xFFFFFFFF
using namespace std ;

struct tnode {
    long value = 0;
    long sum = 0;
    long level = 0;
    struct tnode *left = NULL;
    struct tnode *right = NULL;
};

tnode* addNode(long v, long level, tnode *tree );

tnode* makeNewTree(long v, long level, tnode *tree );