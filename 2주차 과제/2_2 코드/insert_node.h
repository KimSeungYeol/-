#ifndef _INSERT_NODE_
#define _INSERT_NODE_

#include "mainheader.h"

/*

    insert_node( NODE **, int)

    insert a key on the back of the linked list.

*/

void insert_node(NODE** n, char data1[10], char data2[10])

{

    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    NODE* temp = *n;

 

    new_node->next = NULL;

    new_node->prev = NULL;

    strcpy(new_node->name, data1);

    strcpy(new_node->number, data2);

 

 

    printf("INSERT [%s, %s]\n", data1, data2);

 

    // there is not any node.

    if (temp == NULL)

    {

        *n = new_node;

 

        return;

    }

 

    // find the last node in the linked list.

    while (temp->next != NULL)

    {

        temp = temp->next;

    }

 

    temp->next = new_node;

    new_node->prev = temp;

}

 

#endif


