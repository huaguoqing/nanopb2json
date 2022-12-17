/**
* @file test.h.cson_ref_tbl.c 
*   !!!AUTO GENERTAED BY ../script/cson-c.sh, DON'T EDIT
*   define the cson reflect table for c structure.
*   src_file:test.h
* @date   2022-12-17
*/

#include "cson.h"
#include "test.h"
#include "test.h.cson_ref_tbl.h"

#undef CSON_REF_NAME
#define CSON_REF_NAME Lyric
CSON_REF_START(Lyric)
CSON_REF(time,int)
CSON_REF(text,string)
CSON_REF_END()
#undef CSON_REF_NAME
#define CSON_REF_NAME SongInfo
CSON_REF_START(SongInfo)
CSON_REF(songName,string)
CSON_REF(signerName,string)
CSON_REF(albumName,string)
CSON_REF(url,string)
CSON_REF(duration,int)
CSON_REF(paid,int)
CSON_REF(price,real)
CSON_REF_AN(lyricNum)
CSON_REF_A(lyric,object,Lyric,lyricNum)
CSON_REF_AN(keyNum)
CSON_REF_A(key,int,int,keyNum)
CSON_REF_AN(strNum)
CSON_REF_A(strList,string,char*,strNum)
CSON_REF_END()
#undef CSON_REF_NAME
#define CSON_REF_NAME ExtData
CSON_REF_START(ExtData)
CSON_REF(a,int)
CSON_REF(b,real)
CSON_REF_END()
#undef CSON_REF_NAME
#define CSON_REF_NAME PlayList
CSON_REF_START(PlayList)
CSON_REF(name,string)
CSON_REF(creater,string)
CSON_REF_AN(songNum)
CSON_REF_A(songList,object,SongInfo,songNum)
CSON_REF_O(extData,ExtData)
CSON_REF_END()
