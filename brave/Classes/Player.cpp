//
//  Player.cpp
//  brave
//
//  Created by Huang Zhenni on 9/14/14.
//
//

#include "Player.h"
bool Player::initWithPlayerType(PlayerType type)
{
    std::string spName = "";
    switch(type)
    {
        case PlayerType::PLAYER:
            spName = "player1-1-1.png";
            break;
        case PlayerType::ENEMY1:
            spName = "enemy1-1-1.png";
            break;
        case PlayerType::ENEMY2:
            spName = "enemy2-1-1.png";
            break;
    }
    this->initWithSpriteFrameName(spName);
    return true;
}

Player* Player::create(PlayerType type)
{
    Player* player = new Player();
    if(player && player->initWithPlayerType(type))
    {
        player->autorelease();
        return player;
    }
    else
    {
        delete player;
        player = NULL;
        return NULL;
    }
}