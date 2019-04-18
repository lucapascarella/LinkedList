//
//  main.c
//  LinkedList
//
//  Created by Luca Pascarella on 4/10/19.
//  Copyright © 2019 Luca Pascarella. All rights reserved.
//

#include <stdio.h>
#include "ll.h"

int main(int argc, const char * argv[]) {
    char test1[] = "1 ";
    char test2[] = "2 ";
    char test3[] = "3 ";
    char test4[] = "4 ";
    char test5[] = "5 ";
    
    LL_Init();
    
    LINKED_LIST_NODE *head = LL_AppendNode(NULL, test1);
    LINKED_LIST_NODE *node2 = LL_AppendNode(head, test2);
    LINKED_LIST_NODE *node3 = LL_AppendNode(head, test3);
    LINKED_LIST_NODE *node4 = LL_AppendNode(node2, test4);
    LINKED_LIST_NODE *node5 = LL_AppendNode(head, test5);
    LINKED_LIST_NODE *prev = LL_RemoveNode(node2);
    node2 = LL_AddNode(head, test2);
    
    printf("Count: %d\n", LL_CountAllNode(node4));
    
    LINKED_LIST_NODE *node = head;
    do {
        printf("%s \n", node->data);
    } while((node = LL_GetNext(node)) != NULL);
    
    return 0;
}
