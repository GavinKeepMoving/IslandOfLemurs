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

void WinScene::createScene(Layer* father)
{
     auto winSprite = Sprite::create("win.png");
     //winSprite->setAnchorPoint(ccp(0, 0));
     auto targetPos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
     winSprite->setScale(0.5, 0.5);
     winSprite->setPosition(targetPos);
    father->addChild(winSprite);
}