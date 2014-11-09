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

void Banana::timeshow()
{
    scheduleOnce(schedule_selector(Banana::show), 5.0f);
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
    //auto p = player->getPosition();
    //Vec2 BananaPos=_background->convertToWorldSpace(this->getPosition());
    auto p = player->getPosition();
    /******************************** Begin-Added by Wenbo Lin *********************************/
    //playerRect.origin = _background->convertToNodeSpace(playerRect.origin);
    Vec2 BananaPos=this->getParent()->convertToNodeSpace(this->getPosition());
    /******************************** End-Added by Wenbo Lin ***********************************/
    
    /*判断是否有交集*/
    return playerRect.containsPoint(BananaPos);
    //return player->boundingBox().intersectsRect(this->boundingBox());
}
void Banana::bindSprite(Sprite* sprite){
    this->_sprite=sprite;
    this->addChild(_sprite);
}