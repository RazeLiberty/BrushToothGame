//
//  GameMainScene.cpp
//  ToothBrushGame
//
//  Created by 鈴木 愛忠 on 2014/10/17.
//
//
#include "TextureFile.h"
#include "common.h"
#include "GameMainScene.h"
#include "Tooth.h"
#include "ToothManager.h"
#include "Plaque.h"
#include "PlaqueManager.h"
#include "EnemyManager.h"
#include "Boss.h"
#include "HitChecker.h"
#include "LifeBar.h"
#include "UIManager.h"
#include "EffectManager.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "PauseScene.h"
#include "Score.h"
#include "Sound.h"
#include "CountDown.h"
#include "ToothPowder.h"
#include "GameDifficult.h"
#include "CharacterStatus.h"
#include "VirusToothManager.h"
#include "VirusTooth.h"
#include "Clock.h"
USING_NS_CC;
#define SHAKE_PERMISSION_DISTANCE (0.3f)

static const GAME_PASE_DATA GamePhaseData[PHASE_MAX] =
{
    {Enemy::ENEMY_KIND_NORMAL_ONE,5,0,Point(150,600)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,10,5,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,30,10,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,3,15,Point(200,300)},
    {Enemy::ENEMY_KIND_LAIR_ONE,4,20,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,10,25,Point(300,350)},
    {Enemy::ENEMY_KIND_LAIR_TWO,3,30,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,30,10,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_TWO,10,35,Point(150,400)},
    {Enemy::ENEMY_KIND_LAIR_TREE,2,40,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_ONE,40,10,Point(300,400)},
    {Enemy::ENEMY_KIND_NORMAL_TREE,2,45,Point(150,400)},
    {Enemy::ENEMY_KIND_NORMAL_TREE,5,50,Point(150,400)},
};
//================================================================================
// デストラクタ
//================================================================================
GameMainScene::~GameMainScene()
{
    SAFE_DELETE(m_pEnemyManager);
    SAFE_DELETE(m_pToothManager);
    SAFE_DELETE(m_pPlaqueManager);
    SAFE_DELETE(m_pUIManager);
    SAFE_DELETE(m_pHitChecker);
    SAFE_DELETE(m_EffectManager);
    SAFE_DELETE(m_pVirusToothManager);
    //すべてのSEを止める
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

//================================================================================
// シーン生成
//================================================================================

Scene* GameMainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

//================================================================================
// シーン初期化
//================================================================================
// on "init" you need to initialize your instance
bool GameMainScene::init()
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
                                           CC_CALLBACK_1(GameMainScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    Enemy::initEnemyDownNum();
    
    //始めるフェーズから
    m_nGamePhase = PHASE_ONE;

    m_nGameTime = GamePhaseData[m_nGamePhase].spawnTime;//終わりの時間になるまで加算
    
    // 更新処理の追加
    this->scheduleUpdate();
    
    // タッチ機能の有効化
    m_pTouchEventOneByOne =  EventListenerTouchOneByOne::create();
    m_pTouchEventOneByOne->setSwallowTouches(true);
    m_pTouchEventOneByOne->onTouchBegan = CC_CALLBACK_2(GameMainScene::onTouchBegin,this);
    m_pTouchEventOneByOne->onTouchMoved = CC_CALLBACK_2(GameMainScene::onTouchMoved,this);
    m_pTouchEventOneByOne->onTouchCancelled = CC_CALLBACK_2(GameMainScene::onTouchCancelled, this);
    m_pTouchEventOneByOne->onTouchEnded = CC_CALLBACK_2(GameMainScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_pTouchEventOneByOne, 100);

    // 加速度センサーの有効化
    Device::setAccelerometerEnabled(true);
    auto pAccelerometerEventListener = EventListenerAcceleration::create(CC_CALLBACK_2(GameMainScene::onAcceleration, this));
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pAccelerometerEventListener, this);
    
    // 歯マネージャーのインスタンス化
    m_pToothManager = ToothManager::create(Vec2(visibleSize.width / 2,visibleSize.height - 64),this);
    m_bHit = false;
    m_pPlaqueManager = PlaqueManager::create(0,m_pToothManager->getToothSprite(), this);

    // タッチ時の判定生成
    m_pBubbleSprite = Sprite::create(TEX_BUBBLE_01);
    m_bubblePos = Vec2(0.0f,0.0f);
    m_pBubbleSprite->setPosition(m_bubblePos);
    m_pBubbleSprite->setOpacity(0);
    this->addChild(m_pBubbleSprite);

    m_acc = Vec3(0,0,0);
    m_acc = m_oldAcc;
    m_nShakeCnt = 0;
    m_pVirusToothManager = VirusToothManager::create(this,m_pToothManager->getToothSprite());
    m_pEnemyManager = EnemyManager::create(this,0);
    //================================================================================
    //敵関係はこれより前に生成
    
    //エフェクト生成
    m_EffectManager = EffectManager::create(this, 0);
    
    //フラグ初期化
    m_bMove = false;
    m_touchPos = Point(0.0f,0.0f);
    m_oldTouchPos = m_touchPos;
    m_swipeDirection = SWIPE_DIRECTION_NONE;
    m_oldSwipeDirection = m_swipeDirection;
    
    //UI生成
    m_pUIManager = UIManager::create(this);

    m_pHitChecker = HitChecker::create(m_pEnemyManager, m_pToothManager, m_pPlaqueManager,m_pUIManager);

    m_pPauseLayer = nullptr;

    m_nTimer = 0;
    

    // 生成が終わった後にカウントダウンを生成する
    //this->scheduleOnce(schedule_selector(GameMainScene::createCountDown), 0.0f);

    
    //今、BGMが流れているかどうか
    if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()){
        
        //音楽を止める
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
        
    }
    
        //音量調整
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(BGM_GAMESCENE_VOLUME_3);
    //タイトル画面BGMをループ再生 第二引数がループするかどうか判定
    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_ENEMY_SCENE_5, true);
        
    m_nUgaiCounter = 0;

    return true;
}

