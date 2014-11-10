//
//  Tree.cpp
//  brave
//
//  Created by Wenbo Lin on 10/2/14.
//
//

#include "Tree.h"
#include "MainScene.h"

extern MainScene *mainLayer;

//float Tree::blood = 6;
#define originalBlood 100

//constructor1
Tree::Tree () {
    
}

//constructor2
Tree::Tree(Sprite* tree, BananaManger* bm, Sprite* background) {
    this->treeSprite = tree;
    _posX = tree->getPosition().x;
    _posY = tree->getPosition().y;
    blood = (float)originalBlood;
    auto s = tree->getContentSize();


    
    _bananaArr = bm->_bananaArr;
    auto banana=Banana::create();
    banana->bindSprite(Sprite::create("fruit.png"));
    banana->_background = background;
    banana->setPosition(Vec2(s.width*0.35,s.height*0.75));
    this->treeSprite->addChild(banana);
    bm->_bananaArr->addObject(banana);
    
    banana=Banana::create();
    banana->bindSprite(Sprite::create("fruit.png"));
    banana->_background = background;
    banana->setPosition(Vec2(s.width*0.50,s.height*0.75));
    this->treeSprite->addChild(banana);
    bm->_bananaArr->addObject(banana);
    
    banana=Banana::create();
    banana->bindSprite(Sprite::create("fruit.png"));
    banana->_background = background;
    banana->setPosition(Vec2(s.width*0.65,s.height*0.75));
    this->treeSprite->addChild(banana);
    bm->_bananaArr->addObject(banana);/*添加到数组中，便于管理*/
    
    state = 6;
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
int Tree::setBlood(int value) {
    log("in setBlood");
    this->blood -= value;
    this->showStateAccordingtoBlood();
    return this->blood;
}

void Tree::showStateAccordingtoBlood() {
    log("in showStateAccordingtoBlood");
    if (blood >= originalBlood * 0.8) {
        log("in 80");
        state = 6;
        showAnimation();
    }
    
    else if (blood >= originalBlood * 0.7) {
        log("in 70");
        state = 5;
        showAnimation();
    }
    else if (blood >= originalBlood * 0.5) {
        log("in 50");
        state = 4;
        showAnimation();
    }
    else if (blood >= originalBlood * 0.3) {
        log("in 30");
        state = 3;
        showAnimation();
    }
    else if (blood >= originalBlood * 0.1) {
        log("in 10");
        state = 2;
        showAnimation();
    }
    else if (blood >= originalBlood * 0.01) {
        log("in 1");
        state = 1;
        showAnimation();
    }
     
    else if (blood <= 0) {
        log("in 0");
        state = 0;
        showAnimation();
    }
}

//show burning or burndown, need to call getState to know which animations to play
void Tree::showAnimation() {
    if(_background == NULL) return;
    //healthy
    
    Fire *fire = NULL;
    
    //add sound
    if(state < 6 && state > 1) {
        _soundEffectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("AudioClip/Fire.wav");
    }
    
    if(state == 6) {
        if(fire != NULL)
            this->removeChild(fire, true);
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree.png"));
    }
    //burning
    if(state == 5) {
        //Try to add fire
        if(fire != NULL)
            this->removeChild(fire, true);
        fire = this->addFire(6 - state);
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-1.png"));
    }
    if(state == 4) {
        if(fire != NULL)
            this->removeChild(fire, true);
        fire = this->addFire(6 - state);
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-2.png"));
    }
    if(state == 3) {
        if(fire != NULL)
            this->removeChild(fire, true);
        fire = this->addFire(6 - state);
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-3.png"));
    }
    if(state == 2) {
        if(fire != NULL)
            this->removeChild(fire, true);
        fire = this->addFire(6 - state);
        CCTextureCache *sharedTextureCache = new CCTextureCache();
        this->treeSprite->setTexture(sharedTextureCache->addImage("image/trees/tree-4.png"));
    }
    if(state == 1) {
        if(fire != NULL)
            this->removeChild(fire, true);
        fire = this->addFire(6 - state);
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
        //for(auto b : this->treeSprite->getChildren()){
        //    delete b;
        //}
        _bananaArr->removeLastObject();
        _bananaArr->removeLastObject();
        _bananaArr->removeLastObject();
        this->treeSprite->removeAllChildrenWithCleanup(true);
        _background->removeChild(this->treeSprite, true);
    }
}

Fire* Tree::addFire(int scale) {
    Fire *fire = Fire::create(Fire::FireType::SHOW);
    fire->setScale(0.2 * scale, 0.2 * scale);
    fire->setPosition(240, 200);
    this->treeSprite->addChild(fire);
    fire->setFire();
}

//return tree right boundary
float Tree::getRightBoundary() {
    auto leftCorner = treeSprite->getPosition();
    auto leftX = leftCorner.x;
    auto rightX = leftCorner.x + this->getContentSize().width;
    return rightX;
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
