#ifndef _DISPLAY_NODE_
#define _DISPLAY_NODE_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainheader.h"


 

/*

    display_node( NODE *)

    display all node in the linked list.

*/

void display_node(NODE* n)

{

    NODE* temp = n;

    NODE* p = NULL;

 

    printf("HEAD > \n");

 

    // print all nodes from the left to the right.

    while (temp != NULL)

    {

        printf("이름 : %s \n", temp->name);

        printf("학번 : %s \n", temp->number);

        printf("\n");

 

 

 

        p = temp;

        temp = temp->next;

    }

 
}


#endif
