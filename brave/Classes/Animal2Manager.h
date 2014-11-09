//
//  Animal2Manager.h
//  brave
//
//  Created by Lishi Jiang on 10/26/14.
//
//

#ifndef __brave__Animal2Manager__
#define __brave__Animal2Manager__

#include "cocos2d.h"
#include "Animal2.h"
#include "Enemy2.h"
#include "Animal2.h"
class Enemy2;
USING_NS_CC;


class Animal2Manager:public Node
{
public:
    Animal2Manager();
    ~Animal2Manager();
    
    static Animal2Manager* create(Sprite* background);
    
    virtual bool init();
    virtual void update(float dt);/*重写update函数*/
    //void bindPlayer(Player* player);
    
    void bindBackground(Sprite* background);
    Sprite* _background;
    Animal2* createAnimal2s(int index);/*创建Monster对象*/
//    void createAnimal2s(int i);/*创建Monster对象*/
    void setEnemy(__Array* _enemy2Arr){this->_enemy2Arr = _enemy2Arr;}
    int judgeNeayBy(Animal2* animal,std::vector<Enemy2*> enemys);
    Enemy2* getNearestEnemy(Animal2* animal);
    
    private:
    __Array* _enemy2Arr;
    __Array* _animal2Arr;/*存放怪物数组*/
    int mindist = 10;
    //Player* _player;
};


#endif /* defined(__brave__Animal2Manager__) */
