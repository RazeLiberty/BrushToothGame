//
//  AchievementsScene.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/23.
//
//


#include "TextureFile.h"
#include "AchievementsScene.h"
#include "AchievementList.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "RankManager.h"
#include "Sound.h"
#include "Random.h"
USING_NS_CC;
AchievementsScene::~AchievementsScene()
{
    SAFE_DELETE(m_pAchievementList);
}
//================================================================================
// シーン生成
//================================================================================

Scene* AchievementsScene::createScene(void)
{    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AchievementsScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

//================================================================================
// シーン初期化
//================================================================================
// on "init" you need to initialize your instance
bool AchievementsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    // 更新処理の追加
    this->scheduleUpdate();
    // タッチ機能の有効化
    m_pTouchEventOneByOne =  EventListenerTouchOneByOne::create();
    m_pTouchEventOneByOne->setSwallowTouches(true);
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(AchievementsScene::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(AchievementsScene::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(AchievementsScene::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(AchievementsScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 100);
    
    Sprite* pSprite;
    pSprite = Sprite::create(TEX_RESULT_CLEAR_BACK);
    pSprite->setColor(Color3B::YELLOW);
    pSprite->setPosition(Vec2(pSprite->getContentSize().width / 2,visibleSize.height - pSprite->getContentSize().height / 2));
    this->addChild(pSprite);
    //リスト作成
    m_pAchievementList = AchievementList::create(this);
    
    //ボタン表示
    MenuItemSprite* pButtonTitle;
    
    //タイトルボタン
    //タップ前のスプライト
    Sprite* pNormalSprite2 = Sprite::create(TEX_BACK_BUTTON);
    pNormalSprite2->setColor(Color3B(255,255,255));
        
    //タップ時のスプライト
    Sprite* pSelectedSprite2 = Sprite::create(TEX_BACK_BUTTON);
    pSelectedSprite2->setColor(Color3B(200,200,200));
    
    pButtonTitle = MenuItemSprite::create(pNormalSprite2,pSelectedSprite2,CC_CALLBACK_0(AchievementsScene::ButtonTitle,this));
    
    Menu* pButton = Menu::create(pButtonTitle,NULL);
    pButton->setPosition(Vec2(visibleSize.width / 2,origin.y + 180));
    addChild(pButton);
    NendModule::hideNADView();

    char apiKey[] = "dda54eb3d743f07ab21f3a8f69805b221d1d8c8d";
    char spotID[] = "281367";
    NendInterstitialModule::createNADInterstitial(apiKey,spotID);
    
    char iconApiKey[] = "7921cf489ca3ba7ade7b5ff8ca16b73e8fa4be48";
    char iconSpotID[] = "281337";
    NendIconModule::createNADIconLoader(iconApiKey, iconSpotID);
    NendIconModule::createNADIconViewBottom();
    NendIconModule::load();
    NendIconModule::showNADIconView();
    return true;
}

//================================================================================
// ゲーム終了処理
//================================================================================

void AchievementsScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//================================================================================
// ゲーム更新
//================================================================================
void AchievementsScene::update(float fTime)
{
}

//================================================================================
// タップ開始判定
//================================================================================

bool AchievementsScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();
    return true;
}

//================================================================================
// スワイプ判定
//================================================================================

void AchievementsScene::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
}

//================================================================================
// タップ離した判定
//================================================================================

void AchievementsScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void AchievementsScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// タイトルボタン処理
//================================================================================
void AchievementsScene::ButtonTitle(void)
{
    //SE
    SimpleAudioEngine::getInstance()->playEffect(SE_BUTTON_1);
    
    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    this->unscheduleUpdate();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f,TitleScene::createScene(),Color3B::WHITE));
    short randView = RandomMT::getRaodom(0,1);
    if(randView)
    {
    NendInterstitialModule::showNADInterstitialView();
    }
    NendModule::showNADView();
    NendIconModule::hideNADIconView();
}
