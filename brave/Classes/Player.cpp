//
//  Player.cpp
//  brave
//
//  Created by Huang Zhenni on 9/14/14.
//
//

#include "Player.h"
#include "Weapon.h"

#include "MainScene.h"

extern MainScene *mainLayer;


float Player::height = 0.25;

void Player::addAnimation()
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
void Player::playAnimationForever(int index)
{
    for(int i=0;i<5;i++)
    {
        this->stopActionByTag(i);
    }
    if(index <0 || index >= _animationNum)
    {
        log("illegal animation index!");
        return;
    }
    
    auto str = String::createWithFormat("%s-%s",_name.c_str(), _animationNames[index].c_str())->getCString();
    auto animation = AnimationCache::getInstance()->getAnimation(str);
    auto animate = Animate::create(animation);
    animate->setTag(index);//bug trigger here
    this->runAction(RepeatForever::create(animate));
}

bool Player::initWithPlayerType(PlayerType type)
{
    std::string sfName = "";
    money = 0;
    _type = type;
    _speed = 100;
    _attackSpeed = 3;
    _attackRange = 350;
	_seq = nullptr;
    DROPING = false;
    int animationFrameNum[5] ={4, 4, 4, 2, 4};
    int animationFrameNum2[5] ={3, 3, 3, 2, 0};
    
    //setup according to PlayerType
    switch(type)
    {
        case PlayerType::PLAYER:
            sfName = "lemur-1-1.png";
            _name = "lemur";
            _animationNum = 5;
            _speed = 125;
			//init player's blood value xiaojing
			_health = 100;
			_maxHealth =100;
			_attack = 20;
			//-----------------------------------//
            _animationFrameNum.assign(animationFrameNum, animationFrameNum + 5);
            break;
        case PlayerType::ENEMY1:
            sfName = "enemy1-1-1.png";
            _name = "enemy1";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 5);
            break;
        case PlayerType::ENEMY2:
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
    this->initFSM();
    
    return true;
}

void Player::initFSM()
{
    _fsm = FSM::create("idle","Lemur");
    _fsm->retain();
    auto onIdle =[&]()
    {
        log("onIdle: Enter idle");
        this->stopAllActions();
        this->background->stopAllActions();
        //this->stopActionByTag(WALKTO_TAG);
        //this->stop();
//        auto func = [&]()
//        {
//            this->stop();
//        };
//        auto sfName = String::createWithFormat("%s-1-1.png", _name.c_str());
//        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName->getCString());
//        this->setSpriteFrame(spriteFrame);
        this->schedule(schedule_selector(Player::generalAttack), _attackSpeed);
    
        this->scheduleUpdate();
    };
    _fsm->setOnEnter("idle",onIdle);
}


Player* Player::create(PlayerType type)
{
    Player* player = new Player();
    if(player && player->initWithPlayerType(type))
    {
        player->autorelease();
        return player;
    }
    else
    {
        delete player;
        player = NULL;
        return NULL;
    }
}

void Player::attackCallback(float test) {
    if(mainLayer->getEnemy(this->targetEnemyIdx)->beHit(this->_attack) == 1) {
        mainLayer->eraseEnemy(this->targetEnemyIdx);
    }
}

void Player::generalAttack(float radius) {
    //log(mainLayer->_enemys.size());
    if(this->_fsm->getState() == "idle" && mainLayer->isEnemyInRange(this)) {
        log("Player: attacking enemy");
        Vec2 attackTarget = mainLayer->attackTarget(this);
        radius = attackTarget.x - this->getPositionX();
        auto weapon = this->attack(radius);
        auto attackTime = (attackTarget-this->getPosition()).getLength()/weapon->getSpeed();
        this->scheduleOnce(schedule_selector(Player::attackCallback), attackTime);
        this->scheduleUpdate();
    }
}

void Player::playerDrop(int start, int end, std::function<void ()> callback) {
    std::function<void()> onDrop = CC_CALLBACK_0(Player::onDrop, this, start, end, callback);
    _fsm->setOnEnter("droping", onDrop);
    _fsm->doEvent("drop");
}

