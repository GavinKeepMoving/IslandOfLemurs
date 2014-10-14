//
//  Animal.h
//  brave
//
//  Created by Yafu Li on 10/12/14.
//
//

#ifndef __brave__Animal__
#define __brave__Animal__

#include "cocos2d.h"
#include "Player.h"
#include "Weapon.h"
#include "FSM.h"
#include "Enemy.h"
class Enemy;

#include "FSM.h"
//******************************************************************************************************************
//added by Wenbo Lin
#include "Progress.h"
//******************************************************************************************************************

USING_NS_CC;

class Animal : public Player
{
public:
    enum AnimalType
    {
        CLOTHE,
        TIGER,
        FOX,
        ELEPHANT
    };
    enum AnimationType
    {
        WALKING = 0,
        ATTACKING = 1,
        DEAD = 2,
        BEINGHIT = 3,
        SKILL = 4
    };
    static float height;
    bool initWithPlayerType(AnimalType type);
    static Animal* create(AnimalType type);
    void walkTo(Vec2 dest);
    void addAnimation();
    void playAnimationForever(int index);
    Animate* getAnimateByType(AnimationType type);
    
    void attack();
    
    Vec2 getCurPos();
    
    void onWalk(Vec2 dest);
	//when hit reduce blood Xiaojing
    void beHit(int attack);
    
    /*** add by Zhe Liu ***/
    Vec2 getBestAttackPosition(std::vector<Enemy*> enemys,int& index);
    
    std::string getState(){return _fsm->getState();}
    
    void stop();
    
    void initFSM();
    
    int getAttack(){return _attack ;}
    /*** add by Zhe Liu ***/
private:
    //Action _seq;
    float _speed;
    AnimalType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
    Sequence* _seq;
    //currentPos
    //blood attribute  xiaojing
	FSM* _fsm;
	int _health;  //current blood 
	int _maxHealth;  //total blood
	int _attack;  //each attack harm enemy
    float _minDist;
	//****************************************//
public:
    Sprite* background;
    Sprite* background1;
    //******************************************************************************************************************
    //added by Wenbo Lin
    Progress* _progress;
    //******************************************************************************************************************
    Vec2 curPos;
};


#endif /* defined(__brave__Animal__) */
