#ifndef __CSON_DEMO_TEST2_H__
#define __CSON_DEMO_TEST2_H__

#include "cson.h"

typedef struct {                            //@CSON_REF_START(ClassInfoChild)
    char*       name;                       //@CSON_REF(name,string)
    char*       jump_url;                   //@CSON_REF(jump_url,string)
} ClassInfoChild;                           //@CSON_REF_END()

typedef struct {                            //@CSON_REF_START(ClassInfo)
    int         has_child;                  //@CSON_REF(has_child,int)
    char*       icon;                       //@CSON_REF(icon,string)
    int         id;                         //@CSON_REF(id,int)
    char*       name;                       //@CSON_REF(name,string)
    char        childrenNum;                //@CSON_REF_AN(childrenNum)
    ClassInfoChild*     children;           //@CSON_REF_A(children,object,ClassInfoChild,childrenNum)
} ClassInfo;                                //@CSON_REF_END()

typedef struct {                            //@CSON_REF_START(Data)            
    long long   timestamp;                  //@CSON_REF(timestamp,int)
    int      infoNum;                       //@CSON_REF_AN(infoNum)
    ClassInfo*  info;                       //@CSON_REF_A(info,object,ClassInfo,infoNum)
} Data;                                     //@CSON_REF_END()

typedef struct {                            //@CSON_REF_START(Response)      
    int         status;                     //@CSON_REF(status,int)
    Data        data;                       //@CSON_REF_O(data,Data)
    int         errcode;                    //@CSON_REF(errcode,int)
} Response;                                 //@CSON_REF_END()

#endif