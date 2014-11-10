//
//  WeaponManager.h
//  brave
//
//  Created by Yafu Li on 11/9/14.
//
//

#ifndef __brave__WeaponManager__
#define __brave__WeaponManager__

#include "cocos2d.h"
#include "Weapon.h"
#include "Tree.h"
#include "Player.h"

USING_NS_CC;


class WeaponManager:public Node
{
public:
    
    static WeaponManager* create(Sprite* background);
    void bindPlayer(Player* player);
    Tree* getNearestTree(std::vector<Tree*> trees);
    float getAttackRadius(Tree* t);
    
    Sprite* _background;
    
private:
    Player* _player;
    float validAttackRadius = 100.;
};

#endif /* defined(__brave__WeaponManager__) */
