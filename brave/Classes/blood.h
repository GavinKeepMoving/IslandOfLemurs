//
// Blood.h
//
//  Xiaojing Liu 10/06/2014
//
//

#ifndef __blood__
#define __blood__

#include "cocos2d.h"
#include "player.h"
USING_NS_CC;

class blood : public Sprite
{
public:
    static int value;
    blood();
    virtual ~blood();
    CREATE_FUNC(blood);
    
public:
    bool initBloodWithPlayerType(Player::PlayerType type);

    void reset(); //reset player's blood
    bool isAlive(); //
    bool isAttack(int attack);
public:
	bool _isCanAttack;
	int _health;
	int _maxHealth;
//private:
	//CCArray *_bloodarray; // store current role's blood
};

#endif /* defined(__blood__) */