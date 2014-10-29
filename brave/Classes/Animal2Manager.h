//
//  Animal2Manager.h
//  brave
//
//  Created by Lishi Jiang on 10/26/14.
//
//

#ifndef __brave__Animal2Manager__
#define __brave__Animal2Manager__

#include "cocos2d.h"
#include "Animal2.h"
USING_NS_CC;


class Animal2Manager:public Node
{
public:
    Animal2Manager();
    ~Animal2Manager();
    
    static Animal2Manager* create(Sprite* background);
    
    virtual bool init();
    virtual void update(float dt);/*重写update函数*/
    //void bindPlayer(Player* player);
    
    void bindBackground(Sprite* background);
    Sprite* _background;
    void createAnimal2s();/*创建Monster对象*/

    private:
    __Array* _animal2Arr;/*存放怪物数组*/
    //Player* _player;
};


#endif /* defined(__brave__Animal2Manager__) */
