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
    
private:
    void createEnemy2s();/*创建Monster对象*/
private:
    __Array* _enemy2Arr;/*存放怪物数组*/
    //Player* _player;
};

#endif /* defined(__brave__Enemy2Manager__) */
