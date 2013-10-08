//
//  CryptologyUtil.cpp
//  ZLib
//
//  Created by user on 13-1-15.
//  Copyright (c) 2013年 MJiao-iTiTa. All rights reserved.
//

#include <iostream>

#include "CryptologyUtil.h"

static const std::string alphabet64( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" );
static const char pad = '=';
static const char np  = (char)std::string::npos;

static char table64vals[] =
{
    62, np, np, np, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, np, np, np, np, np,
    np, np,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, np, np, np, np, np, np, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

inline char table64( unsigned char c )
{
    return ( c < 43 || c > 122 ) ? np : table64vals[c-43];
}



/**
 * Base64加密
 *
 * Base64-encodes the input according to RFC 3548.
 * @param input The data to encode.
 * @return The encoded string.
 */
CCString* CryptologyUtil::encode64( CCString* input1 )
{
    std::string input = input1->m_sString;
    std::string encoded;
    char c;
    const std::string::size_type length = input.length();
    
    encoded.reserve( length * 2 );
    
    for( std::string::size_type i = 0; i < length; ++i )
    {
        c = static_cast<char>( ( input[i] >> 2 ) & 0x3f );
        encoded += alphabet64[c];
        
        c = static_cast<char>( ( input[i] << 4 ) & 0x3f );
        if( ++i < length )
            c = static_cast<char>( c | static_cast<char>( ( input[i] >> 4 ) & 0x0f ) );
        encoded += alphabet64[c];
        
        if( i < length )
        {
            c = static_cast<char>( ( input[i] << 2 ) & 0x3c );
            if( ++i < length )
                c = static_cast<char>( c | static_cast<char>( ( input[i] >> 6 ) & 0x03 ) );
            encoded += alphabet64[c];
        }
        else
        {
            ++i;
            encoded += pad;
        }
        
        if( i < length )
        {
            c = static_cast<char>( input[i] & 0x3f );
            encoded += alphabet64[c];
        }
        else
        {
            encoded += pad;
        }
    }
    
    return CCString::create(encoded);
}

/**
 * Base64解密
 *
 * Base64-decodes the input according to RFC 3548.
 * @param input The encoded data.
 * @return The decoded data.
 */
CCString* CryptologyUtil::decode64(CCString* input1 )
{
    std::string input = input1->m_sString;
    char c, d;
    const std::string::size_type length = input.length();
    std::string decoded;
    
    decoded.reserve( length );
    
    for( std::string::size_type i = 0; i < length; ++i )
    {
        c = table64(input[i]);
        ++i;
        d = table64(input[i]);
        c = static_cast<char>( ( c << 2 ) | ( ( d >> 4 ) & 0x3 ) );
        decoded += c;
        if( ++i < length )
        {
            c = input[i];
            if( pad == c )
                break;
            
            c = table64(input[i]);
            d = static_cast<char>( ( ( d << 4 ) & 0xf0 ) | ( ( c >> 2 ) & 0xf ) );
            decoded += d;
        }
        
        if( ++i < length )
        {
            d = input[i];
            if( pad == d )
                break;
            
            d = table64(input[i]);
            c = static_cast<char>( ( ( c << 6 ) & 0xc0 ) | d );
            decoded += c;
        }
    }
    
    return CCString::create(decoded);
    
}