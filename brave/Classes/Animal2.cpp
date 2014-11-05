//
//  Animal2.cpp
//  brave
//
//  Created by Lishi Jiang on 10/26/14.
//
//

#include "Animal2.h"
//#include "Progress.h"

#include "Progress.h"
Animal2::Animal2(int i)
{
    armature = nullptr;
    switch (i)
    {
        case 0:
            armature = Armature::create("animal");
            break;
        case 1:
            armature = Armature::create("monkey2");
            break;
        case 2:
            armature = Armature::create("monkey2");
            break;
        case 3:
            armature = Armature::create("monkey2");
            break;
        default:
            break;
    }
    armature->setScaleX(-1);
    this->animation = armature->getAnimation();
    this->animation->setMovementEventCallFunc(this, movementEvent_selector(Animal2::onAnimationEvent));
    direction = WALK_RIGHT;
    this->addChild(armature);
    currentState = IDLE;
    newState = IDLE;
    lockState = false;
    _attack = 5;
	_maxHealth = 1000;
	_blood = 1000;
	//****init progress for blood  xiaojing***********//
	_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	//************add its progress***xiaojing**********************//
	//add enemy's progress
	auto size = this->getContentSize();
	Point animalPos = this->getPosition();
	_progress->setPosition( animalPos.x +size.width*2/3, animalPos.y + size.height+ _progress->getContentSize().height/2+230);
	this->addChild(_progress);

	//**********************************************************//
}
Animal2::~Animal2()
{
    delete _progress;
//    delete armature;
}

Animal2* Animal2::create(int i){
    Animal2* animal2 = new Animal2(i);
    return animal2;
}

//void Animal2::setblood()
//{
//    this->_blood = 100;
//}

int Animal2::beHit(int attack)
{
    this->_blood -= attack;
    std::cout<<"current blood is: "<<_blood<<std::endl;
    if (_blood <= 0){
        _blood = 0;
		this->_progress->setProgress((float)_blood/_maxHealth*100);
        return 1;
    }
    else{
        this->_progress->setProgress((float)_blood/_maxHealth*100);
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
        this->setPosition(oldPos.x -direction * WALK_SPEED,oldPos.y);
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
            animation->play("animalwalk");
            break;
        case ATTACK:
            animation->play("animalhit");
            break;
        case BEHIT:
            animation->play("animalbehit");
            break;
        case DEAD:
            animation->play("animaldead");
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