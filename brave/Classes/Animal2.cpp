//
//  Animal2.cpp
//  brave
//
//  Created by Lishi Jiang on 10/26/14.
//
//

#include "Animal2.h"

Animal2::Animal2()
{
    Armature *armature = Armature::create("p1");
    //armature->setScaleX(-1);
    this->animation = armature->getAnimation();
    this->animation->setMovementEventCallFunc(this, movementEvent_selector(Animal2::onAnimationEvent));
    direction = WALK_RIGHT;
    this->addChild(armature);
    currentState = IDLE;
    newState = IDLE;
    lockState = false;
    _attack = 5;
}

void Animal2::setblood()
{
    this->_blood = 100;
}

int Animal2::beHit(int attack)
{
    this->_blood -= attack;
    if (_blood <= 0){
        return 1;
    }
    else{
        return 0;
    }
}

//设置方向
void Animal2::setDirection(int newDirection)
{
    direction = newDirection;
    this->setScaleX(direction * fabs(this->getScaleX()));
}

void Animal2::update(float dt)
{
    if (currentState == newState || isLockState())
    {
        updateMovement();
    }
    else
    {
        currentState = newState;
        updateAnimation();
    }
}

void Animal2::updateMovement()
{
    Point oldPos = this->getPosition();
    if (currentState == WALK)
    {
        this->setPosition(oldPos.x + -direction * WALK_SPEED,oldPos.y);
    }
}

void Animal2::updateAnimation()
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

bool Animal2::isLockState()
{
    return lockState;
}

void Animal2::onAnimationEvent(Armature *pArmature, MovementEventType eventType, const char *animationID)
{
    if (eventType == LOOP_COMPLETE) {
        if (strcmp(animationID, "grenade") == 0)
        {
            lockState = false;
            newState = IDLE;
        }
    }
}