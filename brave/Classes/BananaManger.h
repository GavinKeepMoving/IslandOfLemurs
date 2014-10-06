//
//  BananaManger.h
//  brave
//
//  Created by Lishi Jiang on 10/5/14.
//
//

#ifndef __brave__BananaManger__
#define __brave__BananaManger__

#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

#define MAX_MONSTER_NUM 10

class BananaManger:public Node
{
public:
    BananaManger();
    ~BananaManger();
    static BananaManger* create();
    virtual bool init();
    virtual void update(float dt);/*重写update函数*/
    void bindPlayer(Player* player);
private:
    void createBananas();/*创建Monster对象*/
private:
    CCArray* _bananaArr;/*存放怪物数组*/
    Player* _player;
};


#endif /* defined(__brave__BananaManger__) */
