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

class WinScene : public Menu
{
    //need to create an object first before createScene
public:
    bool createScene(Layer* father);
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__brave__WinScene__) */
