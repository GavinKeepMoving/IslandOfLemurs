//
//  LoseScene.cpp
//  brave
//
//  Created by Wenbo Lin on 11/9/14.
//
//

#include "LoseScene.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "CustomTool.h"

extern MainScene *mainLayer;

using namespace std;

void LoseScene::createScene(Layer* father)
{
    auto LoseSprite = Sprite::create("lose.png");
    //winSprite->setAnchorPoint(ccp(0, 0));
    auto targetPos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
    LoseSprite->setScale(0.5, 0.5);
    LoseSprite->setPosition(targetPos);
    father->addChild(LoseSprite);
}