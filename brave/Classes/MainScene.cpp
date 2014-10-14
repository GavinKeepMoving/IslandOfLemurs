#include "MainScene.h"
#include "Player.h"
#include "Animal.h"
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
    int curBlood = _trees[0]->setBlood(1);
    //curBlood = _trees[0]->setBlood(1);
    //curBlood = _trees[0]->setBlood(1);
    //_background->removeChild(_trees[0]->treeSprite, true);
    //_trees[0]->showStateAccordingtoBlood();
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
	
    //Lishi Jiang
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/animal.plist", "image/animal.pvr.ccz");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
	//-------------------------------------//
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animals.plist", "animals.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/weapons/weapons.plist","image/weapons/weapons.pvr.ccz");

    

    
    //************************* Begin add by Wenbo Lin *****************************//
    //add fire animation
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/fire/fire.plist","image/fire/fire.pvr.ccz");
    //************************* End add by Wenbo Lin *****************************//
       
    //add player
    _player = Player::create(Player::PlayerType::PLAYER);
    _player->setPosition(visibleSize.width/2, origin.y + visibleSize.height*Player::height*3);
    _player->background = _background;
    _player->background1 = _background1;
    _player->setScale(0.5);
    //_player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height*3);
    this->addChild(_player);
    _player->retain();
    
    /******************Begin-Added by Zhe Liu*****************************/
    //add enemy1
    _enemy1 = Enemy::create(Enemy::EnemyType::ENEMY1);
     _enemy1->setPosition(1450, origin.y + visibleSize.height * Enemy::height);
    _background->addChild(_enemy1);
    
//    _enemy2 = Enemy::create(Enemy::EnemyType::ENEMY2);
//    _enemy2->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height * Enemy::height);
     //_background->addChild(_enemy2);
    
//    _animal = Animal::create(Animal::AnimalType::ELEPHANT);
//    _animal->setPosition(1450, origin.y + visibleSize.height * Animal::height);
//    _background->addChild(_animal);
    /******************End-Added by Yafu*****************************/
    
    BananaManger* bananaManger = BananaManger::create(_background);
    bananaManger->bindPlayer(_player);
    
    /****************** Begin-Added by Wenbo *********************/
    //Original Version
    //this->addChild(bananaManger,4);
    
    //Edit Version
    bananaManger->_background = _background;
    _background->addChild(bananaManger, 2);
    /****************** End-Added by Wenbo *********************/
    

    //add blood progress
    
    /****************** Begin-Added by Zhe Liu *********************/
    
    _enemys.push_back(_enemy1);
//    _enemys.pushBack(_enemy2);
    _enemy1->addAttacker(_player);
