//
//  Animal2.h
//  brave
//
//  Created by Lishi Jiang on 10/26/14.
//
//

#ifndef __brave__Animal2__
#define __brave__Animal2__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

#define WALK_SPEED 1
#define WALK_LEFT 1
#define WALK_RIGHT -1


class Animal2 : public Node
{
public:
    enum Animal2State
    {
        IDLE = 0,      //默认
        WALK,          //行走
        ATTACK,         //射击
        BEHIT,
        DEAD        //子弹
    };
    Animal2(int i);
    static Animal2* create(int i);
    //CREATE_FUNC(Animal2);
    void update(float dt);              //更新角色状态
    void updateAnimation();             //状态判断及播放动画
    void updateMovement();              //行走状态
    void play(std::string animName);    //播放动画
    bool isLockState();                 //锁定角色状态
    
    inline void setState(Animal2State state) {newState = state;} //设置角色状态
    void setDirection(int newDirection); //设置方向
    Sprite* _background;
    int beHit(int attack);
    void setblood();
    int getAttack(){return _attack;}
    
private:
    Sprite* Animal2Node;
    ArmatureAnimation* animation;     //动画变量
    Animal2State currentState;           //当前状态
    Animal2State newState;               //更换状态
    int direction;                      //方向
    bool lockState;                     //锁定状态
    void onAnimationEvent(Armature *pArmature, MovementEventType eventType, const char *animationID);                   //角色射击状态
    int _blood;
    int _attack;
};

#endif /* defined(__brave__Animal2__) */
