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
    
    Sprite* treeSprite;
    
    Tree(void);
    Tree(Sprite* tree);

    bool initSingleTree();
    std::vector<Tree*> initWithTreeNum(int num);// call createTree to build trees

    int getBlood(Tree* tree);//get blood values
    int getState(Tree* tree);//get state: burning or burn down or healthy
    bool generateBananas(Tree* tree);//generate banana objects
    bool showAnimation(Tree* tree);//show burning or burndown, need to call getState to know which animations to play
};

#endif /* defined(__brave__Tree__) */
