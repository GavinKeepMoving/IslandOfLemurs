//
//  Tree.cpp
//  brave
//
//  Created by Wenbo Lin on 10/2/14.
//
//

#include "Tree.h"

float Tree::blood = 10;

//constructor1
Tree::Tree () {
    
}

//constructor2
Tree::Tree(Sprite* background, Sprite* background1) {
    this->background = background;
    this->background1 = background1;
}

//create a single object of Tree
static Tree* createTree() {
    //add object and call initialization
    Tree* newTree = new Tree();
    if(newTree) {
        newTree->autorelease();
        return newTree;
    }
    else {
        delete newTree;
        newTree = NULL;
        return NULL;
    }
}

//initialize a single tree
bool Tree::initSingleTree() {
    state = HEATHY;
    //-----------
    return true;
}

//create trees at the beginning of game
std::vector<Tree*> Tree::initWithTreeNum(int num) {
    std::vector<Tree*> trees;
    for(int i = 0; i < num; i++) {
        trees.push_back(createTree());
        //set tree position according to background position
    }
    return trees;
}

//get blood values
int Tree::getBlood() {
    //call status function
}

//get state: burning or burn down or healthy
Tree::TreeStates getState() {
    
}

//generate banana objects
bool Tree::generateBananas() {
    
}

//show burning or burndown, need to call getState to know which animations to play
bool Tree::showAnimation() {
    TreeStates curState = getState();
    //play curState animation
    
}
