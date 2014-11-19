//
//  SkillButton.cpp
//  brave
//
//  Created by Lishi Jiang on 11/17/14.
//
//

#include "SkillButton.h"
#include "SkillButton.h"

USING_NS_CC;

SkillButton::SkillButton():
    mItemSkill(NULL),
    mMenuSkill(NULL),
    mStencil(NULL),
    mProgressTimer(NULL),
    mCDTime(1.f)
{
    
}

SkillButton::~SkillButton()
{
    
}

SkillButton* SkillButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, int i)
{
    SkillButton* skillButton = new SkillButton();
    if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name, i))
    {
        skillButton->autorelease();
        return skillButton;
    }
    else
    {
        delete skillButton;
        skillButton = NULL;
    }
    
    return NULL;
}

bool SkillButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, int i)
{
    CCAssert(stencil_file_name, "SkillButton::init stencil_file_name != NULL");
    CCAssert(button_normal_name, "SkillButton::init button_normal_name != NULL");
    CCAssert(button_click_name, "SkillButton::init button_click_name != NULL");
    
    index = i;
    // 添加技能按钮 下层

    mItemSkill = MenuItemImage::create(button_normal_name, button_click_name, CC_CALLBACK_1(SkillButton::skillClickCallBack, this));
    mItemSkill->setPosition(CCPointZero);
    
    mMenuSkill = Menu::create(mItemSkill, NULL);
    mMenuSkill->setPosition(CCPointZero);
    addChild(mMenuSkill, -100);
    
    // 添加旋转进度条精灵---半阴影 上层
    Sprite* progressSprite = Sprite::create(stencil_file_name);
    mProgressTimer = ProgressTimer::create(progressSprite);
    mProgressTimer->setPosition(CCPointZero);
    mProgressTimer->setVisible(false);
    addChild(mProgressTimer, 100);
    
    mCDTime = cdTime;
    return true;
}

/** 技能按钮点击回调 */
void SkillButton::skillClickCallBack(Ref* pSender)
{
    // 冷却计时，即时状态技能按钮不可点击
    mItemSkill->setEnabled(false);
    
    
    
    //put out fire
    if (index == 2) {
        _player->setWeapon(Weapon::WeaponType::WATER);
        Tree* t = _weaponManager->getNearestTree(_trees);
        
        if (t) {
            _player->attack(_weaponManager->getAttackRadius(t));
            t->setBlood(-20.);
        }
        _player->setWeapon(Weapon::WeaponType::COCONUT);
    }
    //get all the banana
    if (index == 3) {
        CCObject* obj=NULL;
        Banana* banana=NULL;
        CCARRAY_FOREACH(bananaManger->_bananaArr,obj)/*循环遍历怪物数组，重复出现在屏幕上*/
        {
            banana=(Banana*) obj;
            if(banana->isAlive())/*活动状态*/
            {
                _player->money += Banana::value;
                banana->hide();
                float time = 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3));
                banana->timeshow(time);
            }
        }
    }
    
    
    
    
    
    
    mProgressTimer->setVisible(true);
    mProgressTimer->setType(ProgressTimerType::RADIAL);
    mProgressTimer->setReverseProgress(true); // 设置进度条为逆时针
    
    //准备一个旋转360度的动画(逐渐覆盖半透模板形成冷却效果;这里进行计时冷却动画的实现和时间控制)
    
    //注意这里冷却效果是从100%到0%顺时针变化的
    ActionInterval* action_progress_from_to = ProgressFromTo::create(mCDTime, 100, 0);
    auto skillCoolDownCallBack = [&]()
    {
        mProgressTimer->setVisible(false);
        
        // 按钮置为可用
        mItemSkill->setEnabled(true);
    };

    
    CallFunc* action_callback = CallFunc::create(skillCoolDownCallBack);
    
    mProgressTimer->runAction(Sequence::create(action_progress_from_to, action_callback, NULL));
}

/** 技能冷却完成回调 */
void SkillButton::skillCoolDownCallBack(Sprite* node)
{
    // 进度条技能不可见
    mProgressTimer->setVisible(false);
    
    // 按钮置为可用
    mItemSkill->setEnabled(true);
}