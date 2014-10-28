//
//  Enemy2.cpp
//  brave
//
//  Created by Lishi Jiang on 10/19/14.
//
//

#include "Enemy2.h"
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