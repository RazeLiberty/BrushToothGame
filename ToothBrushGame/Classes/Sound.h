//
//  Sound.h
//  ToothBrushGame
//
//  Created by 川原 岳大 on 2014/10/20.
//
//

#ifndef ToothBrushGame_Sound_h
#define ToothBrushGame_Sound_h


#include "SimpleAudioEngine.h"

//CocosDenshion::を書くのが面倒な人用
using namespace CocosDenshion;
//********************************************************************************
// BGM
//********************************************************************************
#define BGM_VOLUME_MIN (0.1f)
#define BGM_VOLUME_MAX (1.0f)

#define SE_VOLUME_HALF (0.5f)
#define SE_VOLUME_MAX (1.0f)
#define SE_ENEMY_DOWN_VOLUME_1 (0.5f)

#define BGM_TITLE_1 ("bgm_title_1.mp3")
#define BGM_TITLE_2 ("bgm_title_2.mp3")

#define BGM_BOSS_SCENE_1 ("bgm_boss_scene_1.mp3")
#define BGM_BOSS_SCENE_2 ("bgm_boss_scene_2.mp3")
#define BGM_BOSS_SCENE_3 ("bgm_boss_scene_3.mp3")
#define BGM_BOSS_SCENE_4 ("bgm_boss_scene_4.mp3")
#define BGM_BOSS_SCENE_5 ("bgm_boss_scene_5.mp3")
#define BGM_BOSS_SCENE_6 ("bgm_boss_scene_6.mp3")
#define BGM_BOSS_SCENE_7 ("bgm_boss_scene_7.mp3")
#define BGM_BOSS_SCENE_8 ("bgm_boss_scene_8.mp3")

#define BGM_ENEMY_SCENE_1 ("bgm_enemy_scene_1.mp3")
#define BGM_ENEMY_SCENE_2 ("bgm_enemy_scene_2.mp3")
#define BGM_ENEMY_SCENE_3 ("bgm_enemy_scene_3.mp3")
#define BGM_ENEMY_SCENE_4 ("bgm_enemy_scene_4.mp3")
#define BGM_ENEMY_SCENE_5 ("bgm_enemy_scene_5.mp3")

#define BGM_GAME_CLEAR_1 ("bgm_game_clear_1.mp3")

#define BGM_STAGE_SELECT_1 ("bgm_stageselect_1.mp3")
#define BGM_STAGE_SELECT_2 ("bgm_stageselect_2.mp3")

#define BGM_RESULT_1 ("bgm_result_1.mp3")


//********************************************************************************
// SE
//********************************************************************************

//ボタン
#define SE_BUTTON_1 ("se_button_1.mp3")
#define SE_BUTTON_2 ("")

#define SE_START_BUTTON_1 ("se_game_start_1.mp3")


/*
//歯垢
#define SE_PLAQUE_DOWN_1 ("se_plaque_down_1.mp3")
#define SE_PLAQUE_DOWN_2 ("se_plaque_down_2.mp3")
#define SE_PLAQUE_DOWN_3 ("se_plaque_down_3.mp3")
*/

//敵
#define SE_ENEMY_DOWN_1 ("hit_1.wav")
#define SE_ENEMY_DOWN_2 ("se_enemy_down_3.mp3")
#define SE_ENEMY_DOWN_3 ("se_enemy_down.wav")

/*
//ボス
#define SE_BOSS_DOWN_1 ("se_damage_1.mp3")
#define SE_BOSS_APPEAR_1 ("voice_boss_appear_1.mp3")
#define SE_BOSS_GAME_OVER_1 ("voice_boss_game_over_1.mp3")
#define SE_BOSS_GAME_OVER_2 ("voice_boss_game_over_2.mp3")
*/

//ダメージ
#define SE_DAMAGE_1 ("se_damage_1.mp3")

//スワイプ
#define SE_SWIPE_1 ("se_swipe_1.mp3")
#define SE_SWIPE_2 ("se_swipe_2.wav")
#define SE_SWIPE_3 ("se_swipe_3.mp3")

#define SE_POWDER_1 ("se_powder_1.mp3")
#define SE_POWDER_2 ("se_powder_2.mp3")

#define SE_FANFARE_1 ("se_fanfare_1.mp3")

#define SE_GAME_OVER_1 ("se_game_over_1.mp3")

#define SE_GET_ACHIEVEMENT_1 ("get_achievement_1.mp3")
#define SE_GET_ACHIEVEMENT_2 ("get_achievement_2.mp3")
#define SE_GET_ACHIEVEMENT_3 ("get_achievement_3.mp3")
#define SE_GET_ACHIEVEMENT_4 ("get_achievement_4.mp3")

#endif
