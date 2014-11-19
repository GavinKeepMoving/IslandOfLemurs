//
//  LoseScene.cpp
//  brave
//
//  Created by Wenbo Lin on 11/9/14.
//
//
#include "MapScene.h"
#include "LoseScene.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "CustomTool.h"

extern MainScene *mainLayer;

using namespace std;

bool LoseScene::createScene(cocos2d::Layer *father) {
    
    auto loseSprite = Sprite::create("lose.png");
    
    loseSprite->setScale(10.0, 10.0);
    
    cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemImage::create(
                                                                   "backToMap.png",
                                                                   "backToMap.png",
                                                                   this,
                                                                   menu_selector(LoseScene::menuCloseCallback));
    
    cocos2d::Menu* pMenu = cocos2d::Menu::create(pCloseItem, NULL);
    
    pMenu->setPosition(loseSprite->getContentSize().width / 2, loseSprite->getContentSize().height * 0.3);
    
    loseSprite->addChild(pMenu, 1);
    
    auto targetPos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
    loseSprite->setScale(0.5, 0.5);
    loseSprite->setPosition(targetPos);
    father->addChild(loseSprite);
    
    return true;
}

void LoseScene::menuCloseCallback(cocos2d::Ref* pSender) {
    auto scene = MapScene::createScene();
    Director::getInstance()->replaceScene(scene);
}