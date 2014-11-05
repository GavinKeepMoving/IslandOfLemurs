//
//  Enemy2.h
//  brave
//
//  Created by Lishi Jiang on 10/19/14.
//
//

#ifndef __brave__Enemy2__
#define __brave__Enemy2__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Progress.h"
USING_NS_CC;
using namespace cocostudio;

#define WALK_SPEED 1
#define WALK_LEFT 1
#define WALK_RIGHT -1

enum Enemy2State
{
    IDLE = 0,      //默认
    WALK,          //行走
    ATTACK,         //射击
    BEHIT,
    DEAD        //子弹
};

class Enemy2 : public Node
{
public:
    Enemy2();
    CREATE_FUNC(Enemy2);
    void update(float dt);              //更新角色状态
    void updateAnimation();             //状态判断及播放动画
    void updateMovement();              //行走状态
    void play(std::string animName);    //播放动画
    bool isLockState();                 //锁定角色状态
    
    inline void setState(Enemy2State state) {newState = state;} //设置角色状态
    void setDirection(int newDirection); //设置方向
    Sprite* _background;
    /* added by Zhe Liu*/
    double mindist = 20;
    int getAttack(){return _attack;}
    void setBlood();
    int behit(int attack);
    //progres*****xiaojing****//
	Progress* _progress;
	//********************//
    
    //add by wenbo
    void playSound();
    //end add by wenbo
    
private:
    int _attack;
    int _blood;
    Sprite* Enemy2Node;
    ArmatureAnimation* animation;     //动画变量
    Enemy2State currentState;           //当前状态
    Enemy2State newState;               //更换状态
    int direction;                      //方向
    bool lockState;                     //锁定状态
    //add by wenbo
    unsigned int _enemySoundEffectId;
    void onAnimationEvent(Armature *pArmature, MovementEventType eventType, const char *animationID);                   //角色射击状态
};

#endif /* defined(__brave__Enemy2__) */
