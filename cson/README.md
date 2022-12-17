# 简体中文 | [English](./README_EN.md)

# cson
轻松完成C语言结构体和Json的转换。

其中Json字符串与Json对象（例如Jansson库中的json_t）之间的转换由第三方库实现（例如Jansson或者cJSON，请参考依赖库）。
cson真正实现的是Json对象与结构体间的转换。

## 编译
### 编译静态库
``` shell
$ git clone https://github.com/sunchb/cson.git
$ cd cson
$ make
```
### 编译示例
``` shell
$ cd demo
$ make
$ ./test
```
## 如何使用cson
1. 定义与Json协议对应的结构体。
2. 定义结构体的属性描述表。
3. 调用cson接口完成转换。

## 依赖
https://github.com/akheron/jansson.git
https://github.com/DaveGamble/cJSON.git

## 示例
下面具有各种数据类型的JSON。例如整数，字符串，实数，布尔值，对象和数组。我们将通过cson对其进行解码和编码。

``` json
{
    "name":"jay zhou",
    "creater":"dahuaxia",
    "songNum":2,
    "songList":[
        {
            "songName":"qilixiang",
            "signerName":"jay zhou",
            "albumName":"qilixiang",
            "url":"www.kugou.com",
            "duration":200,
            "paid":false,
            "price":6.6600000000000001,
            "lyricNum":2,
            "lyric":[
                {
                    "time":1,
                    "text":"Sparrow outside the window"
                },
                {
                    "time":10,
                    "text":"Multi mouth on the pole"
                }
            ]
        },
        {
            "songName":"dongfengpo",
            "signerName":"jay zhou",
            "albumName":"dongfengpo",
            "url":"music.qq.com",
            "duration":180,
            "paid":true,
            "price":0.88,
            "lyricNum":2,
            "lyric":[
                {
                    "time":10,
                    "text":"A sad parting, standing alone in the window"
                },
                {
                    "time":20,
                    "text":"I'm behind the door pretending you're not gone"
                }
            ]
        }
    ],
    "extData":{
        "a":999,
        "b":1.05
    }
}
```

### 1. 定义与Json协议对应的结构体。
即使不使用cson，通常我们也会这么做。

#### 注意事项
- 字符串必须定义为char*类型。
- 数组必须定义为指针类型。
- 如果结构体包含数组，需要为每一个数组定义一个额外的属性，用于保存数组大小。
- 结构体属性名必须与Json字段名一致。

``` c
typedef struct {
    int         time;
    char*       text;         /* String must be declared as char* */
} Lyric;

typedef struct {
    char*       songName;
    char*       signerName;
    char*       albumName;
    char*       url;
    int         duration;
    int         paid;
    double      price;
    size_t      lyricNum;     /* Declare additional properties to hold the array size */
    Lyric*      lyric;        /* Array must be declared as pointer */
} SongInfo;

typedef struct {
    int         a;
    double      b;
} ExtData;

typedef struct {
    char*       name;
    char*       creater;
    size_t      songNum;
    SongInfo*   songList;
    ExtData     extData;
} PlayList;
```

### 2. 定义结构体的属性描述表。

####2.1 方法1：使用以下宏定义描述结构体属性。
- _property_int(type, field) 
- _property_real(type, field)
- _property_bool(type, field)
- _property_string(type, field)
- _property_obj(type, field, tbl) 
- _property_array_object(type, field, tbl, arrayType, countfild) # I know it's a little cumbersome, I'm trying to simplify it.
- _property_array_int(type, field, arrayType, countfild)
- _property_array_string(type, field, arrayType, countfild)
- _property_array_real(type, field, arrayType, countfild)
- _property_array_bool(type, field, arrayType, countfild)


参数说明：
- type:         type of data structure
- field:        property name
- tbl:          description table of the property type. use when object or object array
- arrayType:    type of the array (Used to calculate size when dynamically get array memory)
- countfild:    property to save array size

也可以使用带有扩展参数的宏定义，其中args可以是_ex_args_nullable, _ex_args_exclude_decode, _ex_args_exclude_encode的组合。
- #define _ex_args_nullable         (0x01)  //不会因为该字段异常而停止后续字段解析, 该选项默认打开。
- #define _ex_args_exclude_decode   (0x02)  //该字段不参与解析————例如指示数组元素个数的字段，Json中可以不包含它
- #define _ex_args_exclude_encode   (0x04)  //该字段不参与格式化输出
- #define _ex_args_all              (_ex_args_nullable | _ex_args_exclude_decode | _ex_args_exclude_encode)

- _property_int_ex(type, field, args)
- _property_real_ex(type, field, args)
- _property_bool_ex(type, field, args)
- _property_string_ex(type, field, args)
- _property_obj_ex(type, field, tbl, args)
- _property_array_ex(type, field, tbl, subType, count, args)
- _property_array_object_ex(type, field, tbl, subType, count, args)
- _property_array_int_ex(type, field, subType, count, args)
- _property_array_string_ex(type, field, subType, count, args)
- _property_array_real_ex(type, field, subType, count, args)
- _property_array_bool_ex(type, field, subType, count, args)

