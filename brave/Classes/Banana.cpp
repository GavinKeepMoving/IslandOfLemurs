//
//  Banana.cpp
//  brave
//
//  Created by Lishi Jiang on 10/5/14.
//
//

#include "Banana.h"

int Banana::value = 5;

Banana::Banana() {
    this->setVisible(true);
    this->m_isAlive=true;
}

Banana::~Banana() {
    
}

void Banana::show(float dt)
{
    this->setVisible(true);
    this->m_isAlive=true;/*标记为活动状态*/
}

void Banana::timeshow(float time)
{
    scheduleOnce(schedule_selector(Banana::show), time);
}

void Banana::hide()
{
    this->setVisible(false);
    //reset();
    this->m_isAlive=false;/*标记为活动状态*/
}


//Edited Version
void Banana::reset(int i)
{
    //初始化金币坐标,宽度(800-2800),高度（100-200
    this->setPosition(830 + i * 70, 600);
    //this->setPosition(ccp(800+CCRANDOM_0_1()*2000,200-CCRANDOM_0_1()*100));
}

/********************************* End-Added Wenbo Lin  *********************************/

bool Banana::isAlive()
{
    return this->m_isAlive;
}

bool Banana::isCollideWithPlayer(Player* player)
{
    Rect playerRect=player->getBoundingBox();
    Vec2 playerPos = _background->convertToNodeSpace(player->getPosition());
    Node * tree = this->getParent();
    Vec2 bananaPos = tree->getPosition()+this->getPosition();
    //log("player position: %f",playerRect.origin.x);
    //log("banana position: %f",bananaPos.x);
    /*判断是否有交集*/
    return playerRect.containsPoint(bananaPos);
}
void Banana::bindSprite(Sprite* sprite){
    this->_sprite=sprite;
    this->addChild(_sprite);
}