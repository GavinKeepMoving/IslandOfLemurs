//
//  Enemy.cpp
//  brave
//
//  Created by Yafu Li on 10/5/14.
//
//

#include "Enemy.h"
#include "Weapon.h"
#include "Progress.h"
#include <iostream>

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
	//init enemy's blood xiaojing**************************//
    _health = 50;
	_maxHealth = 50;
	_attack = 5;
	//*************************************************//
    //setup according to PlayerType
    switch(type)
    {
        case EnemyType::ENEMY1:
            sfName = "enemy1-1-1.png";
            _name = "enemy1";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            _minDist = 20;
            _speed = 100;
            break;
        case EnemyType::ENEMY2:
            sfName = "enemy2-1-1.png";
            _name = "enemy2";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            _minDist = 30;
            _speed = 70;
            break;
    }
    this->initWithSpriteFrameName(sfName);
    std::string animationNames[] = {"walk", "attack", "dead", "hit", "skill"};
    _animationNames.assign(animationNames, animationNames + 5);
    //load animation
    this->initFSM();
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
void Enemy::walkTo(Vec2 dest)
{
	std::function<void()> onWalk = CC_CALLBACK_0(Enemy::onWalk, this, dest);
	_fsm->setOnEnter("walking", onWalk);
	_fsm->doEvent("walk");
}
// dest is the position of the targetted ending point of the enemy
void Enemy::onWalk(Vec2 dest)
{
    log("Enter walk");
    auto curPos = this->getPosition();
    //    this->stopActionByTag(WALKTO_TAG);
    auto diff = dest - curPos;
	auto time = diff.getLength()/_speed;
    auto move = MoveTo::create(time,dest);
    auto func = [&]()
    {
        this->_fsm->doEvent("stop");
    };
    auto callback = CallFunc::create(func);
    auto seq = Sequence::create(move, callback,nullptr);
    //    seq->setTag(w)
    this->runAction(seq);
    this->playAnimationForever(WALKING);
}


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

/****************** Begin-Added by Zhe Liu *********************/
//enemy functions: attack, behit
void Enemy::attack()
{
    // find the nearest player, and then attack it.
    //    for (auto attacker : _attackers){
    //        if (abs(attacker->getPositionX()-this->getPositionX()) <= 1){
//    this->attack(30.0);
    //            break;
    //        }
    //    }
    _fsm->doEvent("attack");
}


// get animate by type
Animate* Enemy::getAnimateByType(AnimationType type){
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

void Enemy::initFSM(){
    _fsm = FSM::create("idle", "Enemy");
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
    // dead callback function
    //	auto onDead = [&]()
    //	{
    //		this->setCanAttack(false);
    //		log("onDead: Enter Dead");
    //		auto animate = getAnimateByType(DEAD);
    //		auto func = [&]()
    //		{
    //			log("A charactor died!");
    //			NotificationCenter::getInstance()->postNotification("enemyDead",this);
    //			this->removeFromParentAndCleanup(true);
    //		};
    //		auto blink = Blink::create(3,5);
    //		auto callback = CallFunc::create(func);
    //		auto seq = Sequence::create(animate, blink, callback, nullptr);
    //		this->stopAllActions();
    //		this->runAction(seq);
    ////		_progress->setVisible(false);
    //	};
    //	_fsm->setOnEnter("dead",onDead);
}



Vec2 Enemy::getCurPos()
{
    auto curPos = this->getPosition();
    Vec2 result = Vec2(curPos.x, curPos.y);
    return result;
}

//reduce the _health value of current enemy Xiaojing ***************//
void Enemy::beHit(int attack){
    _health -= attack;
	if(_health <= 0)
	{ //the enemy die
		_health = 0;
		//reset blood progress
		this->_progress->setProgress((float)_health/_maxHealth*100);
		//do event die
		_fsm->doEvent("die");
		return;
	}
	else
	{
		this->_progress->setProgress((float)_health/_maxHealth*100);
		_fsm->doEvent("beHit");
	}
}
//***************************************************//

//judge for the player
void Enemy::addAttacker(Player *attacker){
    _attackers.pushBack(attacker);
}
void Enemy::removeAttacker(Player *attacker){
    _attackers.eraseObject(attacker);
}
bool Enemy::isInRange(Player *enemy){
    return _attackers.contains(enemy);
}

// get best attack position
Vec2 Enemy::getBestAttackPosition(const Vec2& pos, std::vector<Tree*> trees)
{
    // fill in the closest object to be attacked.
    auto curPos = this->getPosition();
    Vec2 firstObj;
    bool isTree = false;
    if (trees.size() == 0 || (pos.x >= trees.back()->getPositionX() && curPos.x >= pos.x)){
        firstObj = pos;
    }
    else{
//        if (pos.x < trees.back()->getPositionX() || ){
        firstObj = trees.back()->getPosition();
        isTree = true;
//        }
    }
	auto pos1 = curPos - Vec2(_speed, 0);
	auto pos2 = curPos;
    auto pos3 = firstObj + Vec2(this->_minDist,0);
    auto diff1 = pos1.x - firstObj.x;
    if (diff1 > this->_minDist+_speed || (isTree == false && std::abs(firstObj.y - curPos.y) > 20)){
//        std::cout<< "the existence of tree is: "<<isTree<<std::endl;
        return pos1;
    }
    else if (diff1 > this->_minDist && (isTree == false && std::abs(firstObj.y - curPos.y) <= 20)){
        return pos3;
    }
    else{
        return pos2;
    }
}

bool Enemy::closeToTree(std::vector<Tree *> trees){
    Tree* last = trees.at(trees.size()-1);
    auto curPos = this->getPosition();
    float dist = last->getPositionX()+last->Sprite::getContentSize().width/2;
}

/****************** End-Added by Zhe Liu *********************/
