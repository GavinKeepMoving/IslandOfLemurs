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
        createEnemy2s(20);/*创建怪物*/
        //this->schedule(schedule_selector(Enemy2Manager::update), 0.5);
        //this->scheduleUpdate();/*启用update*/
        bRet=true;
    } while (0);
    return bRet;
    
}


Enemy2* Enemy2Manager::createEnemy2s(int order)
{

    
        auto enemy2=Enemy2::create();
        enemy2->_background = this->_background;
//        enemy2->setPosition(950 + i * 70, 430);
        enemy2->setPosition(2800+order,70);
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
int Enemy2Manager::judgeNearby(const Vec2& pos,Enemy2* enemy,std::vector<Tree*> trees, std::vector<Animal2*> animal2Arr)
{
    int index = -1;
    int isTree = 0;
    int hasAnimal = 0;
    Animal2* closest = NULL;
    Vec2 firstObj;
    int animal_index = -1;
    int i = 0;
    // try on trees: error here!
    if (animal2Arr.size() > 0){
        for (i=0;i<animal2Arr.size();i++)
        {
            if (animal2Arr[i]->getPositionX() < enemy->getPositionX() && (animal_index == -1 || animal2Arr[i]->getPositionX() > closest->getPositionX())){
                hasAnimal = 1;
                animal_index = i;
                closest = animal2Arr[i];
            }
        }
    }
    // lemur
    if ( pos.y == 80 &&(trees.size() == 0 || (pos.x >= trees.back()->treeSprite->getPositionX() &&
         enemy->getPositionX() >= pos.x))
        && (hasAnimal == 0 || (pos.x >= closest->getPositionX() && enemy->getPositionX() >= pos.x))){
        firstObj = pos;
        index = 0;
    }
    // tree
    else if (trees.size() > 0 && (enemy->getPositionX() > trees.back()->treeSprite->getPositionX()) && (hasAnimal == 0 || (trees.back()->treeSprite->getPositionX() > closest->getPositionX()))&&(pos.y > 80 || pos.x < trees.back()->treeSprite->getPositionX())){
        firstObj = Vec2(trees.back()->treeSprite->getPositionX(),enemy->getPositionY());
        index = 1;
        isTree = 1;
    }
    // animal
    else if (hasAnimal > 0 && (trees.size() == 0 || closest->getPositionX() > trees.back()->treeSprite->getPositionX()) && (pos.y > 80 || closest->getPositionX() > pos.x) && enemy->getPositionX() >= closest->getPositionX())
    {
        isTree = 2;
        firstObj = Vec2(closest->getPositionX(),enemy->getPositionY());
        index = 200+animal_index;
    }
    else{
        isTree = 3;
        index = -1;
    }
    // judge for the nearby
//    std::cout<<"the current nearby oppoent is: "<<index<<std::endl;
    return index;
    
}


void Enemy2Manager::bindBackground(Sprite* background)
{
    this->_background=background;
}
