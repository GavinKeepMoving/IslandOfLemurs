#include "MainScene.h"
#include "Player.h"
#include "Animal.h"
#include "Enemy.h"
#include "Weapon.h"
#include "FSM.h"
//******************************************************************************************************************
//added by Wenbo Lin
#include "Progress.h"
#include <unistd.h>
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
    
    //Zhenni
    this->boundry = 550;

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
    _player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height*3);
    _player->background = _background;
    _player->background1 = _background1;
    _player->setScale(0.5);
    //_player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height*3);
    this->addChild(_player);
    _player->retain();
    
    /******************Begin-Added by Zhe Liu*****************************/
    //add enemy1
    _enemy1 = Enemy::create(Enemy::EnemyType::ENEMY1);
     _enemy1->setPosition(1600, origin.y + visibleSize.height * Enemy::height);
    _background->addChild(_enemy1);
    
//    _enemy2 = Enemy::create(Enemy::EnemyType::ENEMY2);
//    _enemy2->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height * Enemy::height);
     //_background->addChild(_enemy2);
    
//    _animal = Animal::create(Animal::AnimalType::ELEPHANT);
//    _animal->setPosition(1450, origin.y + visibleSize.height * Animal::height);
//    _background->addChild(_animal);
    /******************End-Added by Yafu*****************************/
    
    bananaManger = BananaManger::create(_background);
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
    this->schedule(schedule_selector(MainScene::addEnemy),20);
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
//            _animal->setFlippedX(true);
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
    int beginningPos = 900;
    int interval = 600;
    int treeNum = 2;
    
    //add treeBase
    treeBase = Sprite::create("image/trees/treeBase.png");
    treeBase->setPosition(580, 460);
    _background->addChild(treeBase);

    
    for(int i = 0; i < treeNum; i++) {
        //add ropes
        auto rope = Sprite::create("image/trees/rope.png");
        rope->setScale(0.3 + i * 0.2, 0.5);
        rope->cocos2d::Node::setPosition(beginningPos - 230 + i * 550, 520);
        _ropes.push_back(rope);
        _background->addChild(rope);
        
//        auto bareTree = Sprite::create("image/trees/bare_tree.png");
//        bareTree->setPosition(beginningPos + interval * i, 180);
//        _background->addChild(bareTree);
        
        auto treeSprite = Sprite::create("image/trees/tree.png");
        treeSprite->setPosition(beginningPos + interval * i, 430);
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
//        addEnemy(0.5);
        return;
    }
    std::cout<<"the size of enemy queue is: "<<_enemys.size()<<std::endl;
    for (auto enemy : _enemys)
    {
        if ("dead" != enemy->getState() && _player)
        {
            int type = -1;
            Vec2 dest = enemy->getBestAttackPosition(_player->getPosition(), _trees,_animals ,type);
            std::cout<<"the attack target of enemy i: "<<type<<std::endl;
            if (dest == enemy->getPosition()){
                if (type >= 0){
                    std::cout<<"the enemy is attacking "<<type<<std::endl;
                    enemy->attack();
                }
//                std::cout<<"the attack target of enemy is: "<<type<<std::endl;
                int animal_index  = -1;
                // control the blood volumn of the object it hitted
                if (type == 0){// lemur
                    
                }
                else if (type == 1){
                    int state = _trees.back()->setBlood(enemy->getAttack());
                    if (state <= 0){
                        /*
                        _trees.pop_back();
                        if(rope != NULL)
                            _background->removeChild(rope, true);
                         */
                        deleteTree();
                    }
                }
                else if (type >= 200){
                    animal_index = type%200;
//                    _animals[animal_index]->stop();
                    int state = _animals[animal_index]->beHit(enemy->getAttack());
                    std::cout<<"the enemy is attacking animal "<<animal_index<<std::endl;
                    if (state == 1){
                        log("this animal is dead, remove it~");
                        enemy->_canWalk = true;
                        _animals.erase(_animals.begin()+animal_index);
                        type = -1;
                        animal_index = -1;
                    }

                }
//                else{// type = -1
////                    enemy->walkTo(dest);
//                }
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
            std::cout<<"the target of animal is: "<<index<<std::endl;
            if (dest == animal->getPosition())
            {
                if (index != -1){
                    animal->attack();
                    std::cout<<"the hitting enemy is: "<<index<<std::endl;
                    _enemys[index]->stop();
                    // control the blood volumn of the bihitted animal
                    int state = _enemys[index]->beHit(animal->getAttack());
                    if (state == 1){
                        animal->_canWalk = true;
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

void MainScene::addEnemy(float dt)
{
    std::cout<<"time for enemy comming out~"<<std::endl;
    _enemy1 = Enemy::create(Enemy::EnemyType::ENEMY1);
    _enemy2 = Enemy::create(Enemy::EnemyType::ENEMY1);
    // origin.x
    //    _enemy1->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height * Enemy::height);
    _enemy1->setPosition(1600, origin.y + visibleSize.height * Enemy::height);
    _enemy2->setPosition(1600, origin.y + visibleSize.height * Enemy::height);
    _background->addChild(_enemy1);
    _background->addChild(_enemy2);
    _enemys.push_back(_enemy1);
    _enemys.push_back(_enemy2);
    _enemy1->addAttacker(_player);
    _enemy2->addAttacker(_player);

}
/****************** End-Added by Zhe Liu *********************/

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    this->touchPos = this->convertToNodeSpace(touch->getLocation());
    //TO-DO change 750 the integer to tree boundries or something
    
    _player->walkTo(this->touchPos, this->boundry);
    log("MainScene::onTouchBegan");
    return true;
}
//added by Zhenni
bool MainScene::isEnemyInRange(Player* p) {
    Rect playerRect=p->getAttackBox();
    for(int i=0; i<_enemys.size(); i++) {
        Vec2 enemyPos = _background->convertToWorldSpace(_enemys[i]->getPosition());
        if(playerRect.containsPoint(enemyPos)) {
            _player->targetEnemyIdx = i;
            return true;
        }
    }
    return false;
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

Vec2 MainScene::attackTarget(Player *p) {
    return _background->convertToWorldSpace(_enemys[0]->getPosition());
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

/*******************************Begin add by Wenbo Lin*******************************/
void MainScene::deleteTree() {
    Tree * target = _trees[_trees.size() - 1];
    Vec2 targetTreePos = _background->convertToWorldSpace(Vec2(target->_posX, 0));
    float xPos = targetTreePos.x;
    float yPos = targetTreePos.y;
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite * rope = _ropes[_ropes.size() - 1];
    float rangeLeft = 0;
    float rangeRight = 0;
    
    if(_trees.size() - 1 == 0) {
        rangeLeft = xPos - target->getContentSize().width / 2;
        rangeRight = xPos + target->getContentSize().width / 2;
        this->boundry = target->_posX - target->getContentSize().width*5/4 - visibleSize.width/2;
        _player->playerDrop(rangeLeft, rangeRight);
    }
    else {
        rangeLeft = xPos - target->getContentSize().width - rope->getContentSize().width;
        rangeRight = xPos + target->getContentSize().width / 2;
        this->boundry = target->_posX - target->getContentSize().width*5/4 - rope->getContentSize().width - visibleSize.width/2;
        std::function<void()> onWalk = CC_CALLBACK_0(Player::onWalk, _player, this->touchPos, this->boundry);
        _player->playerDrop(rangeLeft, rangeRight, onWalk);
    }
    
    _trees.pop_back();
    
    if(_trees.size() == 0) _background->removeChild(bananaManger, true);
    
    if(rope != NULL) {
        _background->removeChild(rope, true);
        _ropes.pop_back();
    }
}
/*******************************Ended add by Wenbo Lin*******************************/

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