//================================================================================
// ゲーム終了処理
//================================================================================
void GameMainScene::menuCloseCallback(Ref* pSender)
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
void GameMainScene::update(float fTime)
{
    // 歯の更新
    m_pToothManager->update();
    // 歯垢の更新
    m_pPlaqueManager->update();
    
    // 歯を動かすか判定
    //歯垢が０になったら
    int nPlaqur = m_pPlaqueManager->getPlaqueNum();
    Plaque** ppPlaque = m_pPlaqueManager->getPlaqueTop();
    int nPlaqurNum = 0;
    for(int nloop = 0;nloop < nPlaqur;nloop++)
    {
        //生きていたらカウント
        if(!ppPlaque[nloop]->getDisappear())
        {
            nPlaqurNum++;
        }
    }
    
    //敵の更新
    m_pEnemyManager->update();
    
    //UI更新
    m_pUIManager->update();
    //エフェクト更新
    m_EffectManager->update();

    m_pHitChecker->checkEnemyFollowPowder(m_touchPos, m_pUIManager->getToothPowder()->getPowderTouchFlag());
    
    updateGamePhase();

}

//================================================================================
// タップ開始判定
//================================================================================

bool GameMainScene::onTouchBegin(Touch* pTouch,Event* pEvent)
{
    m_nTimer++;
    
    // タッチ座標の取得
    m_touchPos = pTouch->getLocation();

    // ポーズメニューを開く
    if(m_pHitChecker->checkTapOnMenuBar(m_touchPos))
    {
        //音量調整
        SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_HALF);
        //SE
        SimpleAudioEngine::getInstance()->playEffect(SE_BUTTON_1);
        m_pPauseLayer = PauseScene::createLayer();
        this->addChild(m_pPauseLayer);
        this->pause();
        return true;
    }
    
    // 泡スプライトの追従
    m_bubblePos = m_touchPos;
    m_pBubbleSprite->setPosition(m_bubblePos);
    m_pBubbleSprite->setOpacity(10);

    m_EffectManager->spawn(40,m_touchPos);
    
    m_pHitChecker->hitCheckTap(m_pBubbleSprite->getBoundingBox());
    
    m_pUIManager->getToothPowder()->chkPowderTouchFlag(m_touchPos);
    
    return true;
}

//================================================================================
// スワイプ判定
//================================================================================

