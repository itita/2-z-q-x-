//
//  CryptologyUtil.h
//  ZLib
//
//  Created by user on 13-1-15.
//  Copyright (c) 2013年 MJiao-iTiTa. All rights reserved.
//

#ifndef ZLib_CryptologyUtil_h
#define ZLib_CryptologyUtil_h


#include "cocos2d.h"

using namespace cocos2d;
//
//  CryptologyUtil.h
//  ZLib
//   
//  Created by user on 13-1-15.
//  Copyright MJiao-iTiTa 2013年. All rights reserved.
//
/**
   常用的加密，解密工具
 */
class CryptologyUtil {
    
public:
    
    /**
     * Base64加密
     *
     * Base64-encodes the input according to RFC 3548.
     * @param input The data to encode.
     * @return The encoded string.
     */
    static CCString*  encode64(CCString* input);
    
    /**
     * Base64解密
     *
     * Base64-decodes the input according to RFC 3548.
     * @param input The encoded data.
     * @return The decoded data.
     */
    static CCString*  decode64(CCString* input );
    
};

#endif
