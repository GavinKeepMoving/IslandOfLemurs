//
//  BananaManger.cpp
//  brave
//
//  Created by Lishi Jiang on 10/5/14.
//
//

#include "BananaManger.h"
#include "BananaManger.h"
#include "Banana.h"
#define max_Banana_num 20

BananaManger::BananaManger(){}

BananaManger::~BananaManger(){}

bool BananaManger::init()
{
    bool bRet=false;
    do
    {
        createBananas();/*创建怪物*/
        this->scheduleUpdate();/*启用update*/
        bRet=true;
    } while (0);
    return bRet;
    
}


void BananaManger::createBananas()
{
    _bananaArr=CCArray::create();
    _bananaArr->retain();/*防止数组被释放*/
    
    Banana* banana=NULL;
    CCSprite* sprite=NULL;
    
    for(int i=0;i<max_Banana_num; i++)
    {
        banana=Banana::create();
        banana->bindSprite(CCSprite::create("sliderThumb.png"));
        banana->reset();
        
        this->addChild(banana);  /*将怪物添加到管理器(CCNode)中*/
        _bananaArr->addObject(banana);/*添加到数组中，便于管理*/
    }
}

void BananaManger::update(float dt)
{
    CCObject* obj=NULL;
    Banana* banana=NULL;
    
    CCARRAY_FOREACH(_bananaArr,obj)/*循环遍历怪物数组，重复出现在屏幕上*/
    {
        banana=(Banana*) obj;
        if(banana->isAlive())/*活动状态*/
        {
            banana->setPositionX(banana->getPositionX()-3);//左移
            if(banana->getPositionX()<0)
            {
                banana->hide();
                
            }else if(banana->isCollideWithPlayer(_player)){
                //_player->hit();
                banana->hide();
            }
            
        }else/*非活动状态*/
        {
            banana->show();//
        }
    }
}
void BananaManger::bindPlayer(Player* player)
{
    this->_player=player;
    this->_player->retain();//引用计数 +1
}