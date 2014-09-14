//
//  Player.h
//  brave
//
//  Created by Huang Zhenni on 9/14/14.
//
//

#ifndef __Player__
#define __Player__
#include "cocos2d.h"
USING_NS_CC;

class Player : public Sprite
{
public:
    enum PlayerType
    {
        PLAYER,
        ENEMY1,
        ENEMY2
    };
    bool initWithPlayerType(PlayerType type);
    static Player* create(PlayerType type);
    
};

#endif