void Player::onDrop(int start, int end, std::function<void()> callback) {
    if (this->getPositionX() > start-this->getContentSize().width/2 && this->getPositionX()+-this->getContentSize().width/2 < end) {
        log("Player: drop!");
        //DROPING = true;
        auto preStatus = this->_fsm->getState();
        //_fsm->doEvent("stop");
        this->stopAllActions();
        background->stopAllActions();
        Vec2 ground;
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        ground.y = origin.y + visibleSize.height*Player::height/2;
        ground.x = this->getPositionX();
        auto time = (this->getPosition()-ground).getLength()/400;
        auto drop = MoveTo::create(time, ground);
        //drop->setTag(200);
        
        
        _fsm->setOnEnter("walking", callback);
        auto funcwalk = [&]()
        {
            _fsm->doEvent("dropwalk");
        };
        auto _callbackwalk = CallFunc::create(funcwalk);
        
        auto funcstop = [&]()
        {
            _fsm->doEvent("dropstop");
        };
        auto _callbackstop = CallFunc::create(funcstop);
        
        if(preStatus == "walking") {
            auto _seq = Sequence::create(drop, _callbackwalk, NULL);
            this->runAction(_seq);
        }
        else {
            auto _seq = Sequence::create(drop, _callbackstop, NULL);
            this->runAction(_seq);
        }
        //auto _sep = Sequence::create(drop, onWalk, NULL);
    }
}

Weapon* Player::attack(float radius)
{
    //add weapon
    Weapon *weapon = Weapon::create(currentWeapon);
    
    mainLayer->_background->addChild(weapon);

    Vec2 groundPos = mainLayer->getOrigin() + Vec2(0.f, this->getContentSize().height);
    Vec2 pos = mainLayer->_background->convertToNodeSpace(this->getPosition());
    weapon->setPosition(pos.x, pos.y);
    //scene->addChild(weapon);
    
    Vec2 target(pos.x+radius, groundPos.y);
    
    weapon->shootTo(target);
    //-------reset attack value of player according to weaponType---xiaojing -------------//
	
	 _attack+= weapon->_weaponPower;
	//-------end edited by xiaojing---------------------------------------------------//
    return weapon;
}

void Player::walkTo(Vec2 dest, int boundry)
{
    std::function<void()> onWalk = CC_CALLBACK_0(Player::onWalk, this, dest, boundry);
    _fsm->setOnEnter("walking", onWalk);
    _fsm->doEvent("walk");
}

void Player::stop(float r) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float upGround = origin.y + visibleSize.height*Player::height*3;
    float downGround = origin.y + visibleSize.height*Player::height/2;
    
    if(this->getPositionY() < upGround - 20 &&
       this->getPositionY() > downGround + 20) {
    }
    else {
        this->unschedule(schedule_selector(Player::stop));
        //this->scheduleUpdate();
        //this->stopActionByTag(WALKTO_TAG);
        //this->stopAllActions();
        //this->background->stopAllActions();
        //this->background->stopActionByTag(WALKTO_TAG);
        _fsm->doEvent("stop");
    }
}

//void Player::stop() {
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    float upGround = origin.y + visibleSize.height*Player::height*3;
//    float downGround = origin.y + visibleSize.height*Player::height/2;
//    
//    if(this->getPositionY() < upGround - 20 &&
//       this->getPositionY() > downGround + 20) {
//        float waitTime = 0.1;
//        this->schedule(schedule_selector(Player::stop), waitTime);
//        this->scheduleUpdate();
//    }
//    else {
//        this->stop(0.1);
//    }
//    
//}

void Player::stop() {
    _fsm->doEvent("stop");
}

