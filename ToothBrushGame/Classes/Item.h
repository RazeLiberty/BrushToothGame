//
//  Item.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/16.
//
//


//********************************************************************************
// インクルードガード
//********************************************************************************
#ifndef __ToothBrushGame__Item__
#define __ToothBrushGame__Item__

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
class Item
{
public:
    Item();
    ~Item();

    bool init(void);
    void uninit(void);
    void update(void);

    static Item* create(const Vec2& pos = Vec2(0.0f,0.0f));
    Sprite* getSprite(void){return m_pSprite;}

    void setPos(Vec2 pos){m_pos = pos;}
    void setPos(float x,float y){m_pos.x = x;m_pos.y = y;}
    void setPosX(float x){m_pos.x = x;}
    void setPosY(float y){m_pos.y = y;}
    void addPos(Vec2 pos){m_pos += pos;}
    void addPos(float x,float y){m_pos.x += x;m_pos.y += y;}
    void addPosX(float x){m_pos.x += x;}
    void addPosY(float y){m_pos.y += y;}
    Vec2 getPos(void){return m_pos;}

    void refreshSpritePos(void){m_pSprite->setPosition(m_pos);}

private:
    Sprite* m_pSprite;
    Vec2 m_pos;
    Vec3 m_rot;
};


#endif /* defined(__ToothBrushGame__Item__) */
