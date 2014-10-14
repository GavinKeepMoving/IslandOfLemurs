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
        ANIMAL1,
        ANIMAL2
    };
    enum AnimationType
    {
        WALKING = 0,
        ATTACKING,
        DEAD,
        BEINGHIT,
        SKILL
    };
    static float height;
    bool initWithPlayerType(AnimalType type);
    static Animal* create(AnimalType type);
    void walkTo(Vec2 dest);
    void addAnimation();
    void playAnimationForever(int index);
    void attack();
    Weapon* attack(float radius);
    
    Vec2 getCurPos();
    
    void onWalk(Vec2 dest);
    //Begin add by Zhe Liu
    std::string getState(){return _fsm->getState();}
    // init enemy's fsm
    void initFSM();
    void stop();
    // get animate by type
    Animate* getAnimateByType(AnimationType type);
    Vec2 getBestAttackPosition(std::vector<Enemy*> enemys,int& index);
    float getMinDist(){return _minDist;}
    int getAttack(){return _attack;}
    //Edn add by Zhe Liu
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
    FSM* _fsm;
    float _minDist;
    int _attack;
    
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
