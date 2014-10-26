//
//  ResultScene.cpp
//  ToothBrushGame
//
//  Created by 鈴木愛忠 on 2014/10/20.
//
//
#include "TextureFile.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "RankManager.h"
#include "Sound.h"
USING_NS_CC;
bool ResultScene::m_bGameOverFlag = false;
int ResultScene::m_nScore;
//================================================================================
// シーン生成
//================================================================================

Scene* ResultScene::createScene(bool bGameOverFlag,int nScoreNumber)
{
    m_bGameOverFlag = bGameOverFlag;
    m_nScore = nScoreNumber;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResultScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

//================================================================================
// シーン初期化
//================================================================================
// on "init" you need to initialize your instance
bool ResultScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    //終了ボタン生成
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ResultScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // 更新処理の追加
    this->scheduleUpdate();
    // タッチ機能の有効化
    m_pTouchEventOneByOne =  EventListenerTouchOneByOne::create();
    m_pTouchEventOneByOne->setSwallowTouches(true);
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(ResultScene::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(ResultScene::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(ResultScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 100);
  
    //フラグに応じてゲームオーバ処理分岐
    void (ResultScene::*pFuncInit)();
    if(!m_bGameOverFlag)
    {
        pFuncInit = &ResultScene::initGameClear;
        m_pFuncUpdate = &ResultScene::updateGameClear;
        
    }else{
        pFuncInit = &ResultScene::initGameOver;
        m_pFuncUpdate = &ResultScene::updateGameOver;
        
    }
    
    (this->*pFuncInit)();
    
    //スコアとランク表示
    m_pRankManager = RankManager::create(Vec2(origin.x + 100,origin.y + 600),m_nScore, this);
    
    //ボタン表示
    MenuItemSprite* pButtonRetry;
    MenuItemSprite* pButtonTitle;
    
    //タップ前のスプライト
    Sprite* pNormalSprite = Sprite::create(TEX_RESULT_RETRY_BUTTON);
    pNormalSprite->setOpacity(180);
    pNormalSprite->setColor(Color3B(250,150,150));
    
    //タップ時のスプライト
    Sprite* pSelectedSprite = Sprite::create(TEX_RESULT_RETRY_BUTTON);
    pSelectedSprite->setColor(Color3B(255,200,200));
    pButtonRetry = MenuItemSprite::create(pNormalSprite,pSelectedSprite,CC_CALLBACK_0(ResultScene::ButtonRetry,this));
    
    Menu* pButton = Menu::create(pButtonRetry,NULL);
    addChild(pButton);
    
    //タイトルボタン
    //タップ前のスプライト
    Sprite* pNormalSprite2 = Sprite::create(TEX_RESULT_TITLE_BUTTON);
    pButton->setPosition(Vec2(visibleSize.width / 2,origin.y + 280));
    pNormalSprite2->setColor(Color3B(150,150,250));

    pNormalSprite2->setOpacity(180);
    
    //タップ時のスプライト
    Sprite* pSelectedSprite2 = Sprite::create(TEX_RESULT_TITLE_BUTTON);
    pSelectedSprite2->setColor(Color3B(200,200,255));

    pButtonTitle = MenuItemSprite::create(pNormalSprite2,pSelectedSprite2,CC_CALLBACK_0(ResultScene::ButtonTitle,this));

    pButton = Menu::create(pButtonTitle,NULL);
    pButton->setPosition(Vec2(visibleSize.width / 2,origin.y + 200));
    addChild(pButton);
    
    /*
    //今、BGMが流れているかどうか
    if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
        
        //音楽を止める
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
        
    }else{
        
        //タイトル画面BGMを再生
        SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_RESULT_1);
        
    }
    */
    return true;
}

//================================================================================
// ゲーム終了処理
//================================================================================

void ResultScene::menuCloseCallback(Ref* pSender)
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
void ResultScene::update(float fTime)
{
    (this->*m_pFuncUpdate)();
}

//================================================================================
// タップ開始判定
//================================================================================

bool ResultScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();
    return true;
}

//================================================================================
// スワイプ判定
//================================================================================

void ResultScene::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
}

//================================================================================
// タップ離した判定
//================================================================================

void ResultScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void ResultScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    
}

//================================================================================
// ゲームオーバ初期化
//================================================================================
void ResultScene::initGameOver(void)
{
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    Sprite* pSprite;
    pSprite = Sprite::create(TEX_RESULT_CLEAR_BACK);
    pSprite->setColor(Color3B::RED);
    pSprite->setPosition(Vec2(pSprite->getContentSize().width / 2,visibleSize.height - pSprite->getContentSize().height / 2));
    this->addChild(pSprite);

}

//================================================================================
// ゲームクリア初期化
//================================================================================
void ResultScene::initGameClear(void)
{
    Size visibleSize = Director::getInstance()->getVisibleSize() / 2 + SCREEN_CENTER;
    Vec2 origin = Director::getInstance()->getVisibleSize() / 2 - SCREEN_CENTER;
    
    Sprite* pSprite;
    pSprite = Sprite::create(TEX_RESULT_CLEAR_BACK);
    pSprite->setColor(Color3B::YELLOW);
    pSprite->setPosition(Vec2(pSprite->getContentSize().width / 2,visibleSize.height - pSprite->getContentSize().height / 2));
    this->addChild(pSprite);

}

//================================================================================
// ゲームオーバ更新
//================================================================================
void ResultScene::updateGameOver(void)
{
    
}

//================================================================================
// ゲームクリア更新
//================================================================================
void ResultScene::updateGameClear(void)
{
    m_pRankManager->update();
}

//================================================================================
// リトライボタン処理
//================================================================================
void ResultScene::ButtonRetry(void)
{
    setNextScene(SCENE_GAME);
}
//================================================================================
// タイトルボタン処理
//================================================================================
void ResultScene::ButtonTitle(void)
{
    setNextScene(SCENE_TITLE);
}
//================================================================================
// 次のシーンへ
//================================================================================
void ResultScene::setNextScene(SCENE_LIST sceneList)
{
    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    this->unscheduleUpdate();
    if(sceneList == SCENE_TITLE)
    {
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f,TitleScene::createScene(),Color3B::WHITE));
    }else{
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f,GameMainScene::createScene(),Color3B::WHITE));
    }
}