void GameMainScene::onTouchMoved(Touch* pTouch,Event* pEvent)
{
    Point swipVec = Point(0,0);
    
    // タッチ座標の取得
    m_oldTouchPos = m_touchPos;
    m_touchPos = pTouch->getLocation();
    
    // 泡スプライトの追従
    m_bubblePos = m_touchPos;
    m_pBubbleSprite->setPosition(m_bubblePos);
    if(m_pUIManager->getToothPowder()->getPowderTouchFlag())
    {
        m_EffectManager->spawn(10,m_touchPos,Color3B(220,220,255));
    }
    CCLOG("現タッチ位置(%f,%f)",m_touchPos.x,m_touchPos.y);
    CCLOG("旧タッチ位置(%f,%f)",m_oldTouchPos.x,m_oldTouchPos.y);
    
    float fDistance = m_touchPos.distance(m_oldTouchPos);
    
    CCLOG("距離(%f)",fDistance);
    
    // スワイプされているならスワイプ方向の取得
    if(fDistance > SWIPE_PERMISSION_DISTANCE)
    {
        Point::subtract(m_touchPos, m_oldTouchPos, &swipVec);
        float fAngle = atan2f(swipVec.x,swipVec.y);
        CCLOG("角度(%f)",fAngle);
        
        m_oldSwipeDirection = m_swipeDirection;
        m_swipeDirection = calcSwipeDirection(fAngle);
    }
    else
    {
        m_swipeDirection = SWIPE_DIRECTION_NONE;
    }
    
    // スワイプされていないorスワイプしていても異常な角度
    if(m_swipeDirection == SWIPE_DIRECTION_NONE)
    {
        return;
    }
    
    // 当たり判定領域の算出
    Rect bubbleRect = m_pBubbleSprite->getBoundingBox();
    Rect swipeRect;
    swipeRect.setRect(m_touchPos.x - swipVec.x - bubbleRect.size.width / 2 ,m_touchPos.y - swipVec.y  - bubbleRect.size.height / 2,
                      swipVec.x + bubbleRect.size.width, swipVec.y + bubbleRect.size.height);


    // 歯磨き粉スプライト座標調整
    if(m_pUIManager->getToothPowder()->getPowderTouchFlag())
    {
        Rect gameTopRect = m_pUIManager->getGameTopBackSprite()->getBoundingBox();
        Rect gameBottomRect = m_pUIManager->getGameBottomBackSprite()->getBoundingBox();
        Rect toothPowderRect = m_pUIManager->getToothPowder()->getSprite()->getBoundingBox();
        Point workPoint = m_touchPos;

        // ゲーム上部UIに引っかかるなら戻す
        if(gameTopRect.origin.y < workPoint.y + toothPowderRect.size.height / 2)
        {
            workPoint.y = gameTopRect.origin.y - toothPowderRect.size.height / 2;
        }

        // ゲーム下部UIに引っかかるなら戻す
        if(gameBottomRect.origin.y + gameBottomRect.size.height > workPoint.y - toothPowderRect.size.height / 2)
        {
            workPoint.y = gameBottomRect.origin.y + gameBottomRect.size.height + toothPowderRect.size.height / 2;
        }

        m_pUIManager->getToothPowder()->setPos(workPoint);
    }

    // スワイプ時の当たり判定
    m_pHitChecker->hitCheckSwipe(swipeRect, m_swipeDirection,m_pUIManager->getToothPowder()->getPowderTouchFlag());
}

//================================================================================
// タップ離した判定
//================================================================================

void GameMainScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    m_pHitChecker->hitCheckTouchEnded(m_pBubbleSprite->getBoundingBox(),m_pUIManager->getToothPowder()->getPowderTouchFlag());

    // タッチしていないので泡スプライトを透明に
    m_pBubbleSprite->setOpacity(0);
    
    m_swipeDirection = SWIPE_DIRECTION_NONE;
    
    m_pUIManager->getToothPowder()->disappear();
    
    m_bHit = false;
    m_nTimer = 0;
}

//================================================================================
// タッチ時に割り込み処理
//================================================================================
void GameMainScene::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    m_pHitChecker->hitCheckTouchEnded(m_pBubbleSprite->getBoundingBox(),m_pUIManager->getToothPowder()->getPowderTouchFlag());
    
    m_nTimer = 0;
    m_pUIManager->getToothPowder()->disappear();
    
}

//================================================================================
// 加速度センサー割り込み処理
//================================================================================
void GameMainScene::onAcceleration(Acceleration *acc,Event *unused_event)
{
    m_oldAcc = m_acc;
    m_acc = Vec3(acc->x,acc->y,acc->z);

    Vec3 work = m_acc - m_oldAcc;
    float fDistance = (work.x * work.x + work.y * work.y + work.z * work.z);

    if(fDistance > SHAKE_PERMISSION_DISTANCE)
    {
        m_nShakeCnt++;
    }

    //シェイク３回でうがい処理
    if(m_nShakeCnt > 3)
    {
        if(m_nUgaiCounter == 0)
        {
        AchievementDataBaseList::addAchievement(ACHIEVEMENT_TYPE_USE_UGAI);
        m_pUIManager->getCharacterStatus()->setPattern(CharacterStatus::CHARACTERSTATUS_PATTERN_GIDDY);
        m_pHitChecker->checkEnemyDown();
        
        //SE
        SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_MAX);
        SimpleAudioEngine::getInstance()->playEffect(SE_SWIPE_3);
            m_nUgaiCounter = 1;
        }
        m_nShakeCnt = 0;

    }
}

