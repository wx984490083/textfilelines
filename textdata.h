//
//  textdata.h
//  MSProxy
//
//  Created by 王鑫 on 2017/7/5.
//  Copyright © 2017年 wx. All rights reserved.
//

#ifndef textdata_h
#define textdata_h

#include <stdio.h>

#define TXT_DEF_LEN 256

/**
 * 文本数据
 */
typedef struct textdata_t
{
    //字符串
    char* data;
    //内存分配大小
    size_t capacity;
}textdata;

textdata* text_new_data();
textdata* text_new_copy_data(char* data);
void text_capacity(textdata* text, size_t capacity);
void text_copy_data(textdata* text, char* data);
void text_append_data(textdata* text, char* data);
void text_replace_data(textdata* text, char* olddata, char* newdata);
void text_free_data(textdata* text);

#endif /* textdata_h */
