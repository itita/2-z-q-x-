//
//  DataCompressionUtil.cpp
//  ZLib
//
//  Created by user on 13-1-14.
//  Copyright (c) 2013年 MJiao-iTiTa. All rights reserved.
//

#include "DataCompressionUtil.h"
#include "cocos2d.h"


int DataCompressionUtil::gzipCompress(Bytef *data, uLong ndata, Bytef *zdata, uLong *nzdata)
{
    z_stream c_stream;
	int err = 0;
    
	if (data && ndata > 0) {
		c_stream.zalloc = (alloc_func) 0;
		c_stream.zfree = (free_func) 0;
		c_stream.opaque = (voidpf) 0;
		if (deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY)
            != Z_OK)
			return -1;
		c_stream.next_in = data;
		c_stream.avail_in = ndata;
		c_stream.next_out = zdata;
		c_stream.avail_out = *nzdata;
		while (c_stream.avail_in != 0 && c_stream.total_out < *nzdata) {
			if (deflate(&c_stream, Z_NO_FLUSH) != Z_OK)
				return -1;
		}
		if (c_stream.avail_in != 0)
			return c_stream.avail_in;
		for (;;) {
			if ((err = deflate(&c_stream, Z_FINISH)) == Z_STREAM_END)
				break;
			if (err != Z_OK)
				return -1;
		}
		if (deflateEnd(&c_stream) != Z_OK)
			return -1;
		*nzdata = c_stream.total_out;
		return 0;
	}
	return -1;
}
bool DataCompressionUtil::gzipUnCompress(const std::string& compressedBytes, std::string& uncompressedBytes)
{
    if (compressedBytes.size() == 0) {
		uncompressedBytes = compressedBytes;
		return true;
	}
    
	uncompressedBytes.clear();
    
	unsigned full_length = compressedBytes.size();
	unsigned half_length = compressedBytes.size() / 2;
    
	unsigned uncompLength = full_length;
	char* uncomp = (char*) calloc(sizeof(char), uncompLength);
    
	z_stream strm;
	strm.next_in = (Bytef *) compressedBytes.c_str();
	strm.avail_in = compressedBytes.size();
	strm.total_out = 0;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
    
	bool done = false;
    //if (inflateInit2(&d_stream, -MAX_WBITS) != Z_OK) 
	if (inflateInit2(&strm, -MAX_WBITS) != Z_OK) {
		free(uncomp);
		return false;
	}
    
    static char dummy_head[2] = { 0x8 + 0x7 * 0x10, (((0x8 + 0x7 * 0x10) * 0x100
                                                      + 30) / 31 * 31) & 0xFF, };
    
    
	while (!done) {
		// If our output buffer is too small
		if (strm.total_out >= uncompLength) {
			// Increase size of output buffer
			char* uncomp2 = (char*) calloc(sizeof(char),
                                           uncompLength + half_length);
			memcpy(uncomp2, uncomp, uncompLength);
			uncompLength += half_length;
			free(uncomp);
			uncomp = uncomp2;
		}
        
		strm.next_out = (Bytef *) (uncomp + strm.total_out);
		strm.avail_out = uncompLength - strm.total_out;
        
        strm.avail_in = strm.avail_out = 1; /* force small buffers */
        
        
		// Inflate another chunk.
		int err = inflate(&strm, Z_SYNC_FLUSH);
		if (err == Z_STREAM_END)
			done = true;
		else if (err != Z_OK) {
            if (err == Z_DATA_ERROR) {
                strm.next_in = (Bytef*) dummy_head;
                strm.avail_in = sizeof(dummy_head);
                if ((err = inflate(&strm, Z_NO_FLUSH)) != Z_OK) {
                    return err;
                }
            } else
            {
                return err;
            }
			break;
		}
	}
    
	if (inflateEnd(&strm) != Z_OK) {
		free(uncomp);
		return false;
	}
    
	for (size_t i = 0; i < strm.total_out; ++i) {
		uncompressedBytes += uncomp[i];
	}
	free(uncomp);
	return true;

}
 

/**
 使用GZip的方式对字符串进行压缩
 @param source压缩的字符串
 @return 返回经过GZip压缩过
 */
const char* DataCompressionUtil::gzipCompressData(const char* source)
{
       
    //要压缩的数据长度
    uLong ndata = strlen(source);
    //    
    uLong destLen= (ndata + 12)*1.001f + 20;
    
	Bytef zdata[destLen];
	uLong nzdata = destLen;
    
    //总的作用：将已开辟内存空间 s 的首 n 个字节的值设为值 c。
	//memset(zdata, 0, 1024);
    if (gzipCompress((Bytef *) source, ndata, zdata, &nzdata) == 0) {
        
       std::string returnStr((char * )zdata);
        
        //delete source;
        
        return returnStr.c_str();
    }
    
    delete source;
     cocos2d::CCLog("压缩失败...");
    return NULL;

}