//================================================================================
// スワイプ方向
//================================================================================
GameMainScene::SWIPE_DIRECTION GameMainScene::calcSwipeDirection(float fAngle)
{
    fAngle = fAngle * 180 / M_PI;
    
    if(fAngle <= 45 && fAngle >= -45)
    {
        CCLOG("上方向");

        return SWIPE_DIRECTION_UP;

    }
    
    if(fAngle <= 135 && fAngle >= 45)
    {
        CCLOG("右方向");
        return SWIPE_DIRECTION_RIGHT;
    }
    
    if(fAngle <= -45 && fAngle >= -135)
    {
        CCLOG("左方向");
        return SWIPE_DIRECTION_LEFT;
    }
    
    if((fAngle <= -135 && fAngle >= -180) || (fAngle <= 180 && fAngle >= 135))
    {
        CCLOG("下方向");
        m_pHitChecker->checkEnemyDown();
        return SWIPE_DIRECTION_DOWN;
    }
    
    return SWIPE_DIRECTION_NONE;
}
//================================================================================
// 結果へ移行
//================================================================================
void GameMainScene::setResultScene(bool bGameOverFlag)
{
    this->getEventDispatcher()->removeAllEventListeners();
    this->removeAllChildren();
    this->unscheduleUpdate();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f,ResultScene::createScene(bGameOverFlag,m_pUIManager->getClock()->getColockNow()),Color3B::WHITE));
}
//================================================================================
// カウントダウン生成処理
//================================================================================
void GameMainScene::createCountDown(float fTime)
{
    m_pCountDown = CountDown::createLayer(5,m_pHitChecker);
    this->addChild(m_pCountDown);
    this->pause();

    m_bCountDownEnd = false;
}

//================================================================================
// ゲームフェーズ更新
//================================================================================
void GameMainScene::updateGamePhase(void)
{
    m_nTimer++;
    if(m_nUgaiCounter != 0)
    {
    m_nUgaiCounter++;
        if(m_nUgaiCounter > UGAI_DELAY)
        {
            m_nUgaiCounter = 0;
        }
    }
    if(m_nTimer % 60 == 0)
    {
        m_nGameTime++;
        AchievementDataBaseList::saveAchievement();
        
    }
    chkGamePhase();
}
//================================================================================
// ゲームフェーズチェック
//================================================================================
void GameMainScene::chkGamePhase(void)
{
    if(m_nGamePhase < PHASE_MAX && (m_nGameTime >= GamePhaseData[m_nGamePhase].spawnTime || m_pEnemyManager->getEnemyNum() < 2))
    {
        m_pEnemyManager->spawn(GamePhaseData[m_nGamePhase].enemykind,GamePhaseData[m_nGamePhase].spawn,m_pVirusToothManager->getVirusToothsTop(m_nGamePhase)->getSprite()->getPosition());
        m_pVirusToothManager->getVirusToothsTop(m_nGamePhase)->disappear();
        if(m_nGamePhase <= PHASE_MAX)
        {
            m_nGamePhase++;
        }
    }
    int nEnemyDown = 0;

    for(int nloop = 0; nloop < PHASE_MAX;nloop++)
    {
        if(GamePhaseData[nloop].enemykind < Enemy::ENEMY_KIND_LAIR_ONE)
        {
            nEnemyDown += GamePhaseData[nloop].spawn;
        }
    }
    int EnemyAll = 0;
    for(int nloop = 0 ; nloop < Enemy::ENEMY_KIND_LAIR_ONE;nloop++)
    {
        EnemyAll += Enemy::getEnemyKindDownNum(nloop);
    }
    if(  EnemyAll >= nEnemyDown)
    {
        setResultScene(false);
    }else
    if(m_pUIManager->getClock()->getColockNow() < 0)
    {
        setResultScene(true);
    }

    m_pUIManager->getCharacterStatus()->checkChangePattern(nEnemyDown,EnemyAll );
}