//actually player stay in the center of the screeen but the background would move to the opposite position as the target
//Move horizontally //added by Zhenni
void Player::constructActionArray(int start, int end,
                                  Vector< FiniteTimeAction * > &arrayOfActions,
                                  Vector< FiniteTimeAction * > &backgroundActions) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int minDiff = -visibleSize.width/2;
    int firstChange = 0;
    int secondChange = background->getContentSize().width*5/4 - visibleSize.width*2;
    int maxDiff = background->getContentSize().width*5/4 - visibleSize.width*3/2;
    auto empty = Vec2(0, 0);
    if (start < end) {
        if(start < firstChange) {
            Vec2 diff;
            if(end < firstChange) {
                diff = Vec2(end - start, 0);
                
            }
            else {
                diff = Vec2(firstChange - start, 0);
            }
            auto time = diff.getLength()/_speed;
            auto move = MoveBy::create(time, diff);
            auto bmove = MoveBy::create(time, empty);
            arrayOfActions.pushBack(move);
            backgroundActions.pushBack(bmove);
        }
        if (start < secondChange && end > firstChange) {
            Vec2 diff;
            if( start > firstChange ) {
                if( end < secondChange ) {
                    diff = Vec2(end - start, 0);
                }
                else {
                    diff = Vec2(secondChange - start, 0);
                }
            }
            else {
                if( end < secondChange ) {
                    diff = Vec2(end - firstChange, 0);
                }
                else {
                    diff = Vec2(secondChange - firstChange, 0);
                }
            }
            auto time = diff.getLength()/_speed;
            auto move = MoveBy::create(time, empty);
            auto bmove = MoveBy::create(time, -diff);
            arrayOfActions.pushBack(move);
            backgroundActions.pushBack(bmove);
        }
        if (start < maxDiff && end > secondChange) {
            Vec2 diff;
            if( start > secondChange ) {
                if( end < maxDiff ) {
                    diff = Vec2(end - start, 0);
                }
                else {
                    diff = Vec2(maxDiff - start, 0);
                }
            }
            else {
                if( end < maxDiff ) {
                    diff = Vec2(end - secondChange, 0);
                }
                else {
                    diff = Vec2(maxDiff - secondChange, 0);
                }
            }
            auto time = diff.getLength()/_speed;
            auto move = MoveBy::create(time, diff);
            auto bmove = MoveBy::create(time, empty);
            arrayOfActions.pushBack(move);
            backgroundActions.pushBack(bmove);
        }
    }
    else {
        if(start > secondChange) {
            Vec2 diff;
            if(end > secondChange && end < maxDiff) {
                diff = Vec2(end - start, 0);
                
            }
            else {
                diff = Vec2(secondChange - start, 0);
            }
            auto time = diff.getLength()/_speed;
            auto move = MoveBy::create(time, diff);
            //move->setTag(1);
            auto bmove = MoveBy::create(time, empty);
            //bmove->setTag(1);
            arrayOfActions.pushBack(move);
            backgroundActions.pushBack(bmove);
        }
        if (start > firstChange && end < secondChange) {
            Vec2 diff;
            if( start < secondChange ) {
                if( end > firstChange ) {
                    diff = Vec2(end - start, 0);
                }
                else {
                    diff = Vec2(firstChange - start, 0);
                }
            }
            else {
                if( end > firstChange ) {
                    diff = Vec2(end - secondChange, 0);
                }
                else {
                    diff = Vec2(firstChange - secondChange, 0);
                }
            }
            auto time = diff.getLength()/_speed;
            auto move = MoveBy::create(time, empty);
            //move->setTag(1);
            auto bmove = MoveBy::create(time, -diff);
            //bmove->setTag(1);
            arrayOfActions.pushBack(move);
            backgroundActions.pushBack(bmove);
        }
        if (start > minDiff && end < firstChange) {
            Vec2 diff;
            if( start < firstChange ) {
                if( end > minDiff) {
                    diff = Vec2(end - start, 0);
                }
                else {
                    diff = Vec2(minDiff - start, 0);
                }
            }
            else {
                if( end > minDiff) {
                    diff = Vec2(end - firstChange, 0);
                }
                else {
                    diff = Vec2(minDiff - firstChange, 0);
                }
            }
            auto time = diff.getLength()/_speed;
            auto move = MoveBy::create(time, diff);
            //move->setTag(1);
            auto bmove = MoveBy::create(time, empty);
            //bmove->setTag(1);
            arrayOfActions.pushBack(move);
            backgroundActions.pushBack(bmove);
        }
    }
    
}

