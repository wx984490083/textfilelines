//
//  textdata.c
//  MSProxy
//
//  Created by 王鑫 on 2017/7/5.
//  Copyright © 2017年 wx. All rights reserved.
//

#include "textdata.h"
#include <stdlib.h>
#include <memory.h>

textdata* text_new_data()
{
    textdata* text = (textdata*)malloc(sizeof(textdata));
    text->capacity = TXT_DEF_LEN+1;
    text->data = (char*)malloc(text->capacity);
    memset(text->data, 0, text->capacity);
    return text;
}

textdata* text_new_copy_data(char* data)
{
    size_t len = strlen(data);
    textdata* text = (textdata*)malloc(sizeof(textdata));
    if (len)
    {
        text->capacity = len+1;
    }
    else
    {
        text->capacity = TXT_DEF_LEN+1;
    }
    text->data = (char*)malloc(text->capacity);
    memset(text->data, 0, text->capacity);
    if (data)
        strcpy(text->data, data);
    return text;
}

void text_capacity(textdata* text, size_t capacity)
{
    char* tmp;
    if (!text)
        return;
    tmp = (char*)malloc(capacity);
    memset(tmp, 0, capacity);
    if (text->data)
    {
        if (capacity-1 < strlen(text->data))
        {
            memcpy(tmp, text->data, capacity-1);
        }
        else
        {
            strcpy(tmp, text->data);
        }
        free(text->data);
    }
    text->data = tmp;
    text->capacity = capacity;
}

void text_copy_data(textdata* text, char* data)
{
    size_t len = strlen(data);
    if (!text || !data)
        return;
    if (len+1 > text->capacity)
    {
        if (text->data)
        {
            free(text->data);
        }
        text->capacity = len+1;
        text->data = (char*)malloc(text->capacity);
        memset(text->data, 0, text->capacity);
    }
    strcpy(text->data, data);
}

void text_append_data(textdata* text, char* data)
{
    size_t textlen,datalen;
    if (!text || !data)
        return;
    textlen = strlen(text->data);
    datalen = strlen(data);
    if (textlen+datalen+1 > text->capacity)
    {
        size_t newcap = textlen+datalen+1;
        char* tmp = (char*)malloc(newcap);
        if (text->data)
        {
            strcpy(tmp, text->data);
            free(text->data);
        }
        text->capacity = newcap;
        text->data = tmp;
    }
    strcpy(text->data+textlen, data);
}

void text_replace_data(textdata* text, char* olddata, char* newdata)
{
    char* substr;
    char* findstr;
    int olddatalen;
    int newdatalen;
    if (!text || !olddata)
        return;
    
    olddatalen = (int)strlen(olddata);
    if (!olddatalen)
        return;
    newdatalen = (int)strlen(newdata);
    
    substr = text->data;
    if ((findstr = strstr(text->data, olddata)))
    {
        char* tmp;
        int totallen;

        int curdatalen = 0;
        if (newdatalen > olddatalen)
        {
            int textlen = (int)strlen(text->data);
            int maxreplacecount = textlen/olddatalen;
            int addlen = maxreplacecount*(olddatalen-newdatalen);
            totallen = textlen + addlen + 1;
        }
        else
        {
            totallen = (int)text->capacity;
        }
        tmp = (char*)malloc(totallen);
        memset(tmp, 0, totallen);
        if (findstr != substr)
        {
            memcpy(tmp+curdatalen, substr, findstr-substr);
            curdatalen += (findstr-substr);
        }
        if (newdatalen)
        {
            strcpy(tmp+curdatalen, newdata);
            curdatalen += newdatalen;
        }
        substr = findstr+olddatalen;
        while ((findstr = strstr(text->data, olddata)))
        {
            if (findstr != substr)
            {
                memcpy(tmp+curdatalen, substr, findstr-substr);
                curdatalen += (findstr-substr);
            }
            if (newdatalen)
            {
                strcpy(tmp+curdatalen, newdata);
                curdatalen += newdatalen;
            }
            substr = findstr+olddatalen;
        }
        free(text->data);
        text->data = tmp;
        text->capacity = totallen;
    }
}

void text_free_data(textdata* text)
{
    if (text)
    {
        if (text->data)
            free(text->data);
        free(text);
    }
}
