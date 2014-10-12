//
//  Enemy.h
//  brave
//
//  Created by Yafu Li on 10/5/14.
//
//

#ifndef __brave__Enemy__
#define __brave__Enemy__

#include "cocos2d.h"
#include "Player.h"
#include "Weapon.h"
#include "FSM.h"
#include "Tree.h"

//******************************************************************************************************************
//added by Wenbo Lin
#include "Progress.h"
//******************************************************************************************************************

USING_NS_CC;

class Enemy : public Player
{
public:
    enum EnemyType
    {
        ENEMY1,
        ENEMY2
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
    bool initWithPlayerType(EnemyType type);
    static Enemy* create(EnemyType type);
    void walkTo(Vec2 dest);
    void addAnimation();
    void playAnimationForever(int index);
    
   Weapon* attack(float radius);
    
    Vec2 getCurPos();
    
    void onWalk(Vec2 dest);
    // init enemy's fsm
    void initFSM();
    // get animate by type
    Animate* getAnimateByType(AnimationType type);
    // attack, behit
    void attack();
    void beHit(int attack);
    void addAttacker(Player* attacker);
    void removeAttacker(Player* attacker);
    bool isInRange(Player* enemy);
    
    std::string getState(){return _fsm->getState();}
    Vec2 getBestAttackPosition(const Vec2& pos, std::vector<Tree*> trees);
    float getMinDist(){return _minDist;}
    bool closeToTree(std::vector<Tree*> trees);
    
private:
    //Action _seq;
    float _speed;
    EnemyType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
    Sequence* _seq;
    //currentPos
    FSM* _fsm;
    float _radius = 0.1f;
    Vector<Player*> _attackers;
    float _minDist; // min distance for attacking

    
	
    //blood value  Xiaojing**************************//
	
	int _health;  //current blood 
	int _maxHealth;  //total blood
	int _attack;  //each attack harm player/animal
	
	//*******************************************************
public:
    Sprite* background;
    Sprite* background1;
    //******************************************************************************************************************
    //added by Wenbo Lin
    Progress* _progress;
    //******************************************************************************************************************
    Vec2 curPos;
};


#endif /* defined(__brave__Enemy__) */
