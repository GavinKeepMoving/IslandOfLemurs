//
//  Tree.cpp
//  brave
//
//  Created by Wenbo Lin on 10/2/14.
//
//

#include "Tree.h"
#include "Fire.h"
#include "MainScene.h"

extern MainScene *mainLayer;

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
    state = 0;
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

//set blood value
void Tree::setBlood(int value) {
    this->blood = value;
}

//get blood values
int Tree::getBlood(Tree* tree) {
    //call status function
    return this->blood;
}

//get state: burning or burn down or healthy
int Tree::getState(Tree* tree) {
    return this->state;
}

//generate banana objects
bool Tree::generateBananas(Tree* tree) {
    return true;
}

void Tree::showStateAccordingtoBlood() {
    if (blood == 6) {
        state = 6;
        showAnimation(_background);
    }
    if (blood == 5) {
        state = 5;
        showAnimation(_background);
    }
    if (blood == 4) {
        state = 4;
        showAnimation(_background);
    }
    if (blood == 3) {
        state = 3;
        showAnimation(_background);
    }
    if (blood == 2) {
        state = 2;
        showAnimation(_background);
    }
    if (blood == 1) {
        state = 1;
        showAnimation(_background);
    }
    if (blood == 0) {
        state = 0;
        showAnimation(_background);
    }
}

//show burning or burndown, need to call getState to know which animations to play
void Tree::showAnimation(Sprite* background) {
    if(background == NULL) return;
    //healthy
    
    Fire *fire;
    
    if(state == 6) {
        
    }
    //burning
    if(state == 5) {
        //Try to add fire
        fire = this->addFire();
    }
    if(state == 5) {
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-1.png"));
    }
    if(state == 4) {
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-2.png"));
    }
    if(state == 3) {
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-3.png"));
    }
    if(state == 2) {
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-4.png"));
    }
    if(state == 1) {
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-5.png"));
    }
    if(state == 0) {
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-6.png"));
        this->treeSprite->removeChild(fire, true);
    }
}

Fire* Tree::addFire() {
    Fire *fire = Fire::create(Fire::FireType::SHOW);
    fire->setScale(0.5, 0.5);
    fire->setPosition(150, 120);
    this->treeSprite->addChild(fire);
    fire->setFire();
}
