//
//  SkillButton.h
//  brave
//
//  Created by Lishi Jiang on 11/17/14.
//
//

#ifndef __brave__SkillButton__
#define __brave__SkillButton__
#include <cocos2d.h>
#include "Player.h"
#include "Tree.h"
#include "WeaponManager.h"
#include "BananaManger.h"
USING_NS_CC;
/**
 实现技能冷却效果
 
 Notice:添加child时要注意上下层关系
 最下方是按钮 其次是半透明的模版图片 最上方是CCProgressTimer进度条精灵
 */


class SkillButton : public Node
{
public:
    SkillButton();
    virtual ~SkillButton();
    
    /** 创建一个SkillButton对象
     */
    static SkillButton* createSkillButton(float cdTime,
                                          const char* stencil_file_name,
                                          const char* button_normal_name,
                                          const char* button_click_name,
                                          int i);
    
    /** CD时间设置
     */
    void    setCDTime(float time) { mCDTime = time; }
    float   getCDTime() const { return mCDTime; }
    
    /** 技能按钮点击回调 */
    void    skillClickCallBack(Ref* pSender);
    
    /** 技能冷却完毕回调*/
    void    skillCoolDownCallBack(Sprite* node);
    
    
    Player* _player;
    BananaManger* bananaManger;
    std::vector<Tree*> _trees;
    WeaponManager* _weaponManager;
private:
    int index;
    /** 初始化 */
    bool    init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name, int i);
    
private:
    MenuItemImage*   mItemSkill;     // 技能按钮
    Menu*            mMenuSkill;     // 技能按钮所在menu
    Sprite*          mStencil;       // 蒙板精灵,黑色半透明(这个是为了显示一个冷却计时效果)
    ProgressTimer*   mProgressTimer; // 时间进度条精灵(360度旋转)
    float            mCDTime;          // CD时间
};
#endif /* defined(__brave__SkillButton__) */

