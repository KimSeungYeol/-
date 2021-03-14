#ifndef _DELETE_NODE_
#define _DELETE_NODE_

#include "mainheader.h"

/*

    delete_node( NODE **, int)

    delete the key that you want from the linked list.

    if the key is removed, this function will return 0.

    if it is not, this function will return -1.

*/

int delete_node(NODE** n, char data1[10])

{

    NODE* temp = *n;

    NODE* f = NULL;

 

    printf("DELETE [%s]\n", data1);

 

    // if the key that you want to remove is located firstly.

    if (    strcmp(  (*n)->name  , data1)==0)

    {

        if ((*n)->next != NULL)

        {

            *n = (*n)->next;

 

            (*n)->prev = NULL;

        }

        else

        {

            *n = NULL;

        }

 

        free(temp);

 

        return 0;

    }

 

    while (temp->next != NULL)

    {

        // if find the key that you want to remove

        if (     strcmp(    (temp->next)->name , data1)==0)

        {

            f = temp->next;

 

            temp->next = (temp->next)->next;

            (temp->next)->prev = temp;

 

            free(f);

 

            return 0;

        }

 

        temp = temp->next;

    }

 

    printf("Can't find the key!\n");

 

    return -1;

}

#endif
