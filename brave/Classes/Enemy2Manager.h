//
//  Enemy2Manager.h
//  brave
//
//  Created by Lishi Jiang on 10/19/14.
//
//

#ifndef __brave__Enemy2Manager__
#define __brave__Enemy2Manager__

#include "cocos2d.h"
#include "Enemy2.h"
#include "Animal2.h"
#include "Tree.h"
#include "MainScene.h"
#include <iostream>
class Animal2;
class MainScene;

USING_NS_CC;

#define MAX_ENEMY2_NUM 10

class Enemy2Manager:public Node
{
public:
    Enemy2Manager();
    ~Enemy2Manager();
    
    static Enemy2Manager* create(Sprite* background);
    
    virtual bool init();
    virtual void update(float dt);/*重写update函数*/
    //void bindPlayer(Player* player);
    
    void bindBackground(Sprite* background);
    Sprite* _background;
    /****/
    void createAnimal2s(int index); /* create a animal object */
    void getAnimals(std::vector<Animal*> _animals){this->_animals = _animals;}
    void setTrees(std::vector<Tree*> _trees){this->_trees = _trees;}
    void setAnimales(__Array* _animal2Arr){this->_animal2Arr = _animal2Arr;}
    int judgeNearby(const Vec2& pos,Enemy2* enemy,std::vector<Tree*> trees,std::vector<Animal2*> animal);
    Enemy2* createEnemy2s(int order);/*创建Monster对象*/
    /****/
    
private:
    
    
private:
    std::vector<Animal*> _animals;
    std::vector<Tree*> _trees;
    __Array* _animal2Arr;
    __Array* _enemy2Arr; /*存放怪物数组*/
    //Player* _player;
};

#endif /* defined(__brave__Enemy2Manager__) */
