//
//  BaseMessage.h
//  ww3
//
//  Created by xiao tang on 12-12-14.
//
//

#ifndef ww3_MyBaseMessage_h
#define ww3_MyBaseMessage_h

#define newbie1MessageTag 1
#define newbie1to2MessageTag 2
#define newbieClickMessageTag 3
#define toFightMessageTag 4
#define noResourceToDeployMessageTag 5
#define unionMessageTag 6
#define unionPushMessageTag 7
#define userMessageTag 8
#define gameDataMessageTag 9
#define systemMessageTag 10
#define storeMessageTag 11
#define updateBuildingMessageTag 13
#define updateArmyMessageTag 14
#define pushMessageTag 15
#define loadSpeakerMessageTag 16
#define UpLevelMessageTag 17
#define questMessageTag 18
#define questUpdateMessageTag 19
#define battleOverMessageTag 20
#define defendOverMessageTag 21
#define RemoveWaitLayerMessageTag 22
#define buildingMessageTag 23
#define DialogCompleteMessageTag 24
#define ThirdLoginCallBackMessageTag 25

#include "cocos2d.h"
using namespace cocos2d;

class MyBaseMessage : public CCObject{
    
public:
    virtual void sendMsg() = 0;
    int tag;
};


#endif
