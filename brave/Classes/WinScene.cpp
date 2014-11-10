//
//  WinScene.cpp
//  brave
//
//  Created by Wenbo Lin on 11/9/14.
//
//

#include "WinScene.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "CustomTool.h"

extern MainScene *mainLayer;

using namespace std;

bool WinScene::init()
{
    if(!Layer::init())
        return false;
    log("WinScene::init");
    
    screen = VisibleRect::rightTop() - VisibleRect::leftBottom();
    
    auto background = Sprite::create("win.png");
    
    background->setPosition(VisibleRect::center());
    
    this->addChild(background);

    return true;
}

Scene* WinScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WinScene::create();
    scene->addChild(layer);
    return scene;
}

void WinScene::onWin(Ref* obj)
{
    log("StartLayer::onWin");
    auto scene = MainScene::createScene();
    
    /******************Start-Modified by Yafu****************************/
    Vector<Node *> children = scene->getChildren();
    mainLayer = (MainScene *)children.back();
    /******************End-Modified by Yafu*****************************/
    
    Director::getInstance()->replaceScene(scene);
}