//
//  Enemy2.cpp
//  brave
//
//  Created by Lishi Jiang on 10/19/14.
//
//

#include "Enemy2.h"
//#include "Progress.h"
#include "Progress.h"
#include <iostream>
Enemy2::Enemy2()
{
    Armature *armature = Armature::create("p1");
    armature->setScaleX(-1);
    this->animation = armature->getAnimation();
    this->animation->setMovementEventCallFunc(this, movementEvent_selector(Enemy2::onAnimationEvent));
    direction = WALK_LEFT;
    this->addChild(armature);
    currentState = IDLE;
    newState = IDLE;
    lockState = false;
    // 
    _attack = 1;
    _blood = 1000;
    _maxHealth = 1000;
    _attack = 1;
//    _blood = 100;
	_maxblood = 1000;
	//****init progress for blood  xiaojing***********//
	_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	//************add its progress***xiaojing**********************//
	//add enemy's progress
	auto size = this->getContentSize();
	Point enemyPos = this->getPosition();
	_progress->setPosition( enemyPos.x +size.width*2/3, enemyPos.y + size.height+ _progress->getContentSize().height/2+230);
	//enemy2->_progress->setPosition( 1800+size.width*2/3, 130+ size.height + enemy2->_progress->getContentSize().height/2);
	this->addChild(_progress);

	//**********************************************************//
}

void Enemy2::setBlood()
{
    _blood = 100;
}

int Enemy2::behit(int attack)
{
    _blood -= attack;
    std::cout<<"enemy's current blood is: "<<_blood<<std::endl;
    if (_blood <= 0){
        _blood = 0;
		_progress->setProgress((float)_blood/_maxblood*100);
        return 1;
    }
    else{
        std::cout<<"enemy's current blood is: "<<_blood<<std::endl;
		_progress->setProgress((float)_blood/_maxblood*100);
        return 0;
    }
}

//设置方向
void Enemy2::setDirection(int newDirection)
{
    direction = newDirection;
    this->setScaleX(direction * fabs(this->getScaleX()));
}

void Enemy2::update(float dt)
{
    if (currentState == newState || isLockState())
    {
        updateMovement();
    }
    else
    {
        currentState = newState;
        updateAnimation();
        
        //add by wenbo
        //change state
        //playSound();
    }
}

void Enemy2::updateMovement()
{
    Point oldPos = this->getPosition();
    if (currentState == WALK)
    {
        this->setPosition(oldPos.x + -direction * WALK_SPEED,oldPos.y);
    }
}

void Enemy2::updateAnimation()
{
    switch (currentState)
    {
        case IDLE:
            animation->stop();
            break;
        case WALK:
            animation->play("enemy_walk");
            break;
        case ATTACK:
            animation->play("hit");
            break;
        case BEHIT:
            animation->play("behit");
            break;
        case DEAD:
            animation->play("dead");
            lockState = true;
            break;
        default:
            break;
    }
}

//add by wenbo
void Enemy2::playSound()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(_enemySoundEffectId);
    switch (currentState)
    {
        case IDLE:
            break;
        case WALK:
            break;
        case ATTACK:
            _enemySoundEffectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("AudioClip/CageBreak.wav", true);
            break;
        case BEHIT:
            _enemySoundEffectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("AudioClip/JackDamage4.wav", true);
            break;
        case DEAD:
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("AudioClip/JackDead4.wav");
            break;
        default:
            break;
    }
}

//end adding by wenbo

bool Enemy2::isLockState()
{
    return lockState;
}

void Enemy2::onAnimationEvent(Armature *pArmature, MovementEventType eventType, const char *animationID)
{
    if (eventType == LOOP_COMPLETE) {
        if (strcmp(animationID, "grenade") == 0)
        {
            lockState = false;
            newState = IDLE;
        }
    }
}