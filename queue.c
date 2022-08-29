/*
 * C 编程技能测试实验代码
 * 为课程预检验
 */

/*
 * 程序实现一个同时支持 FIFO 和 LIFO 的队列
 *
 * 使用单链表表示队列元素
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  创建空队列
  如果没有分配空间则返回 NULL
*/
queue_t *q_new()
{
  queue_t *q = (queue_t *)malloc(sizeof(queue_t)); /*创建空队列*/
  if (q == NULL)
  {
    return NULL; /*创建失败返回 NULL*/
  }
  q->head = NULL;
  q->tail = NULL;
  q->size = 0; /*初始化队列长度*/
  return q;
}

/*
  释放队列所用到的所有空间
  如果 q 为 NULL 则没有效果
*/
void q_free(queue_t *q)
{
  /* 如何释放链表元素和字符串 */
  /* 释放队列结构 */
  if (q == NULL)
  {
    return;
  }
  for (int i = 0; i < q->size; i++)
  {
    list_ele_t *l = q->head;
    q->head = q->head->next;
    if (l->value)
    {
      free(l->value); /*释放字符串空间*/
    }
    free(l); /*释放链表空间*/
  }
  free(q); /*释放队列空间*/
}

/*
  在队首插入一个元素
  成功则返回 true
  q 为 NULL 或者 无法分配空间则返回 false
  参数 s 指向待存储的字符串
  函数必须显式地分配空间并拷贝字符串到空间里面
 */
bool q_insert_head(queue_t *q, char *s)
{
  if (q == NULL)
  {
    return false;
  }
  list_ele_t *newh = (list_ele_t *)malloc(sizeof(list_ele_t)); /*插入节点申请空间*/
  if (newh == NULL)
  {
    return false;
  }
  newh->value = (char *)malloc(strlen(s) + 1); /*插入节点的value申请空间*/
  if (newh->value == NULL)
  {
    free(newh); /*value为NULL但是newh占有空间，一定要释放空间*/
    return false;
  }
  strcpy(newh->value, s); /*为节点的value赋值*/
  if (q->size == 0)
  {
    newh->next = NULL;
    q->head = newh;
    q->tail = newh;
  }
  else
  {
    newh->next = q->head;
    q->head = newh;
  }
  q->size++; /*长度加1*/
  return true;
}

/*
  在队尾插入一个元素
  成功则返回 true
  q 为 NULL 或者 无法分配空间则返回 false
  参数 s 指向待存储的字符串
  函数必须显式地分配空间并拷贝字符串到空间里面
 */
bool q_insert_tail(queue_t *q, char *s)
{
  if (q == NULL)
  {
    return false;
  }
  list_ele_t *newh = (list_ele_t *)malloc(sizeof(list_ele_t)); /*插入节点申请空间*/
  if (newh == NULL)
  {
    return false;
  }
  newh->value = (char *)malloc(strlen(s) + 1); /*插入节点的value申请空间*/
  if (newh->value == NULL)
  {
    free(newh); /*value为NULL但是newh占有空间，一定要释放空间*/
    return false;
  }
  strcpy(newh->value, s); /*为节点的value赋值*/
  if (q->size == 0)
  {
    newh->next = NULL;
    q->head = newh;
    q->tail = newh;
  }
  else
  {
    newh->next = NULL;
    q->tail->next = newh;
    q->tail = newh;
  }
  q->size++; /*长度加1*/
  return true;
}

/*
  移除队首元素Attempt to remove element from head of queue.
  成功则返回 true
  队列为 NULL 或者为 空 则返回 false
  如果 sp 非空 并移除了一个元素，则将移除的字符串拷贝给 *sp
  (至多 bufsize-1 个字符, 加上1个 null 结束符（'\0',0）)
  元素和字符串使用的空间需要释放
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  if (q == NULL || q->size == 0)
  {
    return false;
  }
  list_ele_t *t = q->head; /*临时指针*/
  q->head = q->head->next;
  t->next = NULL;
  if (sp != NULL)
  {
    strncpy(sp, t->value, bufsize - 1); /*拷贝字符串*/
    sp[bufsize - 1] = '\0'; /*字符串结束符*/
  }
  if (t->value != NULL)
  {
    free(t->value); /*释放空间*/
  }
  free(t);
  q->size--;
  return true;
}

/*
  返回队列的元素数量
  如果队列为 NULL 或者为 空 则返回 0
 */
int q_size(queue_t *q)
{
  /* 你需要为这个函数编写代码 */
  /* 记住: 函数时间复杂度为 O(1) */
  if (q == NULL)
  {
    return 0;
  }
  return q->size;
}

/*
  反转队列元素
  如果 q 为 NULL 则没有效果
  该函数不能直接或者间接调用其他函数为队列元素分配任何额外的空间
  (例如, 不能调用 q_insert_head, q_insert_tail, 或者 q_remove_head).
  应该是通过重排现有元素实现
 */
void q_reverse(queue_t *q)
{
  /* 你需要为这个函数编写代码 */
  if (q == NULL || q->size == 0)
  {
    return; /*队列为空直接结束函数*/
  }
  list_ele_t *a = q->head; /*记录反转前头指针*/
  list_ele_t *b = q->tail; /*记录反转前尾指针*/
  for (int i = 0; i < q->size - 1; i++)
  {
    list_ele_t *c = q->head; /*临时指针记录每一次循环的头指针*/
    q->head = q->head->next; 
    c->next = q->tail->next;
    q->tail->next = c;
  }
  q->head = b; /*头变尾*/
  q->tail = a; /*尾变头*/
}
