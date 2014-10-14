//
//  Fire.cpp
//  brave
//
//  Created by Wenbo Lin on 10/12/14.
//
//

#include "Fire.h"
#include "MainScene.h"

extern MainScene *mainLayer;

void Fire::addAnimation()
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
void Fire::playAnimationForever(int index)
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


bool Fire::initWithFireType(FireType type)
{
    std::string sfName = "";
    _type = type;
    _speed = 100;
    _seq = nullptr;
    int animationFrameNum[1] ={7};
    int animationFrameNum2[5] ={10, 3, 3, 2, 0};
    
    //setup according to PlayerType
    switch(type)
    {
        case FireType::SHOW:
            sfName = "fire-1-1.png";
            _name = "fire";
            _animationNum = 1;
            _speed = 100;
            _animationFrameNum.assign(animationFrameNum, animationFrameNum + 1);
            break;
    }
    this->initWithSpriteFrameName(sfName);
    std::string animationNames[] = {"fire"};
    _animationNames.assign(animationNames, animationNames + 1);
    
    //load animation
    this->addAnimation();
    return true;
}

Fire* Fire::create(FireType type)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/fire/fire.plist","image/fire/fire.pvr.ccz");
    
    Fire* Fire = new class Fire();
    if(Fire && Fire->initWithFireType(type))
    {
        Fire->autorelease();
        return Fire;
    }
    else
    {
        delete Fire;
        Fire = NULL;
        return NULL;
    }
}

void Fire::setFire() {
    this->playAnimationForever(0);
}