/**
 使用GZip的方式对字符串进行解压缩
 @param source要解压缩的字符串
 @return 返回经过GZip解压缩过
 */
const  char* DataCompressionUtil::gzipUnCompressData(const char*  source)
{  
    std::string uncompressedBytes("");
    std::string compressedBytes(source);
    if(gzipUnCompress(compressedBytes, uncompressedBytes)){
         delete source;
        return uncompressedBytes.c_str();
    }  
    cocos2d::CCLog("解压失败...");
    delete source;
    return NULL;
 
}


/**
 使用Zlib的方式对字符串进行解压缩
 @param data要解压缩的字符串
 @return 返回经过GZip解压缩过
 */
CCString* DataCompressionUtil::compressData(CCString* data1 )
{   
    z_stream m_zinflate;
    z_stream m_zdeflate;
    std::string data = data1->m_sString;
    
    int ret = Z_OK;
    m_zinflate.zalloc = Z_NULL;
    m_zinflate.zfree = Z_NULL;
    m_zinflate.opaque = Z_NULL;
    m_zinflate.avail_in = 0;
    m_zinflate.next_in = Z_NULL;
    ret = inflateInit( &m_zinflate );
    if( ret != Z_OK )
        return NULL;
    
    m_zdeflate.zalloc = Z_NULL;
    m_zdeflate.zfree = Z_NULL;
    m_zdeflate.opaque = Z_NULL;
    m_zinflate.avail_in = 0;
    m_zinflate.next_in = Z_NULL;
    ret = deflateInit( &m_zdeflate, Z_BEST_COMPRESSION/*Z_DEFAULT_COMPRESSION*/ );
    if( ret != Z_OK )
    {
        return NULL;
    }

    
    
    long unsigned int CHUNK = data.length() + ( data.length() / 100 ) + 13;
    Bytef* out = new Bytef[CHUNK];
    char* in = const_cast<char*>( data.c_str() );
    
    
    
    m_zdeflate.avail_in = static_cast<uInt>( data.length() );
    m_zdeflate.next_in = (Bytef*)in;
    
  
    std::string result;
   
    do {
        m_zdeflate.avail_out = static_cast<uInt>( CHUNK );
        m_zdeflate.next_out = (Bytef*)out;
        
        ret = deflate( &m_zdeflate, Z_SYNC_FLUSH );
        result.append( (char*)out, CHUNK - m_zdeflate.avail_out );
    } while( m_zdeflate.avail_out == 0 );
    
    inflateEnd( &m_zinflate );
    deflateEnd( &m_zdeflate );
    
    delete[] out;
    
    return CCString::create(result);

    
    
}

/**
 使用Zlib的方式对字符串进行解压缩
 @param source要解压缩的字符串
 @return 返回经过GZip解压缩过
 */ 
CCString* DataCompressionUtil::unCompressData(CCString* data1 )
//CCString* DataCompressionUtil::unCompressData(char* data)
{
    z_stream m_zinflate;
    z_stream m_zdeflate;
    
    std::string data = data1->m_sString;
    
    int ret = Z_OK;
    
    m_zinflate.zalloc = Z_NULL;
    m_zinflate.zfree = Z_NULL;
    m_zinflate.opaque = Z_NULL;
    m_zinflate.avail_in = 0;
    m_zinflate.next_in = Z_NULL;
    ret = inflateInit( &m_zinflate );
    if( ret != Z_OK )
        return NULL;
    
    m_zdeflate.zalloc = Z_NULL;
    m_zdeflate.zfree = Z_NULL;
    m_zdeflate.opaque = Z_NULL;
    m_zinflate.avail_in = 0;
    m_zinflate.next_in = Z_NULL;
    ret = deflateInit( &m_zdeflate, Z_BEST_COMPRESSION/*Z_DEFAULT_COMPRESSION*/ );
    if( ret != Z_OK )
    {
        return NULL;
    }
     
    
    int CHUNK = 50;
    char* out = new char[CHUNK];
    char* in = const_cast<char*>( data.c_str() );
    
    m_zinflate.avail_in = static_cast<uInt>( data.length() );
    m_zinflate.next_in = (Bytef*)in;
    
    
    std::string result;
    do
    {
        m_zinflate.avail_out = CHUNK;
        m_zinflate.next_out = (Bytef*)out;
        
        ret = inflate( &m_zinflate, Z_SYNC_FLUSH );
        result.append( out, CHUNK - m_zinflate.avail_out );
    } while( m_zinflate.avail_out == 0 );
    
    
    inflateEnd( &m_zinflate );
    deflateEnd( &m_zdeflate );

    
    delete[] out;

    
    return   CCString::create(result);
 
}





