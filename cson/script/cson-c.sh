#!/bin/sh
#####################################
# @file: $0
# @brief
#    auto generate cson reflect table by CSON annotations
#           @CSON_REF_XXXX
#           
#    if want to check the macro preprocess result, plese run cmd like this:   
#           gcc -E -I ../inc/ test2.h.cson_ref_tbl.c -o  test2.h.cson_ref_tbl.s; cat test2.h.cson_ref_tbl.s | grep -v ^# > test2.h.cson_ref_tbl.S
# @author: huaguoqing
# @data  : 2022.12.17
#####################################
usage()
{
    echo "usage: $0 {IN_H_FILE} [OUTPUT_FILE]"
    echo "  if no param OUTPUT_FILE, will output to ${INF_FILE}.cson_ref_tbl.c"
}

#check param nums
if [ $# -lt 1 ] ;then
    usage
    exit 1
fi

in=$1
out=$2
#check if ${in} is a valid file.
if [ ! -f ${in} ] ;then
    usage
    exit 2
fi

default_output_c_file=${in}.cson_ref_tbl.c

if [ -z "${out}"];then
    out=${default_output_c_file}
fi

in_basename=`basename ${in}`
out_h=${out%.*}.h
out_h_basename=`basename ${out_h}`
out_h_basename_macro="__`echo -n ${out_h_basename} | tr '.'  '_' | tr '[:lower:]' '[:upper:]' `__"

cur_date=`date -Idate`
output=`cat ${in} |grep @CSON_REF|grep @CSON_REF|sed -e "s/.*@CSON_REF\(.*(.*)\)/CSON_REF\1/g;/CSON_REF_START/h;/CSON_REF_START/G;s/CSON_REF_START(\([^)]*\))/#define CSON_REF_NAME \1/;/CSON_REF_START/i#undef CSON_REF_NAME" `
output_h=`echo -n "${output}" |grep CSON_REF_START|sed -e "s/.*CSON_REF_START(\(.*\))/extern reflect_item_t cson_ref_tbl_\1[];/g"`

cat > ${out} <<EOF
/**
* @file ${out} 
*   !!!AUTO GENERTAED BY $0, DON'T EDIT
*   define the cson reflect table for c structure.
*   src_file:${in}
* @date   ${cur_date}
*/

#include "cson.h"
#include "${in_basename}"
#include "${out_h_basename}"

${output}
EOF

cat > ${out_h} <<EOF
/**
* @file ${out_h} 
*   !!!AUTO GENERTAED BY $0, DON'T EDIT
*   define the cson reflect table for c structure.
*   src_file:${in}
* @date   ${cur_date}
*/
#ifndef ${out_h_basename_macro}
#define ${out_h_basename_macro}
#include "cson.h"

${output_h}

#endif
EOF

