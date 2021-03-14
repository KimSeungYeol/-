#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mainheader.h"
#include "delete_node.h"
#include "display_node.h"
#include "insert_node.h"




int main(void)

{

    NODE* head = NULL; // HEAD

 

    int mode1;

    char user_name[10];

    char user_number[10];

 

    while (1)

    {

        printf("////////////////////////////\n");

        printf("모드를 입력해주세요\n");

        printf("1번 : 추가\n");

        printf("2번 : 삭제\n");

        printf("3번 : 검색\n");

        printf("4번 : 전체보기\n");

        printf("0번 : 나가기\n");

        printf("////////////////////////////\n");

 

        scanf("%d", &mode1);

        

        if (mode1 == 1)

        {

            printf("이름과 학번을 입력해주세요 \n");

            printf("이름 :  ");

            scanf("%s", &user_name);

            printf("학번 :  ");

            scanf("%s", &user_number);

 

 

            insert_node(&head, user_name, user_number);

 

            continue;

 

 

        }

 

        if (mode1 == 2)

        {

            printf("삭제할 사람의 이름을 입력해주세요 \n");

            printf("이름 : ");

            scanf("%s", &user_name);

            delete_node(&head, user_name);

            continue;

 

 

        }

 

        if (mode1 == 3)

        {

            char temp[10];

            printf("학번 또는 이름을 입력하면 검색할수 있습니다.\n");

            printf("검색: ");

            scanf("%s", &temp);

 

            NODE* curr = head->next;

 

            while (curr != NULL)               // 포인터가 NULL이 아닐 때 계속 반복

            {

                if (!(strcmp(temp, curr->name))) {

                    printf("--> %s\n", curr->number);

                }

 

                if (!(strcmp(temp, curr->number))) {

                    printf("--> %s\n", curr->name);

                }

                curr = curr->next;             // 포인터에 다음 노드의 주소 저장

            }

 

 

 

        }

 

        if (mode1 == 4)

 

        {

            display_node(head);

            continue;

 

 

 

        }

 

        if (mode1 == 0)

        {

            printf("프로그램을 종료합니다. \n");

 

            NODE* curr = head->next;

 

            curr = head->next;      // 연결 리스트 순회용 포인터에 첫 번째 노드의 주소 저장

            while (curr != NULL)    // 포인터가 NULL이 아닐 때 계속 반복

            {

                NODE* next = curr->next;    // 현재 노드의 다음 노드 주소를 임시로 저장

                free(curr);                        // 현재 노드 메모리 해제

                curr = next;                       // 포인터에 다음 노드의 주소 저장

            }

 

            free(head);    // 머리 노드 메모리 해제

 

 

            break;

 

 

        }

 

 

 

 

    }


    return 0;

}
