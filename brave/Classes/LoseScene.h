//
//  LoseScene.h
//  brave
//
//  Created by Wenbo Lin on 11/9/14.
//
//

#ifndef __brave__LoseScene__
#define __brave__LoseScene__

#include <stdio.h>
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class LoseScene : public Layer
{
    
public:
    //need to create an object first before createScene
    bool createScene(Layer* father);
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__brave__LoseScene__) */
