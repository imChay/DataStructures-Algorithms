//
//  main.m
//  数据结构和算法
//
//  Created by cy on 2017/3/13.
//  Copyright © 2017年 cy. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
/*
 关键点：如何创建一个链表：需要一个头指针、尾指针
 */

typedef struct node {
    int data;
    struct node *next;
}Node;
//typedef struct node Node;  //typedef为C语言的关键字，作用是为一种数据类型定义一个新名字。
//使用typedef目的一般有两个，一个是给变量一个易记且意义明确的新名字，另一个是简化一些比较复杂的类型声明。

Node *create(void);                             //创建链表
Node *createTest(void);
void insert(Node *head,Node *pnew,int i);   //插入链表
void pdelete(Node *head,int i);             //删除列表
void display(Node *head);                   //输出链表
void Pfree(Node *head);                     //销毁链表

Node *reverseNodeList(Node *head);          //链表反转

#pragma mark - main

int main(int argc, char *argv[]) {
    
    // ======= 创建 =======
    struct node *head;
    head = createTest();
    if (head == NULL)
        return 0;
    printf("输出创建的链表：\n");
    display(head);
    
    display(reverseNodeList(head));
    
    // ======= 插入 =======
    //    struct node *pnew;
    //    pnew = (Node *)malloc(sizeof(Node));
    //    if (pnew == NULL) {
    //        printf("创建失败！");
    //        return 0;
    //    }
    //    pnew->data = 88;
    //    insert(head,pnew, 3);   //将新节点插入节点3的后面
    //    printf("插入后的链表：");
    //    display(head);
    
    // ======= 删除 =======
//    pdelete(head,3);   //删除节点3
//    printf("删除后的链表：");
//    display(head);
//    Pfree(head);
    
    return 0;
}

struct node *create() {
    
    // 1、创建头指针，尾指针
    Node *head,*tail;
    
    // 2、创建头节点（指针域赋值为NULL,头指针赋值给尾指针）
    head = (Node *)malloc(sizeof(Node));  //创建头节点。
    if (head == NULL) { //创建失败返回
        printf("创建失败！");
        return NULL;
    }
    head->next = NULL;  //头节点指针域置NULL
    tail = head;        // 开始时尾指针指向头节点
    
    // 3、创建新节点，并给数据域赋值，指针域赋值为NULL；
    //    将新节点加入到链表-尾指针的next指向新节点，更新尾指针-将尾指针赋值为新节点
    int data;
    Node *pnew;
    printf("输入数据：");
    while (1) {      //创建链表
        scanf("%d",&data);
        if (data<0)    //成绩为负是退出循环
            break;
        pnew = (Node *)malloc(sizeof(Node));  //创建新节点
        if (pnew == NULL) { //创建失败返回
            printf("创建失败！");
            return NULL;
        }
        pnew->data = data;      //新节点数据域存放输入的成绩
        pnew->next = NULL;      //新节点指针域置NULL
        tail->next = pnew;      //新节点插入到表尾
        tail = pnew;            //为指针指向当前的尾节点
    }
    return head;  //返回创建链表的头指针
}

Node* createTest(void){
    
    Node *head,*tail;
    
    printf("请输入节点数据，负数代表结束输入：");
    int input;
    Node *pNew;
    while (1) {
        scanf("%d",&input);
        if (input < 0) {
            break;
        }
        
        if (head == NULL) {
            head = (Node*)malloc(sizeof(Node));
            head->data = input;
            head->next = NULL;
            tail = head;
        }else{
            pNew = (Node*)malloc(sizeof(Node));
            pNew->data = input;
            pNew->next = NULL;
            
            tail->next = pNew;
            tail = pNew;
        }
    }
    
    return head;
}

void insert(Node *head,Node *pnew,int i) {
    Node *p; //当前指针
    int j;
    
    p=head;
    for (j=0; j<i&&p!=NULL; j++) //p指向要插入的第i个节点
        p=p->next;
    
    if (p==NULL) { //节点i不存在
        printf("与插入的节点不存在！");
        return;
    }
    
    pnew->next=p->next;   //插入节点的指针域指向第i个节点的后继节点
    p->next=pnew;    //犟第i个节点的指针域指向插入的新节点
}

void pdelete(Node *head,int i) {
    Node *p,*q;
    int j;
    if (i==0) //删除的是头指针，返回
        return;
    p=head;
    for (j=1; j<i&&p->next!=NULL; j++)
        p=p->next;  //将p指向要删除的第i个节点的前驱节点
    if (p->next==NULL) { //表明链表中的节点不存在
        printf("不存在！");
        return;
    }
    q=p->next;  //q指向待删除的节点
    p->next=q->next;  //删除节点i，也可写成p->next=p->next->next
    free(q);   //释放节点i的内存单元
}

void display(Node *head) {
    Node *p;
    for (p=head; p!=NULL; p=p->next){
        printf("%d ",p->data);
    }
    printf("\n");
}

void pfree(Node *head) {
    Node *p,*q;
    
    p=head;
    while (p->next!=NULL) { //每次删除头节点的后继节点
        q=p->next;
        p->next=q->next;
        free(q);
    }
    free(head);   //最后删除头节点
}

#pragma mark - 单链表反转

Node *reverseNodeList(Node *head){
    
    Node  *currentP,*behindP,*preP;
    
    currentP = head;
    behindP = NULL;
    
    while (1) {
        preP = currentP->next; // 保存反转前的下一个节点
        
        currentP->next = behindP;// 反转
        
        if (preP == NULL) {
            break;
        }
        behindP = currentP; // behindP和currentP移位
        currentP = preP;
    }
    
    return currentP;
}
