//
//  Player.h
//  brave
//
//  Created by Huang Zhenni on 9/14/14.
//
//

#ifndef __Player__
#define __Player__
#include "cocos2d.h"
#include "FSM.h"
#include "Weapon.h"
USING_NS_CC;

class Player : public Sprite
{
public:
    enum PlayerType
    {
        PLAYER,
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
    enum ActionTag
    {
        WALKTO_TAG =100
    };
    static float height;
    bool initWithPlayerType(PlayerType type);
    static Player* create(PlayerType type);
    void walkTo(Vec2 dest);
    void walkTo(Vec2 dest, int boundry);
    void addAnimation();
    void playAnimationForever(int index);
    void onWalk(Vec2 dest, int boundry);
    void initFSM();
    void stop();
    void stop(float r);
    Weapon* attack(float radius = 250.f);
    
    
    void setWeapon(Weapon::WeaponType weaponType) {
        currentWeapon = weaponType;
    }
    
    Vec2 getCurPos();
    Sprite* background;
    Sprite* background1;
    Vec2 curPos;
    //lishi
    int getMoney();
    Rect getBoundingBox();
    int money;
	
	//blood attribute  xiaojing
	int _health;  //current blood 
	int _maxHealth;  //total blood
	int _attack;  //each attack harm enemy
	void beHit(int attack);
    
    //Zhenni
    Rect getAttackBox();
    int targetEnemyIdx;
    void attackCallback(float test);
    void generalAttack(float radius = 250.f);
    //void playerDrop(int start, int end);
    void playerDrop(int start, int end, std::function<void()> callback);
    void onDrop(int start, int end, std::function<void()> callback);
    void constructActionArray(int start, int end,Vector< FiniteTimeAction * > &arrayOfActions, Vector< FiniteTimeAction * > &backgroundActions);
private:
    //Action _seq;
    float _speed;
    float _attackSpeed; //wait duration for attack //Zhenni
    float _attackRange; //horizontal attack range // Zhenni
    PlayerType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
    Sequence* _seq;
    //currentPos
    FSM *_fsm;
    Weapon::WeaponType currentWeapon;
    bool DROPING;
    //std::vector<Enemy*> *_enemys;

};

#endif
