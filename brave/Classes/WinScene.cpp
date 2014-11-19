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
#include "MapScene.h"

extern MainScene *mainLayer;

using namespace std;

bool WinScene::createScene(cocos2d::Layer *father) {
    
    auto winSprite = Sprite::create("win.png");
    
    cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemImage::create(
                                                                   "backToMap.png",
                                                                   "backToMap.png",
                                                                   this,
                                                                   menu_selector(WinScene::menuCloseCallback));
    //pCloseItem->setAnchorPoint(ccp(0, 0));
    //pCloseItem->setPosition(0, 0);
    
    cocos2d::Menu* pMenu = cocos2d::Menu::create(pCloseItem, NULL);
    
    //pMenu->setAnchorPoint(ccp(0, 0));
    pMenu->setPosition(winSprite->getContentSize().width / 2, winSprite->getContentSize().height * 0.2);
    
    winSprite->addChild(pMenu, 1);
    
    auto targetPos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
    winSprite->setScale(0.5, 0.5);
    winSprite->setPosition(targetPos);
    father->addChild(winSprite);
    
    return true;
}

void WinScene::menuCloseCallback(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(scene);
}