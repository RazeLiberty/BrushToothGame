//
//  SoundManager.cpp
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/27.
//
//

#include "SoundManager.h"

int SoundManager::m_nSoundId[SOUND_MAX];

const char* SOUND_NAME[SOUND_MAX] = {
    SE_POWDER_2,
    SE_BUTTON_1,
};

using namespace CocosDenshion;

void SoundManager::init()
{
    //音量を設定 1.0 ~ 0.0
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0);

    // BGMの場合
    /*
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_1);
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_2);
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_3);
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_4);
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_5);
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_6);
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_7);
     SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BOSS_SCENE_8);
     */
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_ENEMY_SCENE_1);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_ENEMY_SCENE_5);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_GAME_CLEAR_1);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_STAGE_SELECT_1);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_STAGE_SELECT_2);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_RESULT_1);



    // EFFECTの場合
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.3);

    SimpleAudioEngine::getInstance()->preloadEffect(SE_BUTTON_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_BUTTON_2);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_START_BUTTON_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_ENEMY_DOWN_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_ENEMY_DOWN_2);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_ENEMY_DOWN_3);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_DAMAGE_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_SWIPE_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_SWIPE_2);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_SWIPE_3);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_FANFARE_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_GAME_OVER_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_POWDER_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_POWDER_2);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_GET_ACHIEVEMENT_1);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_GET_ACHIEVEMENT_2);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_GET_ACHIEVEMENT_3);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_GET_ACHIEVEMENT_4);

    /*
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_DOWN_1);

     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_APPEAR_1);
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_GAME_OVER_1);
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SE_BOSS_GAME_OVER_2);
     */

    for(int nloop = 0 ; nloop < SOUND_MAX;nloop++)
    {
        m_nSoundId[nloop] = 0;

    }

}


void SoundManager::uninit()
{
    /*
     //BGM
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_1);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_2);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_3);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_4);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_5);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_6);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_7);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_BOSS_SCENE_8);
     */
    /*
     SimpleAudioEngine::getInstance()->unloadEffect(BGM_ENEMY_SCENE_1);
     SimpleAudioEngine::getInstance()->unloadEffect(BGM_ENEMY_SCENE_2);
     SimpleAudioEngine::getInstance()->unloadEffect(BGM_ENEMY_SCENE_3);
     SimpleAudioEngine::getInstance()->unloadEffect(BGM_ENEMY_SCENE_4);

     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_GAME_CLEAR_1);

     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_STAGE_SELECT_1);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(BGM_STAGE_SELECT_2);

     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BGM_RESULT_1);
     */

    //SE
    SimpleAudioEngine::getInstance()->unloadEffect(SE_BUTTON_1);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_BUTTON_2);

    SimpleAudioEngine::getInstance()->unloadEffect(SE_START_BUTTON_1);

    SimpleAudioEngine::getInstance()->unloadEffect(SE_ENEMY_DOWN_1);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_ENEMY_DOWN_2);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_ENEMY_DOWN_3);

    /*
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(SE_BOSS_DOWN_1);

     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(SE_BOSS_APPEAR_1);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(SE_BOSS_GAME_OVER_1);
     CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(SE_BOSS_GAME_OVER_2);
     */
    SimpleAudioEngine::getInstance()->unloadEffect(SE_DAMAGE_1);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_SWIPE_1);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_SWIPE_2);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_SWIPE_3);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_FANFARE_1);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_GAME_OVER_1);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_GET_ACHIEVEMENT_1);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_GET_ACHIEVEMENT_2);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_GET_ACHIEVEMENT_3);
    SimpleAudioEngine::getInstance()->unloadEffect(SE_GET_ACHIEVEMENT_4);

}

void SoundManager::playSoundID(SOUND_LABEL soundlabel)
{
    if(m_nSoundId[soundlabel] == 0)
    {
    //音量を設定 1.0 ~ 0.0
    SimpleAudioEngine::getInstance()->setEffectsVolume(SE_VOLUME_MAX);
    m_nSoundId[soundlabel] = SimpleAudioEngine::getInstance()->playEffect(SOUND_NAME[soundlabel], true);
    }
}

void SoundManager::stopSoundID(SOUND_LABEL soundlabel)
{
    if(m_nSoundId[soundlabel] != 0)
    {
    SimpleAudioEngine::getInstance()->stopEffect(m_nSoundId[soundlabel]);

    m_nSoundId[soundlabel] = 0;
    }

}
