/**
* @file test2.h.cson_ref_tbl.c 
*   !!!AUTO GENERTAED BY ../script/cson-c.sh, DON'T EDIT
*   define the cson reflect table for c structure.
*   src_file:test2.h
* @date   2022-12-17
*/

#include "cson.h"
#include "test2.h"
#include "test2.h.cson_ref_tbl.h"

#undef CSON_REF_NAME
#define CSON_REF_NAME ClassInfoChild
CSON_REF_START(ClassInfoChild)
CSON_REF(name,string)
CSON_REF(jump_url,string)
CSON_REF_END()
#undef CSON_REF_NAME
#define CSON_REF_NAME ClassInfo
CSON_REF_START(ClassInfo)
CSON_REF(has_child,int)
CSON_REF(icon,string)
CSON_REF(id,int)
CSON_REF(name,string)
CSON_REF_AN(childrenNum)
CSON_REF_A(children,object,ClassInfoChild,childrenNum)
CSON_REF_END()
#undef CSON_REF_NAME
#define CSON_REF_NAME Data            
CSON_REF_START(Data)            
CSON_REF(timestamp,int)
CSON_REF_AN(infoNum)
CSON_REF_A(info,object,ClassInfo,infoNum)
CSON_REF_END()
#undef CSON_REF_NAME
#define CSON_REF_NAME Response      
CSON_REF_START(Response)      
CSON_REF(status,int)
CSON_REF_O(data,Data)
CSON_REF(errcode,int)
CSON_REF_END()
