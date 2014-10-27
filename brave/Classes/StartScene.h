//
//  StartScene.h
//  brave
//
//  Created by Yafu Li on 10/26/14.
//
//

#ifndef __brave__StartScene__
#define __brave__StartScene__

#include "cocos2d.h"

USING_NS_CC;

class StartScene : public Layer
{
public:
    bool init();
    static Scene* createScene();
    void onStart(Ref* obj);
    CREATE_FUNC(StartScene);
};

#endif /* defined(__brave__StartScene__) */
