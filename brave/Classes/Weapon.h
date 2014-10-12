//
//  Weapon.h
//  brave
//
//  Created by Yafu Li on 9/21/14.
//
//

#ifndef brave_Weapon_h
#define brave_Weapon_h

#include "cocos2d.h"
USING_NS_CC;

class Weapon : public Sprite {
public:
    enum WeaponType
    {
        COCONUT,
        WATER,
        BAMBOO,
        HONEYNEST,
        
        ARROW
    };
    
    bool initWithWeaponType(WeaponType type);
    static Weapon* create(WeaponType type);
    
    void addAnimation();
    void playAnimationForever(int index);
    void shootTo(Vec2 dest);
    
private:
    //Action _seq;
    float _speed;
    WeaponType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
    Sequence* _seq;

public:
    int _weaponPower;  //each weapon will add a value to player's attack
};



#endif
