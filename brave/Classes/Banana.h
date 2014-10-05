//
//  Banana.h
//  brave
//
//  Created by Lishi Jiang on 10/5/14.
//
//

#ifndef __brave__Banana__
#define __brave__Banana__

#include "cocos2d.h"
#include "player.h"
USING_NS_CC;

class Banana : public Sprite
{
public:
    static int value;
    Banana();
    virtual ~Banana();
    CREATE_FUNC(Banana);
    
public:
    void show();
    void hide();
    void reset();//重置怪物数据
    bool isAlive();//是否活动状态
    
    bool isCollideWithPlayer(Player* player);//检测是否碰撞
    void bindSprite(CCSprite* sprite);
private:
    bool m_isAlive;
    CCSprite* _sprite; 
};

#endif /* defined(__brave__Banana__) */
