#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Tree.h"
#include "Weapon.h"
#include "Animal.h"
#include "Enemy.h"
#include <iostream>


//******************************************************************************************************************
//added by Wenbo Lin
#include "Progress.h"
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
    void activateWeaponOption(Ref* pSender);
    LabelTTF* label;
    
    void spriteMoveFinished(CCNode* sender);
    //initialize trees
    void initTrees(int num);
    
    // enemy module
    void enemyMove(float dt);
    //
//    bool closeToEnemy( obj);
    
      
	//------blood progress----------------//
	void addProgress();
private:
    Animal* _animal;
    Player* _player;
	Enemy* _enemy1;
    Enemy* _enemy2;
    Enemy* _enemy3;
    Vector<Enemy*> _enemys;
    
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
    //******************************************************************************************************************
};

#endif // __HELLOWORLD_SCENE_H__
