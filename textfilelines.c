//
//  textfilelines.c
//  MSProxy
//
//  Created by 王鑫 on 2017/7/4.
//  Copyright © 2017年 wx. All rights reserved.
//

#include "textfilelines.h"
#include <stdlib.h>
#include <memory.h>



//
// 文本文件相关操作
//

/**
 * 设置一行文本，将会对数据进行拷贝
 */
void tfl_line_copy_data(listnode* node, char* data)
{
    if (!node || !data)
        return;
    if (!node->data)
    {
        node->data = text_new_copy_data(data);
    }
    else
    {
        text_copy_data((textdata*)node->data, data);
    }
}

/**
 * 创建一行文本，默认设置为空行。
 * 销毁节点时使用tfl_delete_node或tfl_free_list
 */
listnode* tfl_new_line()
{
    listnode* line = (listnode*)malloc(sizeof(listnode));
    memset(line, 0, sizeof(listnode));
    line->data = text_new_data();
    return line;
}

listnode* tfl_new_data_line(char* data)
{
    listnode* line = (listnode*)malloc(sizeof(listnode));
    memset(line, 0, sizeof(listnode));
    line->data = text_new_copy_data(data);
    return line;
}

/**
 * 读取文本文件，并用链表记录文本文件的每一行
 * @param file 具有读权限的文本文件指针
 * @return 链表头
 */
listnode* tfl_load_lines_f(FILE* file)
{
    char buf[4096];
    size_t read = 0;
    size_t curbuflen = 0;
    listnode* list = tfl_new_line();
    listnode* curnode = list;
    if (!file)
        return NULL;
    while (fgets(buf, 4096, file))
    {
        curbuflen = ftell(file) - read;
        read += curbuflen;
        text_append_data((textdata*)curnode->data, buf);
        if (buf[curbuflen-1] != '\n')
        {
            if (curbuflen == 4096)
                continue;
            else
                break;
        }
        else
        {
            ((textdata*)curnode->data)->data[curbuflen-1] = 0;
            curnode->next = tfl_new_line();
            curnode = curnode->next;
        }
    }
    return list;
}

/**
 * 保存文本文件
 */
void tfl_save_lines(listnode* list, FILE* file)
{
    textdata* text;
    if (!file)
        return;
    while (list->next)
    {
        text = (textdata*)list->data;
        fwrite(text->data, strlen(text->data), 1, file);
        fputc('\n', file);
        list = list->next;
    }
    text = (textdata*)list->data;
    fwrite(text->data, strlen(text->data), 1, file);
}

/**
 * 销毁整个链表
 * @param list 可以是链表中任一节点
 */
void tfl_delete_lines(listnode* list)
{
    listnode* curnode = list;
    if (!list)
        return;
    while (curnode->prev)
        curnode = curnode->prev;
    
    while (curnode)
    {
        list = curnode->next;
        text_free_data((textdata*)curnode->data);
        free(curnode);
        curnode = list;
    }
}

/**
 * 搜索字符串
 * @return 第一行找到的文本
 * @param index 输出参数，如果找到文本，输出文本首次出现的位置
 */
listnode* tfl_find_line(listnode* list, const char* searchstr, int* index)
{
    listnode* curnode = list;
    if (!list || !searchstr)
        return NULL;
    while (curnode)
    {
        textdata* text = (textdata*)curnode->data;
        if (text && text->data)
        {
            const char* substr = strstr(text->data, searchstr);
            if (substr)
            {
                if (index)
                    *index = (int)(substr - text->data);
                break;
            }
        }
        curnode = curnode->next;
    }
    return curnode;
}


