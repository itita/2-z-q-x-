//
//  PurchaseAddtion.m
//  ww4
//
//  Created by xiao tang on 13-7-23.
//
//

#import "PurchaseAddtion.h"
#include "RemoveWaitLayerMessage.h"

@implementation PurchaseAddtion

+(void) sendRemoveWaitLayerMsg{
    RemoveWaitLayerMessage::create()->sendMsg();
}

@end
