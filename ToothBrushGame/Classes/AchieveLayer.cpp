//
//  AchieveLayer.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/27.
//
//

#include "AchieveLayer.h"

#include "TextureFile.h"
#include "AchievementList.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "RankManager.h"
USING_NS_CC;
//================================================================================
// シーン生成
//================================================================================

Scene* AchieveLayer::createScene(void)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AchieveLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

//================================================================================
// シーン初期化
//================================================================================
// on "init" you need to initialize your instance
bool AchieveLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    m_pAchieve = Sprite::create();
    m_pAchieve->setTextureRect(Rect(0,0,200,100));
    m_pAchieve->setColor(Color3B::WHITE);
    m_pAchieve->setPosition(Vec2(origin.x -200,origin.y + 850));
    
    // 文字列
    m_pTitle = LabelTTF::create("実績解除", "ariel", 24);
    //左上の位置に設定
    m_pTitle->setPosition(Vec2(origin.x - 200,origin.y + 850));

    // 文字列
    m_pMessage = LabelTTF::create("", "ariel", 24);
    //左上の位置に設定
    m_pMessage->setPosition(Vec2(m_pTitle->getPosition().x + m_pTitle->getContentSize().width,origin.y + 850));
    
    this->addChild(m_pAchieve,9995);
    this->addChild(m_pMessage,9996);
    this->addChild(m_pTitle,9997);
    return true;
}

//================================================================================
// ゲーム更新
//================================================================================
void AchieveLayer::update(float fTime)
{
}

//================================================================================
// タップ開始判定
//================================================================================

bool AchieveLayer::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();
    return true;
}

//================================================================================
// スワイプ判定
//================================================================================

void AchieveLayer::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
}

//================================================================================
// タップ離した判定
//================================================================================

void AchieveLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void AchieveLayer::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// タイトルボタン処理
//================================================================================
void AchieveLayer::ButtonTitle(void)
{
    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    this->unscheduleUpdate();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f,TitleScene::createScene(),Color3B::WHITE));
}

void AchieveLayer::setDispAchieveLayer(int nAchieveNum)
{
    m_pMessage->setString(AchievementDataBaseList::getAchievement(nAchieveNum).name);
    Sequence* pSequence = Sequence::create(MoveBy::create(3.0f,Vec2(200,m_pAchieve->getPosition().y)),MoveBy::create(3.0f,Vec2(-200,m_pAchieve->getPosition().y)), NULL);
    m_pAchieve->runAction(pSequence);
    m_pMessage->runAction(pSequence);
    m_pTitle->runAction(pSequence);

}