//
//  UIManager.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/16.
//
//

//********************************************************************************
// インクルード
//********************************************************************************
#include "UIManager.h"
#include "Score.h"
#include "MenuBar.h"
#include "LifeBar.h"
#include "Item.h"

static const int TOOTHMANAGER_DISPLAY_CENTER_X = (320);

//================================================================================
// コンストラクタ
//================================================================================
UIManager::UIManager(void)
{
    // メンバ変数の初期化
    m_pScore = nullptr;
    m_pMenuBar = nullptr;
    m_pLifeBar = nullptr;
    m_pItem = nullptr;
    m_pLayer = nullptr;
}

//================================================================================
// デストラクタ
//================================================================================
UIManager::~UIManager()
{

}

//================================================================================
// 初期化処理
//================================================================================
bool UIManager::init(void)
{
    /*
    // スコア生成
    m_pScore = Score::create();

    // スプライトサイズ取得
    Rect gumSpriteRect = (m_pScore->getSprite()->getBoundingBox());

    // 座標変換(左上を持ってきているため、中心にそろえる処理)
    m_pScore->setPos(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                           m_startLeftTopPos.y - (gumSpriteRect.size.height / 2)));

    // スプライトの再配置
    m_pScore->refreshSpritePos();

    // スプライトの登録
    m_pLayer->addChild(m_pScore->getSprite());
/*
    // 上歯生成処理
//    m_pTopTooth = Tooth::create();

    // スプライトサイズ取得
    Rect toothSpriteRect = m_pTopTooth->getSprite()->getBoundingBox();

    // 座標変換
    m_pTopTooth->setPos(TOOTHMANAGER_DISPLAY_CENTER_X,
                        m_pTopGum->getPos().y - gumSpriteRect.size.height / 2 - (toothSpriteRect.size.height / 2));

    // スプライトの再配置
    m_pTopTooth->refreshSpritePos();

    // スプライトの登録
    m_pLayer->addChild(m_pTopTooth->getSprite());


    // 下歯生成処理
    m_pBottomTooth = Tooth::create(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                                        m_pTopTooth->getPos().y - toothSpriteRect.size.height));

    // スプライトの回転
    m_pBottomTooth->getSprite()->setRotation(180);

    // スプライトの登録
    m_pLayer->addChild(m_pBottomTooth->getSprite());

    // 下歯茎生成処理
    m_pBottomGum = Gum::create(Vec2(TOOTHMANAGER_DISPLAY_CENTER_X,
                                    m_pBottomTooth->getPos().y - toothSpriteRect.size.height / 2 - gumSpriteRect.size.height / 2));

    // スプライトの登録
    m_pLayer->addChild(m_pBottomGum->getSprite());

    */
    // 正常終了
    return true;
}

//================================================================================
// 終了処理
//================================================================================
void UIManager::uninit(void)
{

}

//================================================================================
// 更新処理
//================================================================================
void UIManager::update(void)
{
}

//================================================================================
// 生成処理
//================================================================================
UIManager* UIManager::create(const Vec2& startLeftTopPos,Layer* layer)
{
    // 歯マネージャーのインスタンス化
    UIManager* pUIManager = new UIManager();

    // メンバー変数の代入
    pUIManager->m_startLeftTopPos = startLeftTopPos;
    pUIManager->m_pLayer = layer;

    // 初期化
    pUIManager->init();

    return pUIManager;
}
/*
//================================================================================
// 上歯茎と上歯の座標を足す
//================================================================================
void UIManager::addTopGumPosAndTopToothPos(const Vec2& vec)
{
    m_pTopGum->addPos(vec);
    m_pTopGum->refreshSpritePos();

    m_pTopTooth->addPos(vec);
    m_pTopTooth->refreshSpritePos();
}

//================================================================================
// 下歯茎と下歯の座標を足す
//================================================================================
void UIManager::addBottomGumPosAndBottomToothPos(const Vec2& vec)
{
    m_pBottomGum->addPos(vec);
    m_pBottomGum->refreshSpritePos();

    m_pBottomTooth->addPos(vec);
    m_pBottomTooth->refreshSpritePos();
}

//================================================================================
// 上下歯を動かす
//================================================================================
void UIManager::moveToothAndGum(float time, Vec2 pos)
{
    //仮の座標に画像のPosを加算する
    m_pTopTooth->addPos(pos);
    m_pBottomTooth->addPos(pos * -1);
    m_pTopGum->addPos(pos);
    m_pBottomGum->addPos(pos * -1);
    //m_pTopTooth->RefreshSpritePos();

    Vec2 TopToothPos = m_pTopTooth->getPos();
    Vec2 BottomToothPos = m_pBottomTooth->getPos();

    Vec2 TopGumPos = m_pTopGum->getPos();
    Vec2 BottomGumPos = m_pBottomGum->getPos();

    //歯
    m_pTopTooth->getSprite()->runAction(MoveTo::create(1.0f, TopToothPos));
    m_pBottomTooth->getSprite()->runAction(MoveTo::create(1.0f, BottomToothPos));
    //歯茎
    m_pTopGum->getSprite()->runAction(MoveTo::create(1.0f, TopGumPos));
    m_pBottomGum->getSprite()->runAction(MoveTo::create(1.0f, BottomGumPos));
    
}
*/
