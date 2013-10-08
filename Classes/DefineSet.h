//
//  DefineSet.h
//  ww2
//
//  Created by xiao tang on 12-9-29.
//
//

#ifndef ww2_DefineSet_h
#define ww2_DefineSet_h
#include "CoordinateTrans.h"

#define glScissorAdapter CoordinateTrans::glScissorAdapter

//#define transTiledSizeInRetina CoordinateTrans::transTiledSizeInRetina
//
//#define transWindowToGLInRetinaInt CoordinateTrans::transWindowToGLInRetinaInt
//
//#define transWindowToGLInRetina CoordinateTrans::transWindowToGLInRetina

#define winSize CCDirector::sharedDirector()->getWinSize()

#define absf(_x) Mathlib::absFloat(_x)

#define keyNum 1.0

#define decelerateSpeed 3

#define sendScanRate 0.5

//同一个状态的不痛表示
#define BeAttackStateTag 17
#define WorkStateTag 17
#define DefendStateTag 17
#define battleNormalStateTag 17

#define UnfinishedStateTag 15
#define RepairStateTag 10000

#define DestroyStateTag 19
#define ReadyToBuildStateTag 26
#define RuinsStateTag 21
#define GarbageCollectionStateTag 22

#define waitMenuTag 9

//Transition
#define BuildTransition 9002
#define CancelTransition 9003
#define CollectTransition 9005
#define InfoTransition 9006
#define UpdateTransition 9007
#define ConscriptionTransition 9008
#define RepairTransition 9009
#define sellTransition 9010
#define sureTransition 9011
#define toRuinsTransition 9012
#define CombineTransition 9013
#define SplitTransition 9014





//ui
#define recordToggleTag 7
#define recorderLayerTag 8
#define MainMapTag 14
#define controlMenuTag 24
#define creatorLayerTag 25
#define resourceBarTag 28
#define avatarTag 29
#define avatarAverseTag 37
#define UIBottomTag 30
#define UILayerTag 31
#define updateLayerTag 33
#define updateMenuTag 35
#define charDialogTag 36
#define levelUpLayerTag 40
#define nicknameLabelTag 41

//scenetag
#define startSceneTag 1000
#define battleSceneTag 1001
#define NewbieStartSceneClassTag 1002
#define NewbieBattleSceneClassTag 1003
#define NewbieMovieSceneClassTag 1004
#define ChthiefSceneClassTag 1005
#define ReadyToBattleTag 1006
#define NewbieReadySceneClassTag 1007
#define unitCreatorClassTag 1008
#define buildingCreatorClassTag 1009
#define ServerSceneTag 1010
#define defendSceneTag 1011
#define battleSceneBySearchTag 1012

#define oilTag 1
#define ironTag 2
#define expTag 3
#define gloryTag 4
#define diamondTag 5
#define levelTag 6
#define powerTag 7

//buildingTag
#define bingyingTag 50
#define youtianTag 51
#define kuangchangTag 52
#define zhihuisuoTag 54
#define wallTag 53
#define dapaoTag 55
#define diaobaoTag 56
#define lianluozhongxinTag 57
#define lianluozhongxinDestroyTag 58
#define combineWall5X1Tag 59
#define combineWall1X5Tag 60
#define superKuangChangTag 61
#define superYouTianTag 62
#define GarbageCenterTag 63
#define CellarTag 64
#define JammerTag 65

#define ghostTag 10

#define ornamentsDefineTag 9000
#define songshuTag 9000
#define stoneBaseTag 9100

#define nameFontTag 1
#define levelFontTag 2
#define battleTipTag 3
#define battleTipAimTag 4


#define byBaseHealth 100
#define wallBaseHealth 45
#define wallUpdateHealthRate 1
#define jdBaseHealth 100
#define jdUpdateHealthRate 5
#define combineWallBaseHealth 325

#define ytBaseHealth 100
#define ytBaseColletSpeed 0.05
#define ytBaseColletMaxCapacity 1000
#define ytUpdateHealthRate 1
#define ytUpdateColletMaxCapacityRate 1
#define ytUpdateColletSpeedRate 0.5

#define kcOriColletSpeed 0
#define kcOriMaxCapacity 0
#define kcBaseColletSpeed 0.05
#define kcBaseColletMaxCapacity 1000
#define kcBaseHealth 100
#define kcUpdateHealthRate 1
#define kcUpdateColletMaxCapacityRate 1
#define kcUpdateColletSpeedRate 0.5

#define superKcOriCollectSpeed 1
#define superKcOriMaxCapacity 40000
#define superKcOriBaseHealth 300
#define superKcBaseColletSpeed 0.05
#define superKcBaseColletMaxCapacity 1000
#define superKcBaseHealth 200
#define superKcUpdateHealthRate 1.5
#define superKcUpdateColletMaxCapacityRate 2
#define superKcUpdateColletSpeedRate 1.5

#define superYtOriCollectSpeed 1
#define superYtOriMaxCapacity 40000
#define superYtOriBaseHealth 300
#define superYtBaseColletSpeed 0.05
#define superYtBaseColletMaxCapacity 1000
#define superYtBaseHealth 200
#define superYtUpdateHealthRate 1.5
#define superYtUpdateColletMaxCapacityRate 2
#define superYtUpdateColletSpeedRate 1.5

#define dpBaseSplash 1
#define dpBaseHealth 50
#define dpBaseDamage 18
#define dpBaseRange 10
#define dpUpdateDamageRate 1
#define dpUpdateRangeCount 0.5

#define dbBaseHealth 180
#define dbBaseDamage 12
#define dbBaseRange 7
#define dbUpdateDamageRate 0.6
#define dbUpdateHealthRate 1
#define dbBaseAttackRate 1
#define dbUpdateAttackRateRate -0.015

#define hszxBaseHealth 300
#define hszxBaseMaxRecycling 0.025
#define hszxUpdateMaxRecyclingCount 0.025

#define cellarBase 300
#define cellarUpdateRate 0.1


#define soft_version 0
#define hard_version 1
#define game_version hard_version

#define ezqx 0
#define ezzhg 1
#define ezzhgThird 2
#define game_style ezqx


#define attackLD 0
#define attackLU 1
#define attackRD 2
#define attackRU 3

#define relativeZeroType 0
#define relativeCenterType 1
#define relativeWidthType 2

#define relativeDWidthZeroType 0
#define relativeDWidthCenterType 1
#define relativeDWidthWidthType 2

#endif