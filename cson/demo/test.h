#ifndef __CSON_DEMO_TEST_H__
#define __CSON_DEMO_TEST_H__

#include "cson.h"

/*
    Step1:定义与json相对应的数据结构
*/
typedef struct {            //@CSON_REF_START(Lyric)
    int         time;       //@CSON_REF(time,int)
    char*       text;       //@CSON_REF(text,string)
} Lyric;                    //@CSON_REF_END()

typedef struct {                            //@CSON_REF_START(SongInfo)
    char*       songName;                   //@CSON_REF(songName,string)
    char*       signerName;                 //@CSON_REF(signerName,string)
    char*       albumName;                  //@CSON_REF(albumName,string)
    char*       url;                        //@CSON_REF(url,string)
    int         duration;                   //@CSON_REF(duration,int)
    int         paid;                       //@CSON_REF(paid,int)
    double      price;                      //@CSON_REF(price,real)
    size_t      lyricNum;                   //@CSON_REF_AN(lyricNum)
    Lyric*      lyric;                      //@CSON_REF_A(lyric,object,Lyric,lyricNum)
    size_t      keyNum;                     //@CSON_REF_AN(keyNum)
    int*        key;                        //@CSON_REF_A(key,int,int,keyNum)
    size_t      strNum;                     //@CSON_REF_AN(strNum)
    char**      strList;                    //@CSON_REF_A(strList,string,char*,strNum)
} SongInfo;                                 //@CSON_REF_END()

typedef struct {                            //@CSON_REF_START(ExtData)
    int         a;                          //@CSON_REF(a,int)
    double      b;                          //@CSON_REF(b,real)
} ExtData;                                  //@CSON_REF_END()

typedef struct {                            //@CSON_REF_START(PlayList)
    char*       name;                       //@CSON_REF(name,string)
    char*       creater;                    //@CSON_REF(creater,string)
    size_t      songNum;                    //@CSON_REF_AN(songNum)
    SongInfo*   songList;                   //@CSON_REF_A(songList,object,SongInfo,songNum)
    ExtData     extData;                    //@CSON_REF_O(extData,ExtData)
} PlayList;                                 //@CSON_REF_END()

#endif