//    _enemy2->addAttacker(_player);
//    _animals.push_back(_animal);
    this->schedule(schedule_selector(MainScene::enemyMove), 3);
    this->schedule(schedule_selector(MainScene::animalMove), 3);
    /****************** End-Added by Zhe Liu *********************/
	
	//*****init blood progress  xiaojing **************//
    addProgress();
	
	
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
                                           "attackoption1.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::activateWeaponOption, this, 1));
    
	optionItem->setPosition(Vec2(origin.x + visibleSize.width - optionItem->getContentSize().width/2 - optionItem->getContentSize().width,
                                origin.y + visibleSize.height - optionItem->getContentSize().height/2));
    
    auto optionItem2 = MenuItemImage::create(
                                            "attackoption2.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(MainScene::activateWeaponOption, this, 2));
    
    optionItem2->setPosition(Vec2(origin.x + visibleSize.width - optionItem->getContentSize().width/2 ,
                                 origin.y + visibleSize.height - optionItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(optionItem, NULL);
    menu->addChild(optionItem2);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

//Right top Weapon option bar
void MainScene::initAnimalOptionsBar()
{
    // add a "close" icon to exit the progress. it's an autorelease object
    auto optionItem1 = MenuItemImage::create(
                                            "animal1.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(MainScene::callAnimalHelper, this, 1));
    
    optionItem1->setPosition(Vec2(origin.x + optionItem1->getContentSize().width/2,
                                 origin.y + optionItem1->getContentSize().height/2));
    
    auto optionItem2 = MenuItemImage::create(
                                            "animal2.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(MainScene::callAnimalHelper, this, 2));
    
    optionItem2->setPosition(Vec2(origin.x + optionItem1->getContentSize().width/2 + optionItem1->getContentSize().width,
                                 origin.y + optionItem1->getContentSize().height/2));
    
    auto optionItem3 = MenuItemImage::create(
                                             "animal3.png",
                                             "CloseSelected.png",
                                             CC_CALLBACK_1(MainScene::callAnimalHelper, this, 3));
    
    optionItem3->setPosition(Vec2(origin.x + optionItem1->getContentSize().width/2 + optionItem1->getContentSize().width*2,
                                  origin.y + optionItem1->getContentSize().height/2));
    
    auto optionItem4 = MenuItemImage::create(
                                             "animal4.png",
                                             "CloseSelected.png",
                                             CC_CALLBACK_1(MainScene::callAnimalHelper, this, 4));
    
    optionItem4->setPosition(Vec2(origin.x + optionItem1->getContentSize().width/2 + optionItem1->getContentSize().width*3,
                                  origin.y + optionItem1->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(optionItem1, NULL);
    menu->addChild(optionItem2);
    menu->addChild(optionItem3);
    menu->addChild(optionItem4);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void MainScene::activateWeaponOption(Ref* pSender, int index)
{
    switch (index) {
        case 1:
            this->_player->setWeapon(Weapon::WeaponType::COCONUT);
            break;
        case 2:
            this->_player->setWeapon(Weapon::WeaponType::WATER);
            break;
        default:
            break;
    }
    
    this->_player->attack();

}
// 1450, origin.y + visibleSize.height * Enemy::height
void MainScene::callAnimalHelper(Ref* pSender, int index) {
    switch (index) {
        case 1:
            _animal = Animal::create(Animal::AnimalType::ELEPHANT);
            _animal->setPosition(100, origin.y + visibleSize.height*Animal::height);
            _background->addChild(_animal);
            //add animals -------------------------------//
            _animals.push_back( _animal);
            break;
        case 2:
            _animal = Animal::create(Animal::AnimalType::CLOTHE);
            _animal->setPosition(100, origin.y + visibleSize.height*Animal::height);
            _background->addChild(_animal);
            //add animals -------------------------------//
            _animals.push_back( _animal);
            break;
        case 3:
            _animal = Animal::create(Animal::AnimalType::TIGER);
            _animal->setPosition(100, origin.y + visibleSize.height*Animal::height);
            _background->addChild(_animal);
            //add animals -------------------------------//
            _animals.push_back( _animal);
            break;
        case 4:
            _animal = Animal::create(Animal::AnimalType::FOX);
            _animal->setPosition(100, origin.y + visibleSize.height*Animal::height);
            _background->addChild(_animal);
            //add animals -------------------------------//
            _animals.push_back( _animal);
            break;
        default:
            break;
    }

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
    int interval = 800;
    int treeNum = 2;
    
    //add rope
    auto rope = Sprite::create("image/trees/rope.png");
    rope->setScale(0.7, 0.5);
    rope->cocos2d::Node::setPosition(beginningPos + 370, 520);
    _background->addChild(rope);
    
    for(int i = 0; i < treeNum; i++) {
        auto treeSprite = Sprite::create("image/trees/tree.png");
        treeSprite->setPosition(beginningPos + interval * i, 450);
        _background->addChild(treeSprite);
        _trees.push_back(new Tree(treeSprite));
        _trees[_trees.size() - 1]->_background = _background;
    }
}

/****************** Begin-Added by Zhe Liu *********************/
// enemy move
void MainScene::enemyMove(float dt)
{
    if (_enemys.size() == 0){
        std::cout<<"no enemy right now, please wait"<<std::endl;
        addEnemy();
        return;
    }
    for (auto enemy : _enemys)
    {
        if ("dead" != enemy->getState() && _player)
        {
            int type = -1;
            Vec2 dest = enemy->getBestAttackPosition(_player->getPosition(), _trees,_animals ,type);
            std::cout<<"current type is: "<<type<<std::endl;
            if (dest == enemy->getPosition()){
                enemy->attack();
                std::cout<<"the attack target of enemy is: "<<type<<std::endl;
                // control the blood volumn of the object it hitted
                if (type == 0){// lemur
                    
                }
                else if (type == 1){
                    
                }
                else if (type >= 200){
                    int animal_index = type%200;
                    _animals[animal_index]->beHit(enemy->getAttack());
                }
                else{
                    
                }
            }
            else{
                enemy->walkTo(dest);
            }
        }
    }
    
}

void MainScene::animalMove(float dt)
{
    if (_enemys.size() == 0){
        for (auto animal : _animals)
            animal->stop();
    }
    for (auto animal : _animals)
    {
        if ("dead" != animal->getState() && _player)
        {
            int index = -1;
            Vec2 dest = animal->getBestAttackPosition(_enemys, index);
            if (dest == animal->getPosition())
            {
                if (index != -1){
                    animal->attack();
                    // control the blood volumn of the bihitted animal
                    int state = _enemys[index]->beHit(animal->getAttack());
                    if (state == 1){
                        log("this enemy is dead, remove it~");
                        _enemys.erase(_enemys.begin()+index);
                        index = -1;
                    }
                }
            }
            else
            {
                animal->walkTo(dest);
            }
        }
    }
}

void MainScene::addEnemy()
{
    _enemy1 = Enemy::create(Enemy::EnemyType::ENEMY1);
    // origin.x
    //    _enemy1->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height * Enemy::height);
    _enemy1->setPosition(1450, origin.y + visibleSize.height * Enemy::height);
    _background->addChild(_enemy1);
    _enemys.push_back(_enemy1);
    _enemy1->addAttacker(_player);

}
/****************** End-Added by Zhe Liu *********************/

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 pos = this->convertToNodeSpace(touch->getLocation());
    //TO-DO change 750 the integer to tree boundries or something
    _player->walkTo(pos, 550);
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
//------------------remove dead enemy--------------------------------------------------------------//
//void MainScene::enemyDead(Ref* obj)
//{
//	auto enemy= (Enemy*)obj;
//	_enemys.eraseObject(enemy,true);
//	log("onEnemyDead:%d", _enemys.size());
//	//if(_enemys.size() == 0) //show success or go to next level
//}

//void MainScene::animalDead(Ref* obj)
//{
//	auto animal= (Animal*)obj;
//	_animals.eraseObject(animal,true);		
//}



//----------------------------------------------------------------------------------//
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
