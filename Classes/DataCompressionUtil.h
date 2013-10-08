//
//  DataCompressionUtil.h
//  ZLib
//
//  Created by user on 13-1-14.
//  Copyright (c) 2013年 MJiao-iTiTa. All rights reserved.
//

#ifndef ZLib_DataCompressionUtil_h
#define ZLib_DataCompressionUtil_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <zlib.h>

#include "cocos2d.h"

using namespace cocos2d;
//
//  DataCompressionUtil.h
//
//  压缩压缩与解压工具类  
//
//  Created by user on 13-1-14.
//  Copyright MJiao-iTiTa 2013年. All rights reserved.
//
class DataCompressionUtil {
    
private :
    /**
        对数据解析Gzip压缩
     */
    int static gzipCompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata);
    /**
       对Gzip数据进行解压缩
     */
    bool static gzipUnCompress(const std::string& compressedBytes, std::string& uncompressedBytes);
 
    
public:
    
    /**
        使用GZip的方式对字符串进行压缩
        @param source压缩的字符串
        @return 返回经过GZip压缩过
    */
    const static char* gzipCompressData(const char* source);
    
    /**
     使用GZip的方式对字符串进行解压缩
     @param source要解压缩的字符串
     @return 返回经过GZip解压缩过
     */
    const static char* gzipUnCompressData(const char*  source);
    
    /**
       使用Zlib的方式对字符串进行解压缩
        @param data要解压缩的字符串
        @return 返回经过GZip解压缩过
     */
    static CCString*  compressData(CCString* data );
    
    /**
     使用Zlib的方式对字符串进行解压缩
     @param source要解压缩的字符串
     @return 返回经过GZip解压缩过
     */
    static CCString*  unCompressData(CCString* data );
//    static CCString*  unCompressData(char* data);
    
};

#endif
