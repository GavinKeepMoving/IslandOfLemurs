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
#include "Fire.h"
USING_NS_CC;

class Tree : public Sprite
{
public:
    //0-6: 0 = healthy; 6 = burn up;
    int state;
    
    float blood;
    
    //store the position of trees
    float _posX;
    float _posY;
    
    Sprite* treeSprite;
    Sprite* _background;
    
    Tree(void);
    Tree(Sprite* tree);

    bool initSingleTree();
    std::vector<Tree*> initWithTreeNum(int num);// call createTree to build trees

    int setBlood(int value);
    
    int getBlood(Tree* tree);//get blood values
    int getState(Tree* tree);//get state: burning or burn down or healthy
    bool generateBananas(Tree* tree);//generate banana objects
    void showStateAccordingtoBlood();
    void showAnimation();//show burning or burndown, need to call getState to know which animations to play
    Fire* addFire(int scale);
    
    //sound effect
    unsigned int _soundEffectId;
};

#endif /* defined(__brave__Tree__) */
