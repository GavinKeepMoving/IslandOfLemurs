//
//  MapScene.cpp
//  brave
//
//  Created by Yafu Li on 11/2/14.
//
//

#include "MapScene.h"


#include "StartScene.h"

#include "MainScene.h"
#include "VisibleRect.h"
#include "CustomTool.h"

extern MainScene *mainLayer;

int globalLevel;

using namespace std;

bool MapScene::init()
{
    if(!Layer::init())
        return false;
    log("MapScene::init");
    
    screen = VisibleRect::rightTop() - VisibleRect::leftBottom();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/role.plist","image/role.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/ui.plist","image/ui.pvr.ccz");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/iui.plist","image/iui.png");
    auto background = Sprite::create("map.png");
    
    // position the sprite on the center of the screen
    //_background->setPosition(origin + visibleSize/2);
    //background->setPosition(background->getPosition() + Vec2(background->getBoundingBox().size.width, 0));
    background->setPosition(VisibleRect::center());
    this->addChild(background);
    
    setMapMarkIcons();
    

    return true;
}


Scene* MapScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MapScene::create();
    scene->addChild(layer);
    return scene;
}


void MapScene::onStart(Ref* obj, int level)
{
    globalLevel = level;
    log("StartLayer::onStart");
    auto scene = MainScene::createScene();
    
    //setLevel(3);
    /******************Start-Modified by Yafu****************************/
    Vector<Node *> children = scene->getChildren();
    mainLayer = (MainScene *)children.back();
    /******************End-Modified by Yafu*****************************/
    
    Director::getInstance()->replaceScene(scene);
}

void MapScene::setMapMarkIcons()
{
    std::vector<Vec2> markPositions;
    markPositions.push_back(VisibleRect::leftBottom() + Vec2(screen.x / 8, screen.y / 8));
    markPositions.push_back(VisibleRect::leftBottom() + Vec2(screen.x / 4, screen.y / 4));
    markPositions.push_back(VisibleRect::leftBottom() + Vec2(screen.x / 2, screen.y / 2));
    
    int level = 1;
    for (auto p : markPositions) {
        addMarkIcon(p, level);
        level++;
    }
    
}

void MapScene::addMarkIcon(Vec2 pos, int level)
{
    auto item = CustomTool::createMenuItemImage("mark.png", "mark.png", CC_CALLBACK_1(MapScene::onStart,this, level));
    
    //item->setPosition(VisibleRect::center());
    auto menu = Menu::createWithItem(item);
    menu->setPosition(pos);
    this->addChild(menu, 1);


}
