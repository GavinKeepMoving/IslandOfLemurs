//
//  Fire.h
//  brave
//
//  Created by Wenbo Lin on 10/12/14.
//
//

#ifndef __brave__Fire__h
#define __brave__Fire__h

#include "cocos2d.h"
USING_NS_CC;

class Fire : public Sprite {
public:
    enum FireType
    {
        SHOW
    };
    
    bool initWithFireType(FireType type);
    static Fire* create(FireType type);
    
    void addAnimation();
    void playAnimationForever(int index);
    
    void setFire();
    
private:
    //Action _seq;
    float _speed;
    FireType _type;
    std::string _name;
    int _animationNum;
    std::vector<int> _animationFrameNum;
    std::vector<std::string> _animationNames;
    Sequence* _seq;
};



#endif /* defined(__brave__Fire__) */