``` c
/* description for Lyric */
reflect_item_t lyric_ref_tbl[] = {
    _property_int(Lyric, time),
    _property_string(Lyric, text),
    _property_end()
};

/* description for SongInfo */
reflect_item_t song_ref_tbl[] = {
    _property_string(SongInfo, songName),
    _property_string(SongInfo, signerName),
    _property_string(SongInfo, albumName),
    _property_string(SongInfo, url),
    _property_int(SongInfo, duration),
    _property_bool(SongInfo, paid),
    _property_real(SongInfo, price),
    _property_int_ex(SongInfo, lyricNum, _ex_args_all),          
    _property_array(SongInfo, lyric, lyric_ref_tbl, Lyric, lyricNum),   /* Lyric: type of array; lyricNum: property to save array size */
    _property_end()
};

/* description for ExtData */
reflect_item_t ext_data_ref_tbl[] = {
    _property_int(ExtData, a),
    _property_real(ExtData, b),
    _property_end()
};

/* description for PlayList */
reflect_item_t play_list_ref_tbl[] = {
    _property_string(PlayList, name),
    _property_string(PlayList, creater),
    _property_int_ex(PlayList, songNum, _ex_args_all),
    _property_array(PlayList, songList, song_ref_tbl, SongInfo, songNum),
    _property_obj(PlayList, extData, ext_data_ref_tbl),
    _property_end()
};
```

#### 2.2 方法2 通过注解方式，自动生成反射表
注解方法的好处是它是直接在c结构上进行声明，方便对照，不易出错。

注解方法：  
- @CSON_REF_START(CSON_REF_name)                  结构体注释开始  
- @CSON_REF(CSON_REF_field,CSON_REF_type)         结构体基本类型字段的注解声明  
- @CSON_REF_O(CSON_REF_field,CSON_REF_st_type)    结构体对象类型字段的注解声明   
- @CSON_REF_AN(CSON_REF_field)                    结构体数组字段大小的注解声明  
- @CSON_REF_A(CSON_REF_field,CSON_REF_type,CSON_REF_st_type,CSON_REF_st_num)  
                                                结构体数组字段的注释声明  
- @CSON_REF_END()                                 结构体注释结束  

    宏参数说明  
    CSON_REF_name           c结构体名字  
    CSON_REF_field          c结构体内的字段名  
    CSON_REF_type           c结构体字段对应的cson类型  
    CSON_REF_st_type        c结构体字段的c类型  
    CSON_REF_st_num         数组大小字段名  

举例：demo/test.h

```  
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

```  

生成C代码的反射表  

以demo/test.h为例
- 进入demo/ 目录
- 编译test.h  
```
    ../script/cson-c.sh test.h
```

则生成 test.h.cson_ref_tbl.c test.h.cson_ref_tbl.h  
即在输入的头文件之后，加后缀 .cson_ref_tbl.c .cson_ref_tbl.h  

test.h.cson_ref_tbl.h如下:  
  里面便是生成的c结构的反射表变量的声明了。
  反射表名以 cson_ref_tbl_XXX 形式定义。
```  
    /**
    * @file test.h.cson_ref_tbl.h 
    *   !!!AUTO GENERTAED BY ../script/cson-c.sh, DON'T EDIT
    *   define the cson reflect table for c structure.
    *   src_file:test.h
    * @date   2022-12-17
    */
    #ifndef __TEST_H_CSON_REF_TBL_H__
    #define __TEST_H_CSON_REF_TBL_H__
    #include "cson.h"

    extern reflect_item_t cson_ref_tbl_Lyric[];
    extern reflect_item_t cson_ref_tbl_SongInfo[];
    extern reflect_item_t cson_ref_tbl_ExtData[];
    extern reflect_item_t cson_ref_tbl_PlayList[];

    #endif
```

test.h.cson_ref_tbl.c如下：

```
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

```

- 将生成的test.h.cson_ref_tbl.c test.h.cson_ref_tbl.h加入makefile,即可使用。


### 3. 调用cson接口编解码Json。
``` c
PlayList playList;

/* Decode */
csonJsonStr2Struct(jStr, &playList, play_list_ref_tbl);
如果是注解方式定义的，则反射变量使用cson_ref_tbl_PlayList  

/* Encode */
char* jstrOutput;
csonStruct2JsonStr(&jstrOutput, &playList, play_list_ref_tbl);  
如果是注解方式定义的，则反射变量使用cson_ref_tbl_PlayList
```

## 限制
- 暂不支持多维数组。
- 默认使用Cjson库。如果需要使用jannson，请修改Makefile中的$(JSON_LIB)变量。
