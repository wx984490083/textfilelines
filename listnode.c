//
//  listnode.c
//  MSProxy
//
//  Created by 王鑫 on 2017/7/5.
//  Copyright © 2017年 wx. All rights reserved.
//

#include "listnode.h"


/**
 * 在节点前面插入一个节点
 */
void list_append_node(listnode* curnode, listnode* newnode)
{
    if (!curnode || !newnode)
        return;
    if (curnode->prev)
    {
        curnode->prev->next = newnode;
    }
    newnode->prev = curnode->prev;
    newnode->next = curnode;
    curnode->prev = newnode;
}

/**
 * 在节点后面添加一个节点
 */
void list_insert_node(listnode* curnode, listnode* newnode)
{
    if (!curnode || !newnode)
        return;
    if (curnode->next)
    {
        curnode->next->prev = newnode;
    }
    newnode->next = curnode->next;
    newnode->prev = curnode;
    curnode->next = newnode;
}

/**
 * 从链表中移除一个节点，但不删除。
 * 不更其中next和prev属性。
 */
void list_remove_node(listnode* curnode)
{
    if (!curnode)
        return;
    if (curnode->prev)
    {
        curnode->prev->next = curnode->next;
    }
    if (curnode->next)
    {
        curnode->next->prev = curnode->prev;
    }
}

/**
 * 获取第一个节点
 */
listnode* list_get_first(listnode* curnode)
{
    if (!curnode)
        return NULL;
    while (curnode->prev)
        curnode = curnode->prev;
    return curnode;
}

/**
 * 获取最后的节点
 */
listnode* list_get_last(listnode* curnode)
{
    if (!curnode)
        return NULL;
    while (curnode->next)
        curnode = curnode->next;
    return curnode;
}
