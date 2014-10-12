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

float Tree::blood = 6;

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
    state = 6;
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
    std::cout<<this->blood;
    this->blood = this->blood - value;
    std::cout<<this->blood;
    log("in setBlood");
    this->showStateAccordingtoBlood();
}

void Tree::showStateAccordingtoBlood() {
    log("in showStateAccordingtoBlood");
    if (blood == 6) {
        state = 6;
        showAnimation();
    }
    if (blood == 5) {
        state = 5;
        showAnimation();
    }
    if (blood == 4) {
        state = 4;
        showAnimation();
    }
    if (blood == 3) {
        state = 3;
        showAnimation();
    }
    if (blood == 2) {
        state = 2;
        showAnimation();
    }
    if (blood == 1) {
        state = 1;
        showAnimation();
    }
    if (blood <= 0) {
        state = 0;
        log("in showStateAccordingtoBlood");
        showAnimation();
    }
}

//show burning or burndown, need to call getState to know which animations to play
void Tree::showAnimation() {
    if(_background == NULL) return;
    //healthy
    
    Fire *fire = NULL;
    
    if(state == 6) {
        
    }
    //burning
    if(state == 5) {
        //Try to add fire
        fire = this->addFire();
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-1.png"));
    }
    if(state == 5) {
    }
    if(state == 4) {
        if(fire == NULL)
            fire = this->addFire();
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-2.png"));
    }
    if(state == 3) {
        if(fire == NULL)
            fire = this->addFire();
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-3.png"));
    }
    if(state == 2) {
        if(fire == NULL)
            fire = this->addFire();
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-4.png"));
    }
    if(state == 1) {
        if(fire == NULL)
            fire = this->addFire();
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-5.png"));
    }
    if(state == 0) {
        log("in showAnimation");
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-6.png"));
        this->treeSprite->removeChild(fire, true);
        //delete this tree
        printf("should delete tree in next step");
        _background->removeChild(this->treeSprite, true);
    }
}

Fire* Tree::addFire() {
    Fire *fire = Fire::create(Fire::FireType::SHOW);
    fire->setScale(0.5, 0.5);
    fire->setPosition(150, 120);
    this->treeSprite->addChild(fire);
    fire->setFire();
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
