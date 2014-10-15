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
    
}

Banana::~Banana() {
    
}

void Banana::show()
{
    this->setVisible(true);
    m_isAlive=true;/*标记为活动状态*/
}
void Banana::hide()
{
    this->setVisible(false);
    //reset();
    m_isAlive=false;/*标记为活动状态*/
}

/********************************* Begin-Added Wenbo Lin *********************************/
//Origin Version
/*
void Banana::reset(int i)
{
    //初始化金币坐标,宽度(800-2800),高度（100-200
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    this->setPosition(origin.x +120+ i*100, origin.y + visibleSize.height*Player::height*3);
    //this->setPosition(ccp(800+CCRANDOM_0_1()*2000,200-CCRANDOM_0_1()*100));
}
*/

//Edited Version
void Banana::reset(int i)
{
    //初始化金币坐标,宽度(800-2800),高度（100-200
    this->setPosition(850 + i * 70, 630);
    //this->setPosition(ccp(800+CCRANDOM_0_1()*2000,200-CCRANDOM_0_1()*100));
}

/********************************* End-Added Wenbo Lin  *********************************/

bool Banana::isAlive()
{
    return m_isAlive;
}

bool Banana::isCollideWithPlayer(Player* player)
{
    Rect playerRect=player->getBoundingBox();
    //Vec2 BananaPos=_background->convertToWorldSpace(this->getPosition());
    
    /******************************** Begin-Added by Wenbo Lin *********************************/
    Vec2 BananaPos=_background->convertToWorldSpace(this->getPosition());
    /******************************** End-Added by Wenbo Lin ***********************************/
    
    /*判断是否有交集*/
    return playerRect.containsPoint(BananaPos);
}
void Banana::bindSprite(Sprite* sprite){
    this->_sprite=sprite;
    this->addChild(_sprite);
}