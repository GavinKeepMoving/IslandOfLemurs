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
//<<<<<<< HEAD
//#include "GameOverLayer.h"
//=======
#include "Enemy2.h"
//>>>>>>> d5d27db014c320a5579e3b82d0284fc1616955e2

//******************************************************************************************************************
//added by Wenbo Lin
#include "Progress.h"
#include "BananaManger.h"
#include "Enemy2Manager.h"
#include "Animal2Manager.h"
#include "SimpleAudioEngine.h" 
//******************************************************************************************************************
class Enemy2Manager;
USING_NS_CC;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    /*********** begin add by Wenbo Lin **************/
    void playMusic();
    void setParameters();
    void addCloseIcon();
    void addBackground();
    void addWeaponOptionBar();
    void addHelloWorldLabel();
    
    void addRoles();
    //method in addRoles
    void addAnimations();
    void addTrees();
    void addFires();
    void addPlayer();
    void addEnemies();
    void addBananas();
    void addEnemiesAI(float dt);
    //end of method in addRoles
    
    void setScheduleAndProgress();
    void addgotoItem();
    /*********** ended add by Wenbo Lin **************/
    
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
    /*** added by Zhe Liu ***/
//    void enemyMove(float dt);
//    void animalMove(float dt);
    void addEnemy(float dt);
    std::vector<Tree*> getTrees(){return _trees;}
    void updateEnemy(float dt);
    void updateAnimal(float dt);
    /*** added by Zhe Liu ***/
    
    
//    void
//    bool closeToEnemy( obj);
	 void enemyDead(Ref* obj);
     void animalDead(Ref* obj);
	
    
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
    
    int boundry;
    Vec2 touchPos;
    /******************End-Added by Zhenni ************************/
	
	
	/**************added by xiaojing***************/
	 //------blood progress----------------//
	void addProgress();
	bool enemyAllDead();
	void gotoNextLevel(Ref* obj);
	void showNextLevelItem();
	/*********************************************/
	
private:
    Animal* _animal;
    Player* _player;
	Enemy* _enemy1;
    Enemy2* _enemy2;
    Enemy* _enemy3;
    std::vector<Enemy*> _enemys;
    std::vector<Animal*> _animals;
    Size visibleSize;
    Vec2 origin;
    EventListenerTouchOneByOne* _listener_touch;
    EventListenerPhysicsContact* _listener_contact;
    

public:
//    __Array* _enemy2Arr;
//    __Array* _animal2Arr;
    std::vector<Enemy2*> _enemy2Arr;
    std::vector<Animal2*> _animal2Arr;
    Sprite *_background;
    Sprite *_background1;
    std::vector<Tree*> _trees;
    int level = 0;
    //******************************************************************************************************************
    //added by Wenbo Lin
    Progress* _progress;
    std::vector<Sprite*> _ropes;
    Sprite* treeBase;
    void deleteTree();
    BananaManger* bananaManger;
    Enemy2Manager* _enemy2Manager;
    Animal2Manager* _animal2Manager;
    bool pause = false;
    //End added by Wenbo Lin
    //******************************************************************************************************************
	int gamelevel; // used to init different number of enemy according to level
	Menu* _menu;
	
	};

#endif // __HELLOWORLD_SCENE_H__
