//
//  Enemy.cpp
//  brave
//
//  Created by Yafu Li on 10/5/14.
//
//

#include "Enemy.h"

#include "Weapon.h"


float Enemy::height = 0.25;

void Enemy::addAnimation()
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
void Enemy::playAnimationForever(int index)
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

bool Enemy::initWithPlayerType(EnemyType type)
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
        case EnemyType::ENEMY1:
            sfName = "enemy1-1-1.png";
            _name = "enemy1";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case EnemyType::ENEMY2:
            sfName = "enemy2-1-1.png";
            _name = "enemy2";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
    }
    this->initWithSpriteFrameName(sfName);
    std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
    _animationNames.assign(animationNames, animationNames + 5);
    //load animation
    this->addAnimation();
	
	
	
	//add enemy's progress
	auto size = this->getContentSize();
	_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	_progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2);
	
	this->addChild(_progress);
//-----------------------------------------------//
    return true;
}

Enemy* Enemy::create(EnemyType type)
{
    Enemy* enemy = new Enemy();
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
 }*/


Weapon* Enemy::attack(float radius)
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
void Enemy::walkTo(Vec2 dest)
{
    log("onIdle: Enter walk");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //stop current moving action, if any.
    if(_seq!=nullptr)
        this->stopAction(_seq);
    
    auto curPos = this->getPosition();
    auto backgroundPos = background->getPosition();
    auto background1Pos = background1->getPosition();
    
    //flip when moving backward
    if(curPos.x > dest.x) {
        dest.x = origin.x;
        this->setFlippedX(true);
    }
    else {
        dest.x = origin.x + visibleSize.width;
        this->setFlippedX(false);
    }
    dest.y = curPos.y;
    
    //calculate the time needed to move
    auto diff = dest - curPos;
    auto realDest = backgroundPos - diff;
    auto realDest1 = background1Pos - diff;
    auto playerTime = diff.length()/_speed;
    auto time = realDest.getLength()/_speed;
    
    //auto movePlayer = MoveTo::create(playerTime, dest);
    auto move = MoveTo::create(time, realDest);
    auto move1 = MoveTo::create(time, realDest1);
    
    //lambda function
    auto func = [&]()
    {
        this->stopAllActions();
        //_seq = nullptr;
    };
    auto callback = CallFunc::create(func);
    
    //create sequence for two backgrounds and player(some bugs)
    //auto _seqPlayer = Sequence::create(movePlayer, callback, nullptr);
    auto _seq = Sequence::create(move, callback, nullptr);
    auto _seq1 = Sequence::create(move1, callback, nullptr);
    
    //this->runAction(_seq);
    //this->playAnimationForever(0);
    
    //run action sequnce
    background->runAction(_seq);
    background1->runAction(_seq1);
    
    //judge if action should be stopped
    auto curPosback1 = background->getPosition();
    auto curPosback2 = background1->getPosition();
    
    /*
     if(curPosback1.x - visibleSize.width / 2 > 0 || visibleSize.width / 2 - curPosback2.x > 0) {
     background->stopAllActions();
     background1->stopAllActions();
     
     //when background hit the end, player continue to move
     //this->runAction(_seqPlayer);
     //this->playAnimationForever(0);
     }
     //background->playAnimationForever(0);
     */
}


Vec2 Enemy::getCurPos()
{
    auto curPos = this->getPosition();
    Vec2 result = Vec2(curPos.x, curPos.y);
    return result;
}
