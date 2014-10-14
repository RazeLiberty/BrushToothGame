//
//  Gum.h
//  ToothBrushGame
//
//  Created by 丸山 潤 on 2014/10/14.
//
//

#ifndef __ToothBrushGame__Gum__
#define __ToothBrushGame__Gum__

#include <stdio.h>
//********************************************************************************
// インクルード
//********************************************************************************
#include "cocos2d.h"

//********************************************************************************
// 名前空間の使用
//********************************************************************************
using namespace cocos2d;

//********************************************************************************
// クラス宣言
//********************************************************************************
class Gum
{
public:
    Gum();
    ~Gum();
    
    bool init(void);
    void uninit(void);
    void update(void);
    
    static Gum* Create(const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSprite;}
    
    void setPos(Vec2 pos){m_pos = pos;}
    void setPos(float x,float y){m_pos.x = x;m_pos.y = y;}
    void addPos(Vec2 pos){m_pos += pos;}
    void addPos(float x,float y){m_pos.x += x;m_pos.y += y;}
    Vec2 getPos(void){return m_pos;}
    
    void RefressSpritePos(void){m_pSprite->setPosition(m_pos);}
    
private:
    Sprite* m_pSprite;
    Vec2 m_pos;
    Vec3 m_rot;
};
#endif /* defined(__ToothBrushGame__Gum__) */
