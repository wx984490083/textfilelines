//
//  listnode.h
//  MSProxy
//
//  Created by 王鑫 on 2017/7/5.
//  Copyright © 2017年 wx. All rights reserved.
//

#ifndef listnode_h
#define listnode_h

#include <stdio.h>

/**
 * 双向链表节点
 */
typedef struct listnode_t
{
    void* data;
    struct listnode_t* prev;
    struct listnode_t* next;
}listnode;

/**
 * 在节点前面插入一个节点
 */
void list_append_node(listnode* curnode, listnode* newnode);

/**
 * 在节点后面添加一个节点
 */
void list_insert_node(listnode* curnode, listnode* newnode);

/**
 * 从链表中移除一个节点，但不删除。
 * 不更其中next和prev属性。
 */
void list_remove_node(listnode* curnode);

/**
 * 获取第一个节点
 */
listnode* list_get_first(listnode* curnode);

/**
 * 获取最后的节点
 */
listnode* list_get_last(listnode* curnode);

#endif /* listnode_h */
