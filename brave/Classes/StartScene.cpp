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
#include "WinScene.h"
#include "LoseScene.h"

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
    auto background = Sprite::create("image/MainMenuBG.png");
    background->setPosition(VisibleRect::center());
    this->addChild(background);
    
    auto item = CustomTool::createMenuItemImage("start1.png", "start2.png", CC_CALLBACK_1(StartScene::onStart,this));
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
    auto scene = MapScene::createScene();
    //    /******************Start-Modified by Yafu****************************/
//    Vector<Node *> children = scene->getChildren();
//    mainLayer = (MainScene *)children.back();
//    /******************End-Modified by Yafu*****************************/
    
    Director::getInstance()->replaceScene(scene);
}

