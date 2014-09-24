#include "MainScene.h"
#include "Player.h"
#include "Weapon.h"

USING_NS_CC;


Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // 3. add Weapon options bar
    initWeaponOptionsBar(origin, visibleSize);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = LabelTTF::create("Hello World", "Arial", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto background = Sprite::create("background.png");

    // position the sprite on the center of the screen
    background->setPosition(origin + visibleSize/2);

    
    _listener_touch = EventListenerTouchOneByOne::create();
    _listener_touch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan,this);
    _listener_touch->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

    
    // add the sprite as a child to this layer
    this->addChild(background, 0);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("role.plist","role.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animals.plist", "animals.pvr.ccz");
    //add player
    
    _player = Player::create(Player::PlayerType::PLAYER);
    _player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height*3);
    this->addChild(_player);
    
    //add enemy1
    _enemy1 = Player::create(Player::PlayerType::ENEMY1);
    _enemy1->setPosition(origin.x + visibleSize.width - _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height);
    this->addChild(_enemy1);
    
    
    
    //test animation
    //_player->playAnimationForever(1);
    _enemy1->playAnimationForever(1);
    
    return true;
}


//Right top Weapon option bar
void MainScene::initWeaponOptionsBar(Vec2 origin, Size visibleSize)
{
    // add a "close" icon to exit the progress. it's an autorelease object
    auto optionItem = MenuItemImage::create(
                                           "weapon1.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::activateWeaponOption, this));
    
	optionItem->setPosition(Vec2(origin.x + visibleSize.width - optionItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height - optionItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(optionItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void MainScene::activateWeaponOption(Ref* pSender)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapons.plist","weapons.pvr.ccz");
    
    //add weapon
    Weapon *weapon = Weapon::create(Weapon::WeaponType::COCONUT);
    Vec2 pos = _player->getPosition();
    weapon->setPosition(pos.x, pos.y);
    this->addChild(weapon);
    
    Vec2 radius(visibleSize.width/3, 0);
    Vec2 target(pos+radius);
    
    weapon->shootTo(target);
    
}


bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 pos = this->convertToNodeSpace(touch->getLocation());
    _player->walkTo(pos);
    log("MainScene::onTouchBegan");
    return true;
}

void MainScene::onTouchEnded(Touch* touch, Event* event)
{
    _player->stopAllActions();
    log("MainScene::onTouchend");
}

void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
