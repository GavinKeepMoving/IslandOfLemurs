//
//  Animal2Manager.cpp
//  brave
//
//  Created by Lishi Jiang on 10/26/14.
//
//

#include "Animal2Manager.h"

#define max_Banana_num 2

Animal2Manager::Animal2Manager(){}

Animal2Manager::~Animal2Manager(){}

Animal2Manager* Animal2Manager::create(Sprite* background)
{
    Animal2Manager* animal2Manager = new Animal2Manager();
    animal2Manager->_background = background;
    animal2Manager->init();
    return animal2Manager;
}

bool Animal2Manager::init()
{
    bool bRet=false;
    do
    {
        _animal2Arr=__Array::create();
        _animal2Arr->retain();
        //createAnimal2s();/*创建怪物*/
        //this->schedule(schedule_selector(Animal2Manager::update), 0.5);
        //this->scheduleUpdate();/*启用update*/
        bRet=true;
    } while (0);
    return bRet;
    
}


void Animal2Manager::createAnimal2s()
{
    //_animal2Arr=__Array::create();
    //_animal2Arr->retain();
    
    
    //for(int i=0;i<max_Banana_num; i++)
    //{
    log("animal!!!!");
        auto animal2=Animal2::create();
        animal2->setblood();
        animal2->_background = this->_background;
        animal2->setPosition(550 , 230);
        this->addChild(animal2);  /*将怪物添加到管理器(CCNode)中*/
        _animal2Arr->addObject(animal2);/*添加到数组中，便于管理*/
    //}
}

int Animal2Manager::judgeNeayBy(Animal2 *animal)
{
    int index = -1;
    if (this->_enemy2Arr->count() == 0){
        return index;
    }
    else{
        // find the nearest enemy and judge whether it is in the attacking scope
        CCObject* obj = NULL;
        Enemy2* enemy = NULL;
        Enemy2* nearest = NULL;
        int min = -1;
        int enemy_index = -1;
        int i = 0;
        CCARRAY_FOREACH(_enemy2Arr, obj)
        {
            enemy = (Enemy2*) obj;
            if (min == -1 || min < std::abs(animal->getPositionX()-enemy->getPositionX())){
                min = std::abs(animal->getPositionX()-enemy->getPositionX());
                nearest = enemy;
                enemy_index = i;
            }
            i++;
        }

//        Enemy2* nearest = getNearestEnemy(animal);
        if (mindist < std::abs(animal->getPositionX()-nearest->getPositionX())){
            animal->setState(Animal2::WALK);
        }
        else{
            animal->setState(Animal2::ATTACK);
            index = enemy_index;
        }
        return index;
    }
}

//Enemy2* Animal2Manager::getNearestEnemy(Animal2* animal)
//{
//    CCObject* obj = NULL;
//    Enemy2* enemy = NULL;
//    Enemy2* nearest = NULL;
//    int min = -1;
//    CCARRAY_FOREACH(_enemy2Arr, obj)
//    {
//        enemy = (Enemy2*) obj;
//        if (min == -1 || min < std::abs(animal->getPositionX()-enemy->getPositionX())){
//            min = std::abs(animal->getPositionX()-enemy->getPositionX());
//            nearest = enemy;
//        }
//    }
//    return enemy;
//}

void Animal2Manager::update(float dt)
{
    CCObject* obj=NULL;
    Animal2* animal2=NULL;
    CCARRAY_FOREACH(_animal2Arr,obj)/*循环遍历怪物数组，重复出现在屏幕上*/
    {
        //need LIU ZHE HELP
        //whatever you want.
        animal2=(Animal2*) obj;
        //******
        animal2->setState(Animal2::WALK);
        //*****
        animal2->update(dt);
    }
}


void Animal2Manager::bindBackground(Sprite* background)
{
    this->_background=background;
}
