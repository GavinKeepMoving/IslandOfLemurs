//
//  WinScene.h
//  brave
//
//  Created by Wenbo Lin on 11/9/14.
//
//

#ifndef __brave__WinScene__
#define __brave__WinScene__

#include <stdio.h>
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class WinScene : public Layer
{
private:
    Vec2 screen;
public:
    bool init();
    static Scene* createScene();
    void onWin(Ref* obj);
    CREATE_FUNC(WinScene);
    
    void setMapMarkIcons();
    void addMarkIcon(Vec2 pos);
};

#endif /* defined(__brave__WinScene__) */
