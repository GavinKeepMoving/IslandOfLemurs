#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "FSM.h"
//******************************************************************************************************************
//added by Wenbo Lin
#include "Progress.h"
//******************************************************************************************************************
#include "BananaManger.h"

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
    initAnimalOptionsBar();
    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    label = LabelTTF::create("Score: 0", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    //add background image
    log("create background");
    _background = Sprite::create("image/background.png");
    _background1 = Sprite::create("image/background.png");
    log("created background");

    // position the sprite on the center of the screen
    _background->setPosition(origin + visibleSize/2);
    _background1->setPosition(_background->getPosition() + Vec2(_background->getBoundingBox().size.width, 0));
    
    //********************************************************************************************************//
    //added by Wenbo Lin
    //add trees to background
    this->initTrees(2);
    _trees[0]->showAnimation(1, _background);
    //finish initializing trees
    //end of Wenbo Lin's code
    //********************************************************************************************************//
    //background->setPosition(origin + visibleSize/2);
    
    // add the sprite as a child to this layer
    //this->addChild(background, 0);

    
    _listener_touch = EventListenerTouchOneByOne::create();
    _listener_touch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan,this);
    _listener_touch->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);

    // add the sprite as a child to this layer
    this->addChild(_background, 0);
    this->addChild(_background1, 0);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("role.plist","role.pvr.ccz");
	
	//init blood progress
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
	//-------------------------------------//
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animals.plist", "animals.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapons.plist","weapons.pvr.ccz");
    //add player
    _player = Player::create(Player::PlayerType::PLAYER);
    _player->setPosition(visibleSize.width/2, origin.y + visibleSize.height*Player::height*3);
    _player->background = _background;
    _player->background1 = _background1;
    _player->setScale(0.5);
    //_player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height*3);
    this->addChild(_player);
    _player->retain();
    
    /******************Begin-Added by Yafu*****************************/
    //add enemy1
    _enemy1 = Enemy::create(Enemy::EnemyType::ENEMY1);
    _enemy1->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height * Enemy::height);
    _background->addChild(_enemy1);
    
    /******************End-Added by Yafu*****************************/
    
    BananaManger* bananaManger = BananaManger::create(_background);
    bananaManger->bindPlayer(_player);
    
    /****************** Begin-Added by Wenbo *********************/
    //Original Version
    //this->addChild(bananaManger,4);
    
    //Edit Version
    bananaManger->_background = _background;
    _background->addChild(bananaManger, 4);
    /****************** End-Added by Wenbo *********************/
    
    //test animation
    //_player->playAnimationForever(1);
    //_enemy1->playAnimationForever(1);
    //add blood progress
    addProgress();
	//--------------------//
    //auto fsm = FSM::create("idle",[](){cocos2d::log("Enter idle");});
    
    this->scheduleUpdate();
    return true;
}

void MainScene::addProgress()
{
	_progress = Progress::create("player-progress-bg.png","player-progress-fill.png");
	
	_progress->setPosition(origin.x + _progress->getContentSize().width/2, origin.y - _progress->getContentSize().height/2);
	this->addChild(_progress);
}

void MainScene::update(float delta)
{

    label->setString(CCString::createWithFormat("Score:%d",_player->getMoney())->getCString());

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

//Right top Weapon option bar
void MainScene::initAnimalOptionsBar()
{
    // add a "close" icon to exit the progress. it's an autorelease object
    auto optionItem = MenuItemImage::create(
                                            "animal1.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(MainScene::activateWeaponOption, this));
    
    optionItem->setPosition(Vec2(origin.x + optionItem->getContentSize().width/2,
                                 origin.y + optionItem->getContentSize().height/2));
    
    auto optionItem2 = MenuItemImage::create(
                                            "animal2.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(MainScene::activateWeaponOption, this));
    
    optionItem2->setPosition(Vec2(origin.x + optionItem->getContentSize().width/2 + optionItem->getContentSize().width,
                                 origin.y + optionItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(optionItem, NULL);
    menu->addChild(optionItem2);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void MainScene::activateWeaponOption(Ref* pSender)
{
    float radius = 250.;
    
    Weapon *weapon = this->_player->attack(radius, Weapon::WeaponType::WATER);
    
    _background->addChild(weapon);
    
    
        
}

void MainScene::spriteMoveFinished(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite);
    //enemyArray->removeObject(sprite);
}

void MainScene::initTrees(int num) {
    if(_background == NULL) return;
    int beginningPos = 700;
    int interval = 600;
    int treeNum = 2;
    for(int i = 0; i < treeNum; i++) {
        auto treeSprite = Sprite::create("image/trees/tree.png");
        treeSprite->setPosition(beginningPos + interval * i, 500);
        _background->addChild(treeSprite);
        _trees.push_back(new Tree(treeSprite));
    }
}


bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 pos = this->convertToNodeSpace(touch->getLocation());
    //TO-DO change 750 the integer to tree boundries or something
    _player->walkTo(pos, 250);
    log("MainScene::onTouchBegan");
    return true;
}

void MainScene::onTouchEnded(Touch* touch, Event* event)
{
    Vec2 pos = this->convertToNodeSpace(touch->getLocation());
    // added by Zhenni Huang
    _player->stop();
    //********************************************************************************
    //added by Wenbo Lin
    _background->stopAllActions();
    _background1->stopAllActions();
    //********************************************************************************
    /*if (_player->getPosition().y > origin.y + visibleSize.height*Player::height) {
        _player->climbDown(pos);
    }
    else
        _player->climbUp(pos);*/
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