void Player::onWalk(Vec2 dest, int boundry) {
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vector< FiniteTimeAction * > arrayOfActions;
    Vector< FiniteTimeAction * > backgroundActions;
    auto pPos = this->getPosition();
    auto bPos = background->getPosition();
    auto empty = Vec2(0, 0);
    
    
    if(dest.x < origin.x + visibleSize.width/2) {
        if(pPos.x - bPos.x >= boundry - 10) {
            this->constructActionArray(pPos.x - bPos.x, boundry, arrayOfActions, backgroundActions);
            Vec2 climbBy(0, origin.y + visibleSize.height*Player::height*3 - pPos.y);
            auto time = climbBy.getLength()/_speed;
            auto climb = MoveBy::create(time, climbBy);
            //climb->setTag(1);
            auto bmove = MoveBy::create(time, empty);
            arrayOfActions.pushBack(climb);
            backgroundActions.pushBack(bmove);
            this->constructActionArray(boundry, -visibleSize.width/2, arrayOfActions, backgroundActions);
        }
        else {
            this->constructActionArray(pPos.x - bPos.x, -visibleSize.width/2, arrayOfActions, backgroundActions);
        }
        this->setFlippedX(true);
    }
    else {
        if(pPos.x - bPos.x <= boundry + 10) {
            this->constructActionArray(pPos.x - bPos.x,  boundry, arrayOfActions, backgroundActions);
            Vec2 climbBy(0, origin.y + visibleSize.height*Player::height/2 - pPos.y);
            auto time = climbBy.getLength()/_speed;
            auto climb = MoveBy::create(time, climbBy);
            //climb->setTag(1);
            auto bmove = MoveBy::create(time, empty);
            arrayOfActions.pushBack(climb);
            backgroundActions.pushBack(bmove);
            this->constructActionArray(boundry,  background->getContentSize().width*5/4 - visibleSize.width/2, arrayOfActions, backgroundActions);
        }
        else {
            this->constructActionArray(pPos.x - bPos.x,  background->getContentSize().width*5/4 - visibleSize.width/2, arrayOfActions, backgroundActions);
        }
        this->setFlippedX(false);
    }

    //lambda function
    auto func = [&]()
    {
        this->_fsm->doEvent("stop");
    };
    auto callback = CallFunc::create(func);

    arrayOfActions.pushBack(callback);
    backgroundActions.pushBack(callback);

    //create sequence for two backgrounds and player(some bugs)
    auto _bseq = Sequence::create(backgroundActions);
    auto _seq = Sequence::create(arrayOfActions);
    
    _bseq->setTag(WALKTO_TAG);
    _seq->setTag(WALKTO_TAG);
    
    //run action sequnce
    this->runAction(_seq);
    background->runAction(_bseq);

    //******************************************************************************************
    //added by Wenbo Lin
    this->playAnimationForever(0);
    //******************************************************************************************
    
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    auto curPos = background->getPosition();
//    Vector< FiniteTimeAction * > arrayOfActions;
//    Vector< FiniteTimeAction * > backgroundActions;
//    //Vector< FiniteTimeAction * > backgroundActions1;
//    Vec2 dest1, dest2, dest3, dest4, diff4 = visibleSize/2;
//    auto backgroundPos = background->getPosition();
//    auto empty = Vec2(0, 0);
//    //auto background1Pos = background1->getPosition();
//    
//    
//    //flip when moving backward
//    if(dest.x < origin.x + visibleSize.width/2) {
//        if(this->getPositionX() > origin.x + visibleSize.width/2) {
//            Vec2 dest0;
//            dest0.x = origin.x + visibleSize.width/2;
//            dest0.y = this->getPositionY();
//            auto diff0 = dest0 - this->getPosition();
//            auto time0 = diff0.getLength()/_speed;
//            auto move0 = MoveTo::create(time0, dest0);
//            auto bmove0 = MoveBy::create(time0, empty);
//            arrayOfActions.pushBack(move0);
//            backgroundActions.pushBack(bmove0);
//        }
//        dest1.x = -boundry;
//        dest3.x = origin.x;
//        dest2.y = origin.y + visibleSize.height*Player::height*3;
//        dest4.x = origin.x;
//        if(this->getPositionX() < origin.x + visibleSize.width/2) {
//            diff4 = dest4 - Vec2(this->getPositionX(), dest4.y);
//        }
//        this->setFlippedX(true);
//    }
//    else {
//        if(this->getPositionX() < origin.x + visibleSize.width/2) {
//            Vec2 dest0;
//            dest0.x = origin.x + visibleSize.width/2;
//            dest0.y = this->getPositionY();
//            auto diff0 = dest0 - this->getPosition();
//            auto time0 = diff0.getLength()/_speed;
//            auto move0 = MoveTo::create(time0, dest0);
//            auto bmove0 = MoveBy::create(time0, empty);
//            arrayOfActions.pushBack(move0);
//            backgroundActions.pushBack(bmove0);
//        }
//        dest1.x = -boundry;
//        dest3.x = visibleSize.width*3/2 - background->getContentSize().width*5/4;
//        dest2.y = origin.y + visibleSize.height*Player::height;
//        dest4.x = origin.x + visibleSize.width;
//        if(this->getPositionX() > origin.x + visibleSize.width/2) {
//            diff4 = dest4 - Vec2(this->getPositionX(), dest4.y);
//        }
//        this->setFlippedX(false);
//    }
//    dest1.y = origin.y;
//    dest2.x = visibleSize.width/2;
//    dest3.y = origin.y;
//    dest1 += visibleSize/2;
//    dest3 += visibleSize/2;
//    dest4.y = dest2.y;
//    //calculate the time needed to move
//    
//    auto diff1 = dest1 - curPos;
//    auto time1 = diff1.getLength()/_speed;
//    auto move1 = MoveBy::create(time1, empty);
//    auto bmove1 = MoveTo::create(time1, dest1);
//    //auto bmove11 = MoveTo::create(time1, dest1 + background1Pos - backgroundPos);
//    auto time2 = (dest2 - this->getPosition()).getLength()/_speed;
//    auto climb = MoveTo::create(time2, dest2);
//    auto bmove2 = MoveBy::create(time2, empty);
//    
//    if((dest.x < origin.x + visibleSize.width/2 && curPos.x <= dest1.x)
//       ||(dest.x > origin.x + visibleSize.width/2 && curPos.x >= dest1.x)) {
//        arrayOfActions.pushBack(move1);
//        arrayOfActions.pushBack(climb);
//        backgroundActions.pushBack(bmove1);
//        backgroundActions.pushBack(bmove2);
//        //backgroundActions1.pushBack(bmove11);
//        //backgroundActions1.pushBack(bmove2);
//    }
//    else {
//        dest1 = curPos;
//    }
//    auto diff3 = dest3 - dest1;
//    auto time3 = diff3.getLength()/_speed;
//    auto move2 = MoveBy::create(time3, empty);
//    auto bmove3 = MoveTo::create(time3, dest3);
//    
//    auto time4 = diff4.getLength()/_speed;
//    auto move4 = MoveTo::create(time4, dest4);
//    auto bmove4 = MoveBy::create(time4, empty);
//    //auto bmove31 = MoveTo::create(time3, dest3 + background1Pos - backgroundPos);
//    
//    arrayOfActions.pushBack(move2);
//    backgroundActions.pushBack(bmove3);
//    arrayOfActions.pushBack(move4);
//    backgroundActions.pushBack(bmove4);
//    //backgroundActions1.pushBack(bmove31);
//    
//    //auto movePlayer = MoveTo::create(playerTime, dest);
//   
//    
//    //lambda function
//    auto func = [&]()
//    {
//        this->_fsm->doEvent("stop");
//    };
//    auto callback = CallFunc::create(func);
//    
//    arrayOfActions.pushBack(callback);
//    backgroundActions.pushBack(callback);
//    
//    //create sequence for two backgrounds and player(some bugs)
//    //auto _seqPlayer = Sequence::create(movePlayer, callback, nullptr);
//    auto _bseq = Sequence::create(backgroundActions);
//    //auto _bseq1 = Sequence::create(backgroundActions1);
//    auto _seq = Sequence::create(arrayOfActions);
//    this->runAction(_seq);
//    
//    //run action sequnce
//    background->runAction(_bseq);
//    //background1->runAction(_bseq1);
//    
//    //******************************************************************************************
//    //added by Wenbo Lin
//    this->playAnimationForever(0);
//    //******************************************************************************************
}

