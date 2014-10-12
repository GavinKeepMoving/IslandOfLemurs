//
//  Player.cpp
//  brave
//
//  Created by Huang Zhenni on 9/14/14.
//
//

#include "Player.h"
#include "Weapon.h"


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

bool Player::initWithPlayerType(PlayerType type)
{
    std::string sfName = "";
    money = 0;
    _type = type;
    _speed = 100;
	_seq = nullptr;
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
        //this->stopActionByTag(WALKING);
        this->stopAllActions();
        auto sfName = String::createWithFormat("%s-1-1.png", _name.c_str());
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName->getCString());
        this->setSpriteFrame(spriteFrame);
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


Weapon* Player::attack(float radius, Weapon::WeaponType weaponType)
{
    //add weapon
    Weapon *weapon = Weapon::create(weaponType);
    Vec2 pos = this->getPosition();
    weapon->setPosition(pos.x, pos.y);
    //scene->addChild(weapon);
    
    Vec2 target(pos.x+radius, pos.y);
    
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

void Player::stop() {
    this->stopAllActions();
    _fsm->doEvent("stop");
}

//actually player stay in the center of the screeen but the background would move to the opposite position as the target

void Player::onWalk(Vec2 dest, int boundry) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto curPos = background->getPosition();
    Vector< FiniteTimeAction * > arrayOfActions;
    Vector< FiniteTimeAction * > backgroundActions;
    Vector< FiniteTimeAction * > backgroundActions1;
    Vec2 dest1, dest2, dest3;
    auto backgroundPos = background->getPosition();
    auto background1Pos = background1->getPosition();
    
    //flip when moving backward
    if(dest.x < origin.x + visibleSize.width/2) {
        dest1.x = -boundry;
        dest3.x = origin.x;
        dest2.y = origin.y + visibleSize.height*Player::height*3;
        this->setFlippedX(true);
    }
    else {
        dest1.x = -boundry;
        dest3.x = visibleSize.width*3/2 - background->getContentSize().width*2;
        dest2.y = origin.y + visibleSize.height*Player::height;
        this->setFlippedX(false);
    }
    dest1.y = origin.y;
    dest2.x = visibleSize.width/2;
    dest3.y = origin.y;
    dest1 += visibleSize/2;
    dest3 += visibleSize/2;
    //calculate the time needed to move
    
    auto diff1 = dest1 - curPos;
    auto time1 = diff1.getLength()/_speed;
    auto empty = Vec2(0, 0);
    auto move1 = MoveBy::create(time1, empty);
    auto bmove1 = MoveTo::create(time1, dest1);
    auto bmove11 = MoveTo::create(time1, dest1 + background1Pos - backgroundPos);
    auto time2 = (dest2 - this->getPosition()).getLength()/_speed;
    auto climb = MoveTo::create(time2, dest2);
    auto bmove2 = MoveBy::create(time2, empty);
    
    if((dest.x < origin.x + visibleSize.width/2 && curPos.x <= dest1.x)
       ||(dest.x > origin.x + visibleSize.width/2 && curPos.x >= dest1.x)) {
        arrayOfActions.pushBack(move1);
        arrayOfActions.pushBack(climb);
        backgroundActions.pushBack(bmove1);
        backgroundActions.pushBack(bmove2);
        backgroundActions1.pushBack(bmove11);
        backgroundActions1.pushBack(bmove2);
    }
    else {
        dest1 = curPos;
    }
    auto diff3 = dest3 - dest1;
    auto time3 = diff3.getLength()/_speed;
    auto move2 = MoveBy::create(time3, empty);
    auto bmove3 = MoveTo::create(time3, dest3);
    auto bmove31 = MoveTo::create(time3, dest3 + background1Pos - backgroundPos);
    
    arrayOfActions.pushBack(move2);
    backgroundActions.pushBack(bmove3);
    backgroundActions1.pushBack(bmove31);
    
    //auto movePlayer = MoveTo::create(playerTime, dest);
   
    
    //lambda function
    auto func = [&]()
    {
        this->_fsm->doEvent("stop");
    };
    auto callback = CallFunc::create(func);
    
    arrayOfActions.pushBack(callback);
    backgroundActions.pushBack(callback);
    
    //create sequence for two backgrounds and player(some bugs)
    //auto _seqPlayer = Sequence::create(movePlayer, callback, nullptr);
    auto _bseq = Sequence::create(backgroundActions);
    auto _bseq1 = Sequence::create(backgroundActions1);
    auto _seq = Sequence::create(arrayOfActions);
    this->runAction(_seq);
    
    //run action sequnce
    background->runAction(_bseq);
    background1->runAction(_bseq1);
    
    //******************************************************************************************
    //added by Wenbo Lin
    this->playAnimationForever(0);
    //******************************************************************************************
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
