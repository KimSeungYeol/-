#ifndef MANAGE_STUDENT_H
#define MANAGE_STUDENT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node {

    char name[10];            // 데이터를 저장할 멤버

    char number[10];            // 데이터를 저장할 멤버

    struct node* prev;

    struct node* next;

}NODE;

void insert_node(NODE** n, char data1[10], char data2[10]);

int delete_node(NODE** n, char data1[10]);

void display_node(NODE* n);



#endif


