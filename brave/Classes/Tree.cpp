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
Tree::Tree(Sprite* tree) {
    this->treeSprite = tree;
}

//initialize a single tree
bool Tree::initSingleTree() {
    state = HEATHY;
    //-----------
    return true;
}

//create trees at the beginning of game
/*
std::vector<Tree*> Tree::initWithTreeNum(int num) {
    int beginningPos = 300;
    std::vector<Tree*> trees;
    for(int i = 0; i < num; i++) {
        auto treeSprite = Sprite::create("image/tree.png");
        treeSprite->setPosition(200, beginningPos);
        trees.push_back();
        //set tree position according to background position
    }
    return trees;
}
 */

//get blood values
int Tree::getBlood(Tree* tree) {
    //call status function
    return 0;
}

//get state: burning or burn down or healthy
int Tree::getState(Tree* tree) {
    return 0;
}

//generate banana objects
bool Tree::generateBananas(Tree* tree) {
    return true;
}

//show burning or burndown, need to call getState to know which animations to play
bool Tree::showAnimation(Tree* tree) {
    int curState = Tree::getState(tree);
    //play curState animation
    return true;
}
