#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Tree.h"
#include "Weapon.h"
#include "Animal.h"
#include "Enemy.h"
#include "Animal.h"
#include <iostream>


//******************************************************************************************************************
//added by Wenbo Lin
#include "Progress.h"
#include "BananaManger.h"
//******************************************************************************************************************

USING_NS_CC;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    virtual void update(float delta);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    //add Attack option top right bar
    void initWeaponOptionsBar(Vec2 origin, Size visibleSize);
    void initAnimalOptionsBar();
    void activateWeaponOption(Ref* pSender, int index);
    void callAnimalHelper(Ref* pSender, int index);
    LabelTTF* label;
    
    void spriteMoveFinished(CCNode* sender);
    //initialize trees
    void initTrees(int num);
    
    // enemy module
    void enemyMove(float dt);
    void animalMove(float dt);
    void addEnemy();
//    void 
//    bool closeToEnemy( obj);
	 void enemyDead(Ref* obj);
     void animalDead(Ref* obj);
	//------blood progress----------------//
	void addProgress();
    
    /******************Begin-Added by Yafu*****************************/
    Vec2 getOrigin() {
        return origin;
    }
    /******************End-Added by Yafu*****************************/

    /******************Begin-Added by Zhenni ************************/
    // judge if the player can attack enemy
    bool isEnemyInRange(Player* p);
    
    bool isOnTree(Player* p);
    
    Vec2 attackTarget(Player* p);
    
    Enemy * getEnemy(int i) {
        return _enemys[i];
    }
    void eraseEnemy(int i) {
        if(_enemys.size() <= i) {
            return;
        }
        _enemys.erase(_enemys.begin() + i);
    }
    /******************End-Added by Zhenni ************************/
private:
    Animal* _animal;
    Player* _player;
	Enemy* _enemy1;
    Enemy* _enemy2;
    Enemy* _enemy3;
    std::vector<Enemy*> _enemys;
    std::vector<Animal*> _animals;
    Size visibleSize;
    Vec2 origin;
    EventListenerTouchOneByOne* _listener_touch;
    EventListenerPhysicsContact* _listener_contact;
    

public:
    Sprite *_background;
    Sprite *_background1;
    std::vector<Tree*> _trees;
    //******************************************************************************************************************
    //added by Wenbo Lin
    Progress* _progress;
    std::vector<Sprite*> _ropes;
    Sprite* treeBase;
    void deleteTree();
    BananaManger* bananaManger;
    //End added by Wenbo Lin
    //******************************************************************************************************************
};

#endif // __HELLOWORLD_SCENE_H__
