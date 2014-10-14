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
#include <iostream>
#include "MainScene.h"
//#include "Enemy.h"

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
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
			//-----assign different blood----------Xiaojing---------------//
			_health = 20;
			_maxHealth =20;
			_attack = 2;
			
			//-------------------------------------------------//
            break;
        case AnimalType::TIGER:
            sfName = "tiger-1-1.png";
            _name = "tiger";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            
			_health = 30;
			_maxHealth = 30;
			_attack = 3;
            break;
        case AnimalType::FOX:
            sfName = "fox-1-1.png";
            _name = "fox";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
			_health = 40;
			_maxHealth =40;
			_attack = 4 ;
            break;
        case AnimalType::ELEPHANT:
            sfName = "elephant-1-1.png";
            _name = "elephant";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
			_health = 50;
			_maxHealth =50;
			_attack = 5;
            break;
    }
    this->initWithSpriteFrameName(sfName);
    std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
    _animationNames.assign(animationNames, animationNames + 5);
    //load animation
    this->addAnimation();
    //this->walkTo(Director::getInstance()->getVisibleOrigin());
    
    
    //add enemy's progress
    auto size = this->getContentSize();
    _progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
    _progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2);
    this->initFSM();
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


//Weapon* Animal::attack(float radius)
//{
//    //add weapon
//    Weapon *weapon = Weapon::create(Weapon::WeaponType::ARROW);
//    Vec2 pos = this->getPosition();
//    weapon->setPosition(pos.x, pos.y);
//    //scene->addChild(weapon);
//    
//    Vec2 target(pos.x+radius, pos.y);
//    
//    weapon->shootTo(target);
//    
//    return weapon;
//}

//actually player stay in the center of the screeen but the background would move to the opposite position as the target
void Animal::walkTo(Vec2 dest)
{
	std::function<void()> onWalk = CC_CALLBACK_0(Animal::onWalk, this, dest);
	_fsm->setOnEnter("walking", onWalk);
	_fsm->doEvent("walk");
}

void Animal::onWalk(Vec2 dest)
{
    log("Enemy: Enter walk");
    auto curPos = this->getPosition();
//    dest.y = origin.y + visibleSize.height*Animal::height;
//    //flip when moving backward
//    if(curPos.x > dest.x) {
//        dest.x = origin.x;
//        this->setFlippedX(true);
//    }
//    else {
//        dest.x = origin.x + visibleSize.width;
//        this->setFlippedX(false);
//    }
//    
    
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
//reduce the _health value of current animal Xiaojing ***************//
void Animal::beHit(int attack){
    _health -= attack;
	if(_health <= 0)
	{ //die
		_health = 0;
		
		//do event die
		_fsm->doEvent("die");
		return;
	}
	else
	{
		//be hit
		_fsm->doEvent("beHit");
	}
}
//***************************************************//

/****************** Begin-Added by Zhe Liu *********************/
void Animal::attack()
{
    _fsm->doEvent("attack");
}
void Animal::stop()
{
    _fsm->doEvent("stop");
}

void Animal::initFSM(){
    _fsm = FSM::create("idle", "Helper");
    _fsm->retain();
    // corresponding functions
    auto onIdle =[&]()
	{
		log("Enemy onIdle: Enter idle");
		this->stopActionByTag(WALKING);
		auto sfName = String::createWithFormat("%s-1-1.png", _name.c_str());
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName->getCString());
		this->setSpriteFrame(spriteFrame);
	};
	_fsm->setOnEnter("idle",onIdle);
    
	auto onAttacking =[&]()
	{
		log("Enemy onAttacking: Enter Attacking");
		auto animate = getAnimateByType(ATTACKING);
		auto func = [&]()
		{
			this->_fsm->doEvent("stop");
		};
		auto callback = CallFunc::create(func);
		auto seq = Sequence::create(animate, callback, nullptr);
		this->runAction(seq);
	};
	_fsm->setOnEnter("attacking",onAttacking);
	
	auto onBeingHit = [&]()
	{
		log("Enemy onBeingHit: Enter BeingHit");
		auto animate = getAnimateByType(BEINGHIT);
		auto func = [&]()
		{
			this->_fsm->doEvent("stop");
		};
		auto wait = DelayTime::create(0.6f);
		auto callback = CallFunc::create(func);
		auto seq = Sequence::create(wait,animate, callback, nullptr);
		this->runAction(seq);
	};
	_fsm->setOnEnter("beingHit",onBeingHit);
    //    dead callback function
    auto onDead = [&]()
    {
        //        this->setCanAttack(false);
        log("onDead: Enter Dead");
        auto animate = getAnimateByType(DEAD);
        auto func = [&]()
        {
            log("A charactor died!");
            NotificationCenter::getInstance()->postNotification("enemyDead",this);
            this->removeFromParentAndCleanup(true);
        };
        auto blink = Blink::create(3,5);
        auto callback = CallFunc::create(func);
        auto seq = Sequence::create(animate, blink, callback, nullptr);
        this->stopAllActions();
        this->runAction(seq);
        //		_progress->setVisible(false);
    };
    _fsm->setOnEnter("dead",onDead);
}

// get animate by type
Animate* Animal::getAnimateByType(AnimationType type){
    if (type < 0 || type >= _animationNum)
    {
        log("illegal animation index!");
        return nullptr;
    }
    auto str = String::createWithFormat("%s-%s",_name.c_str(), _animationNames[type].c_str())->getCString();
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    auto animate = Animate::create(animation);
    animate->setTag(type);
    return animate;
}
// return the position we need to go in the next frame
Vec2 Animal::getBestAttackPosition(std::vector<Enemy*> enemys,int& index)
{
    // animal's position
    auto curPos = this->getPosition();
    auto pos1 = curPos;
    auto pos2 = curPos + Vec2(_speed,0);
    if (enemys.size() == 0){
        return pos1;
    }
    else{
        // find the closest enemy
        Enemy* closestEnemy = enemys[0];
        index = 0;
        for (int i=1;i<enemys.size();i++){
            if (enemys[i]->getPositionX() < closestEnemy->getPositionX()){
                closestEnemy = enemys[i];
                index = i;
            }
        }
        // judge for the move dest
        auto diff = closestEnemy->getPositionX() - curPos.x;
        if (diff > _minDist+_speed){
            return pos2;
        }
        else if (diff > _minDist){
            auto pos3 = Vec2(closestEnemy->getPositionX()-_minDist, curPos.y);
            return pos3;
        }
        else{
            return pos1;
        }
    }
}
/****************** End-Added by Zhe Liu *********************/

