//
//  Weapon.cpp
//  brave
//
//  Created by Yafu Li on 9/21/14.
//
//

#include "Weapon.h"

extern Scene* scene;

void Weapon::addAnimation()
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
void Weapon::playAnimationForever(int index)
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


bool Weapon::initWithWeaponType(WeaponType type)
{
    std::string sfName = "";
    _type = type;
    _speed = 100;
	_seq = nullptr;
    int animationFrameNum[1] ={1};
    int animationFrameNum2[5] ={10, 3, 3, 2, 0};
    
    //setup according to PlayerType
    switch(type)
    {
        case WeaponType::COCONUT:
            sfName = "coconut1-1-1.png";
            _name = "coconut1";
            _animationNum = 1;
            _speed = 100;
            _animationFrameNum.assign(animationFrameNum, animationFrameNum + 1);
            break;
        case WeaponType::BAMBOO:
            sfName = "arrow1-1-1.png";
            _name = "arrow1";
            _animationNum = 3;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 1);
            break;
        case WeaponType::HONEYNEST:
            sfName = "enemy2-1-1.png";
            _name = "enemy2";
            _animationNum = 4;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 1);
            break;
        case WeaponType::ARROW:
            sfName = "arrow1-1-1.png";
            _name = "arrow1";
            _animationNum = 1;
            _animationFrameNum.assign(animationFrameNum2, animationFrameNum2 + 1);
            break;
    }
    this->initWithSpriteFrameName(sfName);
    std::string animationNames[] = {"throw"};
    _animationNames.assign(animationNames, animationNames + 1);
    
    //load animation
    this->addAnimation();
    return true;
}

Weapon* Weapon::create(WeaponType type)
{
    Weapon* weapon = new Weapon();
    if(weapon && weapon->initWithWeaponType(type))
    {
        weapon->autorelease();
        return weapon;
    }
    else
    {
        delete weapon;
        weapon = NULL;
        return NULL;
    }
}

void Weapon::shootTo(Vec2 dest, std::function<void()> removefunc)
{
    //stop current moving action, if any.
    if(_seq!=nullptr)
        this->stopAction(_seq);
    
    auto curPos = this->getPosition();
    
    //flip when moving backward
    if(curPos.x > dest.x)
        this->setFlippedX(true);
    else
        this->setFlippedX(false);
    
    //calculate the time needed to move
    auto diff = dest - curPos;
    auto time = diff.getLength()/_speed;
    
    //设置投掷轨迹
    CCSize s = CCDirector::sharedDirector()->getWinSize();
//    // 创建第一个贝塞尔曲线
//
//    
//    ccBezierConfig bezier;
//    bezier.controlPoint_1 = CCPointMake(0, s.height/2);
//    //bezier.controlPoint_2 = CCPointMake(300, -s.height/2);
//    bezier.endPosition = CCPointMake(300,100);
//    //创建一个贝塞尔曲线动画，这个CCBezierBy的意思是当前位置为曲线起点。曲线的其它点是相对于它的位置。
//    CCActionInterval*  bezierForward = CCBezierBy::create(time, bezier);
    
    //auto move = MoveTo::create(time, dest);
    
    //auto jump = JumpBy::create(time, dest, s.height/10, 1);
    auto actionTo = JumpTo::create(2, dest, 150, 1);
    

    //lambda function
    auto func = [&]()
    {
        this->stopAllActions();
        
        removefunc();
                //_seq = nullptr;
    };
    auto callback = CallFunc::create(func);
    auto _seq = Sequence::create(actionTo, callback, nullptr);
    
    this->runAction(_seq);
    this->playAnimationForever(0);
}