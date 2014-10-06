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
    
   // Weapon* attack(float radius);
    
    Vec2 getCurPos();
    
    void onWalk(Vec2 dest);
    
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
    
public:
    Sprite* background;
    Sprite* background1;
    Vec2 curPos;
};


#endif /* defined(__brave__Enemy__) */
