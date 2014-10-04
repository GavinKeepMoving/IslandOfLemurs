//
//  Tree.h
//  brave
//
//  Created by Wenbo Lin on 10/2/14.
//
//

#ifndef __brave__Tree__
#define __brave__Tree__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Tree : public Sprite
{
public:
    enum TreeStates
    {
        HEATHY,
        BURNING,
        BURNDOWN
    };

    TreeStates state;
    
    static float blood;
    
    Sprite* background;
    Sprite* background1;
    
    Tree(void);
    Tree(Sprite* background, Sprite* background1);
    
    static Tree* createTree();// put trees
    bool initSingleTree();
    std::vector<Tree*> initWithTreeNum(int num);// call createTree to build trees

    int getBlood();//get blood values
    TreeStates getState();//get state: burning or burn down or healthy
    bool generateBananas();//generate banana objects
    bool showAnimation();//show burning or burndown, need to call getState to know which animations to play
};

#endif /* defined(__brave__Tree__) */
