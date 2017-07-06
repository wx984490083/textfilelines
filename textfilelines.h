//
//  textfilelines.h
//  MSProxy
//
//  Created by 王鑫 on 2017/7/4.
//  Copyright © 2017年 wx. All rights reserved.
//

#ifndef textfilelines_h
#define textfilelines_h

#include <stdio.h>
#include "listnode.h"
#include "textdata.h"

//
// 文本文件相关操作
//

/**
 * 设置节点的数据
 */
void tfl_line_copy_data(listnode* node, char* data);

/**
 * 创建一行文本，默认设置为空行。
 * 销毁节点时使用tfl_delete_node或tfl_free_list
 */
listnode* tfl_new_line();

/**
 * 根据数据创建一个节点；
 * 销毁节点时使用tfl_delete_node或tfl_free_list
 */
listnode* tfl_new_data_line(char* data);

/**
 * 读取文本文件，并用链表记录文本文件的每一行
 * @return 链表头
 */
listnode* tfl_load_lines_f(FILE* file);

/**
 * 保存文本文件
 */
void tfl_save_lines(listnode* list, FILE* file);

/**
 * 销毁整个文本链表
 * @param list 可以是链表中任一节点
 */
void tfl_delete_lines(listnode* list);


/**
 * 搜索字符串
 * @return 第一行找到的文本
 * @param index 输出参数，如果找到文本，输出文本首次出现的位置
 */
listnode* tfl_find_line(listnode* list, const char* searchstr, int* index);


#endif /* textfilelines_h */
