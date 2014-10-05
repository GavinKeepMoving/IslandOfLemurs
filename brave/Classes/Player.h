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
    static float height;
    bool initWithPlayerType(PlayerType type);
    static Player* create(PlayerType type);
    void walkTo(Vec2 dest);
    void addAnimation();
    void playAnimationForever(int index);
    void onWalk(Vec2 dest);
    void climbDown(Vec2 dest);
    void climbUp(Vec2 dest);
    Vec2 getCurPos();
    //lishi
    int getMoney();
    CCRect getBoundingBox();
    
private:
    //Action _seq;
    float _speed;
    PlayerType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
    Sequence* _seq;
    int _money;
    //currentPos
    
public:
    Sprite* background;
    Vec2 curPos;

};

#endif
