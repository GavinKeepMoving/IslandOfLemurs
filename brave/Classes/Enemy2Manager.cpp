//
//  Enemy2Manager.cpp
//  brave
//
//  Created by Lishi Jiang on 10/19/14.
//
//

#include "Enemy2Manager.h"

#define max_Banana_num 2

Enemy2Manager::Enemy2Manager(){}

Enemy2Manager::~Enemy2Manager(){}

Enemy2Manager* Enemy2Manager::create(Sprite* background)
{
    Enemy2Manager* enemy2Manager = new Enemy2Manager();
//    this->getTrees();
    enemy2Manager->_background = background;
//    enemy2Manager->init();
    return enemy2Manager;
}

bool Enemy2Manager::init()
{
    bool bRet=false;
    do
    {
        createEnemy2s();/*创建怪物*/
        //this->schedule(schedule_selector(Enemy2Manager::update), 0.5);
        //this->scheduleUpdate();/*启用update*/
        bRet=true;
    } while (0);
    return bRet;
    
}


Enemy2* Enemy2Manager::createEnemy2s()
{
//    _enemy2Arr=__Array::create();
//    _enemy2Arr->retain();

    
//    for(int i=0;i<max_Banana_num; i++)
//    {
        auto enemy2=Enemy2::create();
        enemy2->_background = this->_background;
//        enemy2->setPosition(950 + i * 70, 430);
        enemy2->setPosition(1800,130);
        this->addChild(enemy2);  /*将怪物添加到管理器(CCNode)中*/
//        _enemy2Arr->addObject(enemy2);/*添加到数组中，便于管理*/
//    }
	
    return enemy2;
}

//void Enemy2Manager::createAnimal2s(int index)
//{
//    _animal2Arr = __Array::create();
//    _animal2Arr->retain();
//    
//    
//}

void Enemy2Manager::update(float dt)
{
    
//    CCObject* obj=NULL;
//    Enemy2* enemy2=NULL;
//    
//    CCARRAY_FOREACH(_enemy2Arr,obj)/*循环遍历怪物数组，重复出现在屏幕上*/
//    {
//        //need LIU ZHE HELP
//        //每次会遍历所有的enemy的位置。使用setState就会改变动画。
//        //但是我不会使用你的判断函数。星号里面是我需要你帮忙修改的地方。
//        //attack什么的会自己停下来的。应该和以前的状态机很相似。
//        enemy2=(Enemy2*) obj;
//        // judge for the tree, main character and helpers
//        //******
//        int index = judgeNearby(enemy2);
//        if (index == -1){
//            enemy2->setState(WALK);
//        }
//        else{
//            enemy2->setState(ATTACK);
//            int state = _trees.back()->setBlood(enemy2->getAttack());
//            if (state <= 0){
//                
//            }
//        }
//        //*****
//        enemy2->update(dt);
//    }
}

// need judge for trees, animals, lemur
int Enemy2Manager::judgeNearby(Enemy2* enemy)
{
    int index = -1;
    // try on trees: error here!
    if (_trees.size() != 0 && enemy->getPositionX() > _trees.back()->treeSprite->getPositionX() &&
       enemy->getPositionX() - _trees.back()->treeSprite->getPositionX() == enemy->mindist)
    {
        return 1;
    }
    else
        return -1;
}


void Enemy2Manager::bindBackground(Sprite* background)
{
    this->_background=background;
}
