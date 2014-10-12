//
//  Animal.cpp
//  brave
//
//  Created by Yafu Li on 10/12/14.
//
//

#include "Animal.h"

#include "Weapon.h"
#include "Progress.h"

float Animal::height = 0.25;

void Animal::addAnimation()
{
    // check if already loaded
    auto animation = AnimationCache::getInstance()->getAnimation(String::createWithFormat("%s-%s",_name.c_str(),
                                                                                          _animationNames[0].c_str())->getCString());
    if(animation)
        return;
    
    for(int i1=0; i1<_animationNum; i1++)
    {
        auto animation = Animation::create();
        animation->setDelayPerUnit(0.2f);
        //put frames into animation
        for(int j = 0; j< _animationFrameNum[i1] ; j++)
        {
            auto sfName =String::createWithFormat("%s-%d-%d.png",_name.c_str(), i1+1, j+1)->getCString();
            animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName));
        }
        // put the animation into cache
        AnimationCache::getInstance()->addAnimation(animation, String::createWithFormat("%s-%s",_name.c_str(),
                                                                                        _animationNames[i1].c_str())->getCString());
    }
}
void Animal::playAnimationForever(int index)
{
    if(index <0 || index >= _animationNum)
    {
        log("illegal animation index!");
        return;
    }
    auto str = String::createWithFormat("%s-%s",_name.c_str(), _animationNames[index].c_str())->getCString();
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    auto animate = Animate::create(animation);
    this->runAction(RepeatForever::create(animate));
}

bool Animal::initWithPlayerType(AnimalType type)
{
    std::string sfName = "";
    _type = type;
    _speed = 100;
    _seq = nullptr;
    int animationFrameNum[5] ={4, 4, 4, 2, 4};
    int animationFrameNum2[5] ={3, 3, 3, 2, 0};
    
    //setup according to PlayerType
    switch(type)
    {
        case AnimalType::CLOTHE:
            sfName = "clothe-1-1.png";
            _name = "clothe";
            _animationNum = 5;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case AnimalType::DOG:
            sfName = "dog-1-1.png";
            _name = "dog";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case AnimalType::AC:
            sfName = "AC-1-1.png";
            _name = "AC";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case AnimalType::ELEPHANT:
            sfName = "elephant-1-1.png";
            _name = "elephant";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
    }
    this->initWithSpriteFrameName(sfName);
    std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
    _animationNames.assign(animationNames, animationNames + 5);
    //load animation
    this->addAnimation();
    this->walkTo(Director::getInstance()->getVisibleOrigin());
    
    
    //add enemy's progress
    auto size = this->getContentSize();
    _progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
    _progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2);
    
    this->addChild(_progress);
    //-----------------------------------------------//
    return true;
}

Animal* Animal::create(AnimalType type)
{
    Animal* enemy = new Animal();
    if(enemy && enemy->initWithPlayerType(type))
    {
        enemy->autorelease();
        return enemy;
    }
    else
    {
        delete enemy;
        enemy = NULL;
        return NULL;
    }
}
/*
 void Player::walkTo(Vec2 dest)
 {
	std::function<void()> onWalk = CC_CALLBACK_0(Player::onWalk, this, dest);
	//_fsm->setOnEnter("walking", onWalk);
	//_fsm->doEvent("walk");
 }
*/

Weapon* Animal::attack(float radius)
{
    //add weapon
    Weapon *weapon = Weapon::create(Weapon::WeaponType::ARROW);
    Vec2 pos = this->getPosition();
    weapon->setPosition(pos.x, pos.y);
    //scene->addChild(weapon);
    
    Vec2 target(pos.x+radius, pos.y);
    
    weapon->shootTo(target);
    
    return weapon;
}

//actually player stay in the center of the screeen but the background would move to the opposite position as the target
void Animal::walkTo(Vec2 dest)
{
    log("onIdle: Enter walk");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //stop current moving action, if any.
    if(_seq!=nullptr)
        this->stopAction(_seq);
    
    auto curPos = this->getPosition();
    dest.y = origin.y + visibleSize.height*Animal::height;
    //flip when moving backward
    if(curPos.x > dest.x) {
        dest.x = origin.x;
        this->setFlippedX(true);
    }
    else {
        dest.x = origin.x + visibleSize.width;
        this->setFlippedX(false);
    }
    
    
    //calculate the time needed to move
    auto diff = dest - curPos;
    auto time = diff.getLength()/_speed;
    auto move = MoveTo::create(time, dest);
    //lambda function
    auto func = [&]()
    {
        //this->_fsm->doEvent("stop");
        this->stopAllActions();
        //_seq = nullptr;
    };
    auto callback = CallFunc::create(func);
    auto _seq = Sequence::create(move, callback, nullptr);
    
    this->runAction(_seq);
    this->playAnimationForever(0);
 
}


Vec2 Animal::getCurPos()
{
    auto curPos = this->getPosition();
    Vec2 result = Vec2(curPos.x, curPos.y);
    return result;
}

