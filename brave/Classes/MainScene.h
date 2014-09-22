#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    Player* _player;
	Player* _enemy1;
    EventListenerTouchOneByOne* _listener_touch;
    EventListenerPhysicsContact* _listener_contact;
};

#endif // __HELLOWORLD_SCENE_H__
