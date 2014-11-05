//
//  StartScene.cpp
//  brave
//
//  Created by Yafu Li on 10/26/14.
//
//

#include "StartScene.h"
#include "MapScene.h"

#include "MainScene.h"
#include "VisibleRect.h"
#include "CustomTool.h"

/******************Start-Modified by Yafu****************************/
MainScene *mainLayer;
/******************End-Modified by Yafu*****************************/

bool StartScene::init()
{
    if(!Layer::init())
        return false;
    log("StartLayer::init");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist","image/role.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/iui.plist","image/iui.png");
    auto background = Sprite::create("image/MainMenuBG.png");
    background->setPosition(VisibleRect::center());
    this->addChild(background);
//    
//    auto menuBG = Sprite::create("MainMenu.png");
//    menuBG->setPosition(VisibleRect::center());
//    this->addChild(menuBG);
    
    auto item = CustomTool::createMenuItemImage("play.png", "play.png", CC_CALLBACK_1(StartScene::onStart,this));
    auto menu = Menu::createWithItem(item);
    this->addChild(menu);
    return true;
}


Scene* StartScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}


void StartScene::onStart(Ref* obj)
{
    log("StartLayer::onStart");
    /******************Start-Modified by Yafu****************************/
    auto scene = MapScene::createScene();
    
    /******************End-Modified by Yafu*****************************/
    
    Director::getInstance()->replaceScene(scene);
}