Vec2 Player::getCurPos()
{
    auto curPos = this->getPosition();
    Vec2 result = Vec2(curPos.x, curPos.y);
    return result;
}
/*
=======
    dest.y = origin.y + visibleSize.height*Player::height*3;
    dest.x = curPos.x;
    
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

Vec2 Player::getCurPos()
{
    auto curPos = this->getPosition();
    Vec2 result = Vec2(curPos.x, curPos.y);
    return result;
}
*/

int Player::getMoney()
{
    return money;
}

Rect Player::getBoundingBox()
{
    /*由于Sprite是放在Player上的，所以要检测Player的碰撞范围*/
    Size spriteSize=getContentSize();
    Vec2 entityPos=getCurPos();//获取player中心点
    
    //获取Player左下角的坐标值
    int x=entityPos.x-spriteSize.width/4;
    int y=entityPos.y-spriteSize.height/2;
    
    return Rect(x,y,spriteSize.width/2,spriteSize.height);
}
Rect Player::getAttackBox() {
    /*由于Sprite是放在Player上的，所以要检测Player的碰撞范围*/
    Size spriteSize=getContentSize();
    Vec2 entityPos=getCurPos();//获取player中心点
    //获取Player attack box左下角的坐标值
    int x=entityPos.x-spriteSize.width/4;
    int y=0;
    //判断攻击方向
    if(this->isFlippedX()) {
        x=entityPos.x+spriteSize.width/4 - _attackRange;
    }
    // attack range 为横向，纵向无限制条件
    return Rect(x, y, _attackRange, Director::getInstance()->getVisibleSize().height);
}
//reduce the _health value of current animal Xiaojing ***************//
void Player::beHit(int attack){
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
