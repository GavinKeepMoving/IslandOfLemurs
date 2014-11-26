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
#include "CustomTool.h"
#include "LoseScene.h"
//******************************************************************************************************************
#include "SkillButton.h"


USING_NS_CC;

extern int globalLevel;


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

    gamelevel = globalLevel;
    
    level = 0;
    
    this->playMusic();
    
    this->setParameters();

    this->addCloseIcon();

    this->addHelloWorldLabel();
    
    this->addBackground();
    
    this->addRoles();
    
    this->addWeaponOptionBar();
    this->addEnemyNumber();
    
    this->setScheduleAndProgress();
    
    //this->addgotoItem();//or combine with menu create??
    return true;
}

void MainScene::setLevel(int l) {
    gamelevel = l;
}

void MainScene::addProgress()
{
	_progress = Progress::create("player-progress-bg.png","player-progress-fill.png");
	
	_progress->setPosition(origin.x + _progress->getContentSize().width/2, origin.y - _progress->getContentSize().height/2);
	this->addChild(_progress);
}


void MainScene::addgotoItem()
{
      this->addChild(_menu, 1);
    /***************goto next level menu**************************/
	
	auto gotoItem =  CustomTool::createMenuItemImage("go.png", "go.png", 
													CC_CALLBACK_1(MainScene::gotoNextLevel,this));
	gotoItem->setVisible(false);
	gotoItem->setTag(2);
	//VisibleRect::right().x - goItem->getContentSize().width/2, VisibleRect::center().y
	//just try position
	gotoItem->setPosition(Vec2(origin.x + visibleSize.width - gotoItem->getContentSize().width/2, origin.y + visibleSize.height * 0.5 + gotoItem->getContentSize().height/2));
    
    // create menu, 
    auto menu = Menu::create(gotoItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

bool MainScene::enemyAllDead()
{
	
	log("all EnemyDead:%lu", _enemy2Arr.size());
	if(_enemy2Arr.size() == 0) return true;
	else return false;
}

void MainScene::gotoNextLevel(Ref* obj)
{
	//need enable goItem in menu
	auto goItem = this->_menu->getChildByTag(2);
	goItem->setVisible(false);
	goItem->stopAllActions();

	//enemy manager add new enemy to background
		
	/*
	

	*/		
}


void MainScene::showNextLevelItem() //called by enemy manager???
{
	if(enemyAllDead() && level == dispatch.size()){//of  check by enemy manager????
		auto goItem = this->_menu->getChildByTag(2);
		goItem->setVisible(true);
		goItem->runAction(RepeatForever::create(Blink::create(1,1)));
		gamelevel = gamelevel+1;  //need add different number of enemy when enemy manager create enemy
        level = 0;
        addEnemyNumber();
	}
}
/*****************************************************/
void MainScene::update(float delta)
{
    /*Point oldPos = _enemy1->getPosition();
    if (_enemy1->getState() == "walking")
    {
        _enemy1->setPosition(oldPos.x -1,oldPos.y);
    }*/
//    if (_enemy2Arr == NULL){
//        _enemy2Arr = __Array::create();
//    }
//    if (_aniaml2Arr == NULL){
//        _aniaml2Arr = __Array::create();
//    }
//    _enemy2Manager->update(delta);
//    _animal2Manager->update(delta);
    this->updateAnimal(delta);
    this->updateEnemy(delta);
    //_enemy2->update(delta);
    a_optionItem1->setEnabled(_player->getMoney() >= 20 ? true : false);
    a_optionItem2->setEnabled(_player->getMoney() >= 40 ? true : false);
    a_optionItem3->setEnabled(_player->getMoney() >= 40 ? true : false);
    a_optionItem4->setEnabled(_player->getMoney() >= 60 ? true : false);
    label->setString(CCString::createWithFormat("%d",_player->getMoney())->getCString());

}

//Right top Weapon option bar
void MainScene::initWeaponOptionsBar(Vec2 origin, Size visibleSize)
{
    _weaponManager = WeaponManager::create(_background);
    _weaponManager->bindPlayer(_player);
    

    SkillButton* mSkillButton = SkillButton::createSkillButton(10.f, "weapon1grey.png", "weapon1.png", "weapon1grey.png", 1);
    mSkillButton->_player = _player;
    mSkillButton->setPosition(Vec2(visibleSize.width-260, visibleSize.height-32));
    addChild(mSkillButton,1);
    mSkillButton = SkillButton::createSkillButton(25.f, "weapon3grey.png", "weapon3.png", "weapon3grey.png", 2);
    mSkillButton->_player = _player;
    mSkillButton->_weaponManager = _weaponManager;
    mSkillButton->_trees = _trees;
    mSkillButton->setPosition(Vec2(visibleSize.width-155, visibleSize.height-32));
    addChild(mSkillButton,1);
    mSkillButton = SkillButton::createSkillButton(60.f, "weapon2grey.png", "weapon2.png", "weapon2grey.png", 3);
    mSkillButton->_player = _player;
    mSkillButton->bananaManger = bananaManger;
    mSkillButton->setPosition(Vec2(visibleSize.width-50, visibleSize.height-32));
    addChild(mSkillButton,1);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto optionItem = MenuItemImage::create(
                                           "weapon1.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::activateWeaponOption, this, 1));
    
	optionItem->setPosition(Vec2(origin.x + visibleSize.width - optionItem->getContentSize().width*3 + optionItem->getContentSize().width/2-6,
                                origin.y + visibleSize.height - optionItem->getContentSize().height/2));
    
    auto optionItem2 = MenuItemImage::create(
                                            "weapon3.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(MainScene::activateWeaponOption, this, 2));
    
    optionItem2->setPosition(Vec2(origin.x + visibleSize.width - optionItem->getContentSize().width*2 + optionItem->getContentSize().width/2-3,
                                 origin.y + visibleSize.height - optionItem->getContentSize().height/2));
    
    auto optionItem3 = MenuItemImage::create(
                                             "weapon2.png",
                                             "CloseSelected.png",
                                             CC_CALLBACK_1(MainScene::activateWeaponOption, this, 3));
    
    optionItem3->setPosition(Vec2(origin.x + visibleSize.width - optionItem->getContentSize().width + optionItem->getContentSize().width/2,
                                  origin.y + visibleSize.height - optionItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(optionItem, NULL);
    menu->addChild(optionItem2);
    menu->addChild(optionItem3);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/
}

//Right top Weapon option bar
void MainScene::initAnimalOptionsBar()
{
    // add a "close" icon to exit the progress. it's an autorelease object
    a_optionItem1 = MenuItemImage::create(
                                            "money.png",
                                            "back.png","moneygrey.png",
                                            CC_CALLBACK_1(MainScene::callAnimalHelper, this, 1));
    
    a_optionItem1->setPosition(Vec2(origin.x + a_optionItem1->getContentSize().width/2,
                                 origin.y + a_optionItem1->getContentSize().height/2));
    
    a_optionItem2 = MenuItemImage::create(
                                            "tiger2.png",
                                            "back.png","tiger2grey.png",
                                            CC_CALLBACK_1(MainScene::callAnimalHelper, this, 2));
    
    a_optionItem2->setPosition(Vec2(origin.x + a_optionItem1->getContentSize().width/2 + a_optionItem1->getContentSize().width+1,
                                 origin.y + a_optionItem1->getContentSize().height/2));
    
    a_optionItem3 = MenuItemImage::create(
                                             "panda.png",
                                             "back.png","pandagrey.png",
                                             CC_CALLBACK_1(MainScene::callAnimalHelper, this, 3));
    
    a_optionItem3->setPosition(Vec2(origin.x + a_optionItem1->getContentSize().width/2 + a_optionItem1->getContentSize().width*2+2,
                                  origin.y + a_optionItem1->getContentSize().height/2));
    
    a_optionItem4 = MenuItemImage::create(
                                             "cloth.png",
                                             "back.png","clothgrey.png",
                                             CC_CALLBACK_1(MainScene::callAnimalHelper, this, 4));
    
    a_optionItem4->setPosition(Vec2(origin.x + a_optionItem1->getContentSize().width/2 + a_optionItem1->getContentSize().width*3+3,
                                  origin.y + a_optionItem1->getContentSize().height/2));
    // create menu, it's an autorelease object
    a_optionItem1->setEnabled(false);
    a_optionItem2->setEnabled(false);
    a_optionItem3->setEnabled(false);
    a_optionItem4->setEnabled(false);
    auto menu = Menu::create(a_optionItem1, NULL);
    menu->addChild(a_optionItem2);
    menu->addChild(a_optionItem3);
    menu->addChild(a_optionItem4);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    //return menu;
}

void MainScene::activateWeaponOption(Ref* pSender, int index)
{

    //put out fire
    if (index == 2) {
        this->_player->setWeapon(Weapon::WeaponType::WATER);
        Tree* t = _weaponManager->getNearestTree(_trees);
        
        if (t) {            
            this->_player->attack(_weaponManager->getAttackRadius(t));
            t->setBlood(-100.);
        }
        this->_player->setWeapon(Weapon::WeaponType::COCONUT);
    }
    //get all the banana
    if (index == 3) {
        CCObject* obj=NULL;
        Banana* banana=NULL;
        CCARRAY_FOREACH(bananaManger->_bananaArr,obj)/*循环遍历怪物数组，重复出现在屏幕上*/
        {
            banana=(Banana*) obj;
            if(banana->isAlive())/*活动状态*/
            {
                _player->money += Banana::value;
                banana->hide();
                float time = 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3));
                banana->timeshow(time);
            }
        }
    }
    

}
// 1450, origin.y + visibleSize.height * Enemy::height
void MainScene::callAnimalHelper(Ref* pSender, int index) {
    Animal2* animal;
    switch (index) {
        case 1:
            if (_player->money < 20) {
                break;
            }
            _player->money-=20;
            animal = this->_animal2Manager->createAnimal2s(0);
            _animal2Arr.push_back(animal);
            break;
        case 2:
            if (_player->money < 40) {
                break;
            }
            _player->money-=40;
            animal = this->_animal2Manager->createAnimal2s(1);
            _animal2Arr.push_back(animal);
            break;
        case 3:
            if (_player->money < 40) {
                break;
            }
            _player->money-=40;
            animal = this->_animal2Manager->createAnimal2s(2);
            _animal2Arr.push_back(animal);
            break;
        case 4:
            if (_player->money < 60) {
                break;
            }
            _player->money-=60;
            animal = this->_animal2Manager->createAnimal2s(3);
            _animal2Arr.push_back(animal);
            break;
        default:
            break;
    }

}

void MainScene::spriteMoveFinished(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    this->removeChild(sprite);
}

void MainScene::initTrees(int num) {
    if(_background == NULL) return;
    int beginningPos = 400;
    int interval = 560;
    int treeNum = num;
    
    //add treeBase
    treeBase = Sprite::create("image/trees/treeBase.png");
    treeBase->cocos2d::Node::setAnchorPoint(ccp(0, 0));
    treeBase->setPosition(0, 100);
    _background->addChild(treeBase);

    
    for(int i = 0; i < treeNum; i++) {
        //add ropes
        auto rope = Sprite::create("image/trees/rope.png");
        rope->cocos2d::Node::setAnchorPoint(ccp(0, 0));
        if(_ropes.size() == 0) {
            rope->setScale(0.35, 0.5);
            rope->cocos2d::Node::setPosition(200, 360);
        }
        else if(_ropes.size() == 1) {
            rope->setScale(0.43, 0.5);
            rope->cocos2d::Node::setPosition(710, 360);
        }
        else {
            rope->setScale(0.43, 0.5);
            rope->cocos2d::Node::setPosition(710 + (i - 1) * interval, 360);
        }
        
        _ropes.push_back(rope);
        _background->addChild(rope);
        
//        auto bareTree = Sprite::create("image/trees/bare_tree.png");
//        bareTree->setPosition(beginningPos + interval * i, 180);
//        _background->addChild(bareTree);
        
        auto treeSprite = Sprite::create("image/trees/tree.png");
        treeSprite->setAnchorPoint(ccp(0, 0));
        treeSprite->setPosition(beginningPos + interval * i, 50);
        
        std::cout<<"tree width: "<<treeSprite->getContentSize().width;
        
        _background->addChild(treeSprite);
        _trees.push_back(new Tree(treeSprite,bananaManger,_background));
        _trees[_trees.size() - 1]->_background = _background;
    }
}

/****************** Begin-Added by Zhe Liu *********************/

void MainScene::updateAnimal(float dt)
{
    for (int i=0;i<_animal2Arr.size();i++)
    {
        int index = _animal2Manager->judgeNeayBy(_animal2Arr[i],_enemy2Arr);
        if (index == -1){
            _animal2Arr[i]->setState(Animal2::WALK);
        }
        else{
            if (_enemy2Arr[index]->getPositionX()-_animal2Arr[i]->getPositionX() > _animal2Arr[i]->mindist){
                _animal2Arr[i]->setState(Animal2::WALK);
            }
            else{
                _animal2Arr[i]->setState(Animal2::ATTACK);
                _enemy2Arr[index]->setState(BEHIT);
                int state = _enemy2Arr[index]->behit(_animal2Arr[i]->getAttack());
                if (state == 1){// enemy is dead, remove it
                    eraseEnemy(index);
                    index = -1;
                }
            }
        }
        _animal2Arr[i]->update(dt);
    }

}
//Zhenni
void MainScene::eraseEnemy(int index) {
    MainScene::removeChild(_enemy2Arr[index]);
    _enemy2Arr[index]->removeFromParentAndCleanup(true);
    _enemy2Arr[index]->setState(DEAD);
    _enemy2Arr.erase(_enemy2Arr.begin()+index);
}
void MainScene::eraseAnimal(int index){
    _animal2Arr[index]->removeFromParentAndCleanup(true);
    _animal2Arr[index]->setState(Animal2::DEAD);
    _animal2Arr.erase(_animal2Arr.begin()+index);
}

void MainScene::updateEnemy(float dt)
{
    for (int i=0;i<_enemy2Arr.size();i++)
    {
//        Vec2 enemyPos = _background->convertToWorldSpace(_enemy2Arr[i]->getPosition());
        Vec2 playerPos = _background->convertToNodeSpace(_player->getPosition());
//        std::cout<<"lemur's posistion is: "<<playerPos.x<<","<<playerPos.y<<std::endl;
//        std::cout<<"enemy's position is: "<<_enemy2Arr[i]->getPositionX()<<","<<_enemy2Arr[i]->getPositionY()<<std::endl;
        int index = _enemy2Manager->judgeNearby(playerPos,_enemy2Arr[i],_trees,_animal2Arr);
        //std::cout<<"current target is: "<<index<<std::endl;
        if (index == -1){
            _enemy2Arr[i]->setState(WALK);
        }
        else{
            if (index == 0){ // lemur
                if (_enemy2Arr[i]->getPositionX()-playerPos.x<= _enemy2Arr[i]->mindist &&playerPos.y == 100)
                {
                    _enemy2Arr[i]->setState(ATTACK);
                    int status = _player->beHit(_enemy2Arr[i]->getAttack());
                    // behit for the lemur
                    if (status == 1){// lemur is dead
                        // game over!!
                        _player->removeFromParentAndCleanup(true);
                        
                        //add by wenbo lin
                        this->cocos2d::Node::pause();
                        LoseScene loseScene;
                        loseScene.createScene(this);
                        //end of add by wenbo lin
                        
                        index = -1;
                    }
                }
                else{
                    _enemy2Arr[i]->setState(WALK);
                }
            }
            else if (index == 1){ // tree
                if (_enemy2Arr[i]->getPositionX()-_trees.back()->getRightBoundary() < _enemy2Arr[i]->mindist){
                    _enemy2Arr[i]->setState(ATTACK);
                    int state = _trees.back()->setBlood(_enemy2Arr[i]->getAttack());
                    if (state <= 0){
                        deleteTree();
                        index = -1;
                    }
                }
                else{
                    _enemy2Arr[i]->setState(WALK);
                }
            }
            else if (index >= 200){ // animal
                int target = index%200;
                if (_enemy2Arr[i]->getPositionX()-_animal2Arr[target]->getPositionX() <= _enemy2Arr[i]->mindist){
                    _enemy2Arr[i]->setState(ATTACK);
                    int state = _animal2Arr[target]->beHit(_enemy2Arr[i]->getAttack());
                    if (state == 1){
                        eraseAnimal(target);
                        index = -1;
                    }
                }
                else{
                    _enemy2Arr[i]->setState(WALK);
                }
            }
        }
        _enemy2Arr[i]->update(dt);
    }
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
    _player->targetEnemy = NULL;
    float distance = INT_MAX;
    Rect playerRect=p->getAttackBox();
    int i;
    for (i=0;i<_enemy2Arr.size();i++)
    {
        Vec2 enemyPos = _background->convertToWorldSpace(_enemy2Arr[i]->getPosition());
        if(playerRect.containsPoint(enemyPos)) {
            float _distance = (enemyPos - _player->getPosition()).getLength();
            if( _distance < distance ) {
                _player->targetEnemy = _enemy2Arr[i];
                _player->targetEnemyIndex = i;
            }
        }
    }
    return _player->targetEnemy == NULL ? false : true;
}

//aoe attack enemy //by Zhenni
void MainScene::aoeAttack(int attack, int range, int x) {
    auto attackRect = Rect(x - range/2 , 0, range, visibleSize.height);
    for (int i=0;i<_enemy2Arr.size();i++)
    {
        if(attackRect.containsPoint(_enemy2Arr[i]->getPosition())) {
            if(_enemy2Arr[i]->behit(attack) == 1) {
                this->eraseEnemy(i);
            }
        }
    }
}

void MainScene::stoneFall(int x){
    ParticleSystem *system = ParticleSystemQuad::create("aoe.plist");
    system->setPosition(Vec2(x, visibleSize.height));
    system->setDuration(3.0);
    system->setAutoRemoveOnFinish(true);
    this->_background->addChild(system);
    
}



void MainScene::onTouchEnded(Touch* touch, Event* event)
{
    Vec2 pos = this->convertToNodeSpace(touch->getLocation());
    // added by Zhenni Huang
    _player->stop();
    //********************************************************************************
    //added by Wenbo Lin
    //_background->stopAllActions();
    //_background1->stopAllActions(); // commented by Zhenni
    //********************************************************************************
    /*if (_player->getPosition().y > origin.y + visibleSize.height*Player::height) {
        _player->climbDown(pos);
    }
    else
        _player->climbUp(pos);*/
    log("MainScene::onTouchend");
}

Vec2 MainScene::attackTarget(Player *p) {
    return _background->convertToWorldSpace(_player->targetEnemy->getPosition());
}

/*******************************Begin add by Wenbo Lin*******************************/
void MainScene::deleteTree() {
    Tree * targetTree = _trees[_trees.size() - 1];
    Vec2 targetTreePos = _background->convertToWorldSpace(Vec2(targetTree->_posX, 0));
    float xPos = targetTreePos.x;
    int treeWidth = 446;
    
    Sprite * rope = _ropes[_ropes.size() - 1];
    float rangeLeft = 0;
    float rangeRight = 0;
    
    rangeLeft = xPos - rope->getContentSize().width * 0.4;
    rangeRight = xPos + treeWidth;
    //this->boundry = target->_posX - target->getContentSize().width*5/4 - rope->getContentSize().width - visibleSize.width/2;
    std::function<void()> onWalk = CC_CALLBACK_0(Player::onWalk, _player, this->touchPos, this->boundry);
    _player->playerDrop(rangeLeft, rangeRight, onWalk);
    
    _trees.pop_back();
    //Zhenni
    updateBoundry();

    //add sound
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("AudioClip/TreeFall.wav");
    
    if(_trees.size() == 0) _background->removeChild(bananaManger, true);
    
    if(rope != NULL) {
        _background->removeChild(rope, true);
        _ropes.pop_back();
    }
    
    /** show lose scene */
    if(_trees.size() == 0) {
        this->cocos2d::Node::pause();
        LoseScene loseScene;
        loseScene.createScene(this);
    }
}
/*******************************Ended add by Wenbo Lin*******************************/

/*******************************Begin add by Wenbo Lin*******************************/
void MainScene::playMusic() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("AudioClip/Willow_and_the_Light.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("AudioClip/Willow_and_the_Light.mp3", true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
}

void MainScene::setParameters()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void MainScene::addCloseIcon()
{
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
}

void MainScene::addWeaponOptionBar()
{
    // 3. add Weapon options bar
    initWeaponOptionsBar(origin, visibleSize);
    initAnimalOptionsBar();
}

void MainScene::addHelloWorldLabel()
{

    auto banana = Sprite::create("banana.png");
    banana->setPosition(Vec2(origin.x + 430 + banana->getContentSize().width/2, origin.y +banana->getContentSize().height/2));
    this->addChild(banana,1);
    
    
    label = LabelTTF::create("0", "HiraKakuProN-W6", 36);
    label->setPosition(Vec2(origin.x + 450 + banana->getContentSize().width/2, origin.y +banana->getContentSize().height/2));
    this->addChild(label, 2);
}

void MainScene::addBackground()
{
    //add background image
    log("create background");
    _background = Sprite::create("image/background.png");
    //_background1 = Sprite::create("image/background.png");
    log("created background");
    
    // position the sprite on the center of the screen
    _background->setAnchorPoint(ccp(0,0));
    _background->setPosition(0,0);
    //_background1->setPosition(_background->getPosition() + Vec2(_background->getBoundingBox().size.width, 0));
    // add the sprite as a child to this layer
    this->addChild(_background, 0);
    //this->addChild(_background1, 0);
}

void MainScene::addRoles()
{
    
    this->addAnimations();
    this->addFires();
    this->addPlayer();
    this->addEnemies();
    this->addBananas();
    this->addTrees();
}

//method in addRoles

void MainScene::addTrees()
{
    int baseNum = 1;
    //int level = 1;
    int delta = 2;
    int upperLimit = 4;
    //********************************************************************************************************//
    //added by Wenbo Lin
    
    //add trees to background
    int treeNum = baseNum + gamelevel;
    if(treeNum <= upperLimit)
        this->initTrees(treeNum);
    else
        this->initTrees(upperLimit);
    //finish initializing trees
    //end of Wenbo Lin's code
    //********************************************************************************************************//
    //Zhenni
    updateBoundry();
    
}

void MainScene::updateBoundry() {
    if (this->_trees.empty() ) {
        this->boundry = 0;
    }
    else {
        this->boundry = this->_trees[this->_trees.size()-1]->getRightBoundary();
    }
}


void MainScene::addAnimations()
{
    _listener_touch = EventListenerTouchOneByOne::create();
    _listener_touch->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan,this);
    _listener_touch->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener_touch, this);
    
    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("role.plist","role.pvr.ccz");
    
    //Lishi Jiang
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/animal.plist", "image/animal.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
    //-------------------------------------//
    ArmatureDataManager::getInstance()->addArmatureFileInfo("animal0.png" , "animal0.plist" , "animal.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("monkey20.png" , "monkey20.plist" , "monkey2.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("tiger20.png" , "tiger20.plist" , "tiger2.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("pada20.png" , "pada20.plist" , "pada2.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("p10.png" , "p10.plist" , "p1.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("remoteen10.png", "remoteen10.plist","remoteen1.ExportJson");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animals.plist", "animals.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/weapons/weapons.plist","image/weapons/weapons.pvr.ccz");
    

}

void MainScene::addFires()
{
    //************************* Begin add by Wenbo Lin *****************************//
    //add fire animation
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/fire/fire.plist","image/fire/fire.pvr.ccz");
    //************************* End add by Wenbo Lin *****************************//
}

void MainScene::addPlayer()
{
    //add player
    _player = Player::create(Player::PlayerType::PLAYER);
    _player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height*3);
    _player->background = _background;
    _player->background1 = _background1;
    _player->setScale(0.5);
    //_player->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height*3);
    this->addChild(_player);
    _player->retain();
}

void MainScene::addEnemies()
{
    /******************Begin-Added by Zhe Liu*****************************/
    //add enemy1
    
    
    
    
    _enemy2Manager = Enemy2Manager::create(_background);
    _enemy2Manager->_background = _background;
    _background->addChild(_enemy2Manager, 2);
    
    _animal2Manager = Animal2Manager::create(_background);
    _animal2Manager->_background = _background;
    _background->addChild(_animal2Manager, 2);

//    _enemy2Manager->setTrees(_trees);
//    _enemy2Arr = __Array::create();
//    Enemy2* enemy1 = _enemy2Manager->createEnemy2s();
//    _enemy2Arr.push_back(enemy1);
//    _enemy2Arr = __Array::create();
//    _enemy2Arr->retain();
//    _enemy2Arr->addObject(enemy1);
    //_enemy2 = new Enemy2();
    //_enemy2->setPosition(850, 430);
    //_enemy2->setPosition(origin.x + _player->getContentSize().width/2, origin.y + visibleSize.height*Player::height);
    //_background->addChild(_enemy2);
    
    
    
    
    
    //_enemy1 = Enemy::create(Enemy::EnemyType::ENEMY1);
    // _enemy1->setPosition(1600, origin.y + visibleSize.height * Enemy::height);
    //_background->addChild(_enemy1);
    
    
    
    
    //    _enemy2 = Enemy::create(Enemy::EnemyType::ENEMY2);
    //    _enemy2->setPosition(origin.x + visibleSize.width - _enemy1->getContentSize().width/2, origin.y + visibleSize.height * Enemy::height);
    //_background->addChild(_enemy2);
    
    //    _animal = Animal::create(Animal::AnimalType::ELEPHANT);
    //    _animal->setPosition(1450, origin.y + visibleSize.height * Animal::height);
    //    _background->addChild(_animal);
    /******************End-Added by Yafu*****************************/
}

void MainScene::addEnemiesAI(float dt)
{
    int i;
    Enemy2* enemy;
//    std::cout<<_player->getPositionX()<<","<<_player->getPositionY()<<std::endl;
    int dist = 100;
    int enemy1 = enemycategory[level];
    std::cout<<"current enemy 0 is: "<<enemy1<<std::endl;
    std::cout<<"dispatch size is: "<<dispatch[level]<<std::endl;
    if (level < dispatch.size()){
        for (i=0;i<dispatch[level];i++){
            if (enemy1 > 0){
                enemy = _enemy2Manager->createEnemy2s(2*dist,0,gamelevel);
                enemy1--;
            }
            else{
                enemy = _enemy2Manager->createEnemy2s(2*dist,1,gamelevel);
            }
            _enemy2Arr.push_back(enemy);
            dist += 50;
        }
        level++;
        std::cout<<"the size of enemy is: "<<_enemy2Arr.size()<<std::endl;
    }
    else{
        // the game ends
    }
}

void MainScene::addEnemyNumber()
{
    // assign enemys with gamelevel
    switch (gamelevel){
        case 1:
            dispatch = {2,3,3};
            enemydelay = {10,40,40};
            enemycategory = {1,1,2};
            break;
        case 2:
            dispatch = {2,3,4,3};
            enemydelay = {10,40,40,40};
            enemycategory = {1,2,2,2};
            break;
        case 3:
            dispatch = {2,3,4,3,3};
            enemydelay = {10,10,10,10,10};
            enemycategory = {2,1,3,2,2};
            break;
        case 4:
            dispatch = {2,3,4,4,4,5};
            enemydelay = {10,10,10,10,10,10};
            enemycategory = {2,2,2,2,2,3};
            break;
        default:
            break;
    }

}

void MainScene::addBananas()
{
    bananaManger = BananaManger::create(_background);
    bananaManger->bindPlayer(_player);
    
    /****************** Begin-Added by Wenbo *********************/
    //Original Version
    //this->addChild(bananaManger,4);
    
    //Edit Version
    bananaManger->_background = _background;
    _background->addChild(bananaManger, 2);
    /****************** End-Added by Wenbo *********************/
}
//end of method in addRoles

void MainScene::setScheduleAndProgress()
{
    //add blood progress
    
    /****************** Begin-Added by Zhe Liu *********************/
    
    if (level < dispatch.size()){
        this->schedule(schedule_selector(MainScene::addEnemiesAI),enemydelay[level]);
    }
    /****************** End-Added by Zhe Liu *********************/
    
    //*****init blood progress  xiaojing **************//
    addProgress();
    
    
    this->scheduleUpdate();
}
/*******************************Ended add by Wenbo Lin*******************************/

//----------------------------------------------------------------------------------//
void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    if(!pause) {
        this->cocos2d::Node::pause();
        pause = true;
    }
    else {
        this->resume();
        pause = false;
    }
    //Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}
