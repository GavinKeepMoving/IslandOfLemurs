//
//  MapScene.h
//  brave
//
//  Created by Yafu Li on 11/2/14.
//
//

#ifndef __brave__MapScene__
#define __brave__MapScene__

#include "cocos2d.h"

#include <vector>

USING_NS_CC;

class MapScene : public Layer
{
private:
    Vec2 screen;
public:
    bool init();
    static Scene* createScene();
    void onStart(Ref* obj);
    CREATE_FUNC(MapScene);
    
    void setMapMarkIcons();
    void addMarkIcon(Vec2 pos);
};

#endif /* defined(__brave__MapScene__) */
