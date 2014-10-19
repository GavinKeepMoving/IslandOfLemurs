//
//  BananaManger.cpp
//  brave
//
//  Created by Lishi Jiang on 10/5/14.
//
//


#include "BananaManger.h"
#include "Banana.h"
#define max_Banana_num 3

BananaManger::BananaManger(){}

BananaManger::~BananaManger(){}

BananaManger* BananaManger::create(Sprite* background)
{
    BananaManger* bananaManger = new BananaManger();
    bananaManger->_background = background;
    bananaManger->init();
    return bananaManger;
}

bool BananaManger::init()
{
    bool bRet=false;
    do
    {
        createBananas();/*创建怪物*/
        this->schedule(schedule_selector(BananaManger::update), 0.5);
        //this->scheduleUpdate();/*启用update*/
        bRet=true;
    } while (0);
    return bRet;
    
}


void BananaManger::createBananas()
{
    _bananaArr=CCArray::create();
    _bananaArr->retain();/*防止数组被释放*/
    
    //Banana* banana=NULL;
    //CCSprite* sprite=NULL;
    
    for(int i=0;i<max_Banana_num; i++)
    {
        auto banana=Banana::create();
        
        /******************************** Begin-Added by Wenbo Lin *********************************/
        banana->_background = this->_background;
        /******************************** End-Added by Wenbo Lin ***********************************/
        
        banana->setScale(0.3);
        banana->bindSprite(Sprite::create("fruit.png"));
        banana->reset(i);
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
            //banana->setPositionX(banana->getPositionX()-3);//左移
            if(banana->getPositionX()<0)
            {
                banana->hide();
                
            }else if(banana->isCollideWithPlayer(_player)){
                _player->money += Banana::value;
                //_player->hit();
                banana->hide();
                log("get a fruit, now: %d",_player->money);
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

/******************************** Begin-Added by Wenbo Lin *********************************/
void BananaManger::bindBackground(Sprite* background)
{
    this->_background=background;
}
/******************************** End-Added by Wenbo Lin ***********************************/