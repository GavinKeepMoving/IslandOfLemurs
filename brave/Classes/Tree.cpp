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
    _posX = tree->getPosition().x;
    _posY = tree->getPosition().y;
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
void Tree::showAnimation(int state, Sprite* background) {
    if(background == NULL) return;
    //healthy
    if(state == 0) {
        
    }
    //burning
    if(state == 1) {
        auto fireSprite = Sprite::create("image/fire/flame.png");
        fireSprite->setPosition(150,90);
        this->treeSprite->addChild(fireSprite);
    }
    //burn up
    if(state == 2) {
        background->removeChild(this->treeSprite, true);
        this->treeSprite = Sprite::create("image/trees/bareTree.png");
        this->treeSprite->setPosition(_posX, _posY);
        background->addChild(this->treeSprite);
    }
}
