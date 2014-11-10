//
//  WeaponManager.cpp
//  brave
//
//  Created by Yafu Li on 11/9/14.
//
//

#include "WeaponManager.h"

WeaponManager* WeaponManager::create(Sprite* background)
{
    WeaponManager* weaponManager = new WeaponManager();
    weaponManager->_background = background;
    return weaponManager;
}

void WeaponManager::bindPlayer(Player* player)
{
    this->_player = player;
    this->_player->retain();//引用计数 +1
}


Tree* WeaponManager::getNearestTree(std::vector<Tree*> trees)
{
    if (trees.size() > 0) {
//        Vec2 playerPos = _background->convertToNodeSpace(_player->getPosition());
//
//        // find the nearest enemy and judge whether it is in the attacking scope
//        float tree_dist = abs(trees[1]->treeSprite->getPositionX() - trees[0]->treeSprite->getPositionX()) / 2;
//        validAttackRadius = trees.size() > 1 ? tree_dist : 200.;
//        for (int i = 0;i < trees.size(); i++){
//            
//            int dist = abs(playerPos.x - trees[i]->treeSprite->getPositionX());
//            
//            if (dist > validAttackRadius) continue;
//            
//            if (_player->isFlippedX() * (playerPos.x - trees[i]->treeSprite->getPositionX()) > 0)
//                return trees[i];
//            
//            
//        }
        
        float distance = INT_MAX;
        Rect playerRect = _player->getAttackBox();
        for (int i = 0;i < trees.size(); i++) {
            Vec2 treePos = _background->convertToWorldSpace(trees[i]->treeSprite->getPosition());
            if(playerRect.containsPoint(treePos)) {
                
                return trees[i];
            }
        }
    }
    return NULL;

}

float WeaponManager::getAttackRadius(Tree* t) {
    Vec2 treePos = _background->convertToWorldSpace(t->treeSprite->getPosition());
    
    Vec2 playerPos = _player->getPosition();
    
    return treePos.x - playerPos.x;
}
