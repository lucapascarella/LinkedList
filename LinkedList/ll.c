/** **************************************************************************
 @Company
 LP Systems https://lpsystems.eu
 
 @File Name
 LL.c
 
 @Author
 Luca Pascarella https://lucapascarella.com
 
 @Summary
 This files implement a linked list in C standard programming language.
 
 @Description
 This file contains the implementation of a custom linked list designed for low-end MCUs.
 
 @License
 Copyright (C) 2019 LP Systems
 
 Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 https://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software distributed under the License
 is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 or implied. See the License for the specific language governing permissions and limitations under
 the License.
 ************************************************************************** */

#include "ll.h"

static LINKED_LIST_NODE *gll;

/****************************************************************************
 Function:
 void LL_Init(void)
 Description:
 This function initialize a linked list
 Precondition:
 None
 Parameters:
 None
 Returns:
 None
 ***************************************************************************/
void LL_Init(void) {
    gll = my_malloc(sizeof(LINKED_LIST_NODE));
    gll->prev = NULL;
    gll->next = NULL;
    gll->data = 0x00;
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_CreateNew(void *data)
 Description:
 This function creates a new list and iniialize with the given data
 Precondition:
 LL_Init() must be called
 Parameters:
 A void pointer to user data
 Returns:
 A pointer to the created node
 ***************************************************************************/
LINKED_LIST_NODE * LL_CreateNew(void *data) {
    // Create and initialize a new linked list
    LINKED_LIST_NODE *node = my_malloc(sizeof(LINKED_LIST_NODE));
    node->prev = NULL;
    node->next = NULL;
    node->data = data;
    // Append this object to the global tracker
    if (LL_AppendNode(gll, node))
        return node;
    my_free(node);
    return NULL;
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_AppendNode(LINKED_LIST_NODE *node, void *data)
 Description:
 This function appends a new user data to a given list,
 if the linked list is NULL a new one will be created
 Precondition:
 LL_Init() must be called
 Parameters:
 node a linked list node
 data a void pointer to user data
 Returns:
 A pointer to the created node
 ***************************************************************************/
LINKED_LIST_NODE * LL_AppendNode(LINKED_LIST_NODE *node, void *data)  {
    if (node != NULL) {
        // Get last element of the queue
        LINKED_LIST_NODE * last;
        do {
            last = node;
        } while((node = LL_GetNext(node)) != NULL);
        node = last;
    }
    
    // Create and initialize a new linked list
    LINKED_LIST_NODE *new = my_malloc(sizeof(LINKED_LIST_NODE));
    
    if (new != NULL) {
        new->data = data;
        new->prev = node;
        if (node != NULL) {
            new->next = node->next;
            if (node->next != NULL)
                node->next->prev = new;
            node->next = new;
        } else {
            new->next = NULL;
        }
    }
    return new;
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_AddNode(LINKED_LIST_NODE *node, void *data)
 Description:
 This function adds a new user data to a given list,
 if the linked list is NULL a new one will be created
 Precondition:
 LL_Init() must be called
 Parameters:
 node a linked list node
 data a void pointer to user data
 Returns:
 A pointer to the created node
 ***************************************************************************/
LINKED_LIST_NODE * LL_AddNode(LINKED_LIST_NODE *node, void *data) {
    // Create and initialize a new linked list
    LINKED_LIST_NODE *new = my_malloc(sizeof(LINKED_LIST_NODE));
    
    if (new != NULL) {
        new->data = data;
        new->prev = node;
        if (node != NULL) {
            new->next = node->next;
            if (node->next != NULL)
                node->next->prev = new;
            node->next = new;
        } else {
            new->next = NULL;
        }
    }
    return new;
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_RemoveNode(LINKED_LIST_NODE *node)
 Description:
 This function removes the user data to a given list
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 A pointer to the next node, if exists
 ***************************************************************************/
LINKED_LIST_NODE * LL_RemoveNode(LINKED_LIST_NODE *node) {
    LINKED_LIST_NODE *prev = node->prev;
    LINKED_LIST_NODE *next = node->next;
    
    if (prev != NULL) {
        prev->next = next;
    }
    
    if (next != NULL) {
        next->prev = prev;
    }
    
    my_free(node);
    
    return next;
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_GetNext(LINKED_LIST_NODE * node)
 Description:
 This function returns next linked list node
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 A pointer to the next node, if exists
 ***************************************************************************/
LINKED_LIST_NODE * LL_GetNext(LINKED_LIST_NODE * node) {
    if (node != NULL)
        return node->next;
    return NULL;
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_GetPrev(LINKED_LIST_NODE * node)
 Description:
 This function returns previous linked list node
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 A pointer to the previous node, if exists
 ***************************************************************************/
LINKED_LIST_NODE * LL_GetPrev(LINKED_LIST_NODE * node) {
    if (node != NULL)
        return node->prev;
    return NULL;
}

/****************************************************************************
 Function:
 uint32_t LL_CountAllNode(LINKED_LIST_NODE *node)
 Description:
 This function counts all nodes of a linked list
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 The number of nodes inside a linked list
 ***************************************************************************/
uint32_t LL_CountAllNode(LINKED_LIST_NODE *node) {
    return LL_CountUpperNode(node) + LL_CountLowerNode(node);
}

/****************************************************************************
 Function:
 uint32_t LL_CountUpperNode(LINKED_LIST_NODE *node)
 Description:
 This function counts all uppper nodes of a linked list
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 The number of upper nodes inside a linked list
 ***************************************************************************/
uint32_t LL_CountUpperNode(LINKED_LIST_NODE *node) {
    uint32_t count = 0;
    if (node != NULL) {
        do {
            count++;
        } while((node = LL_GetPrev(node)) != NULL);
    }
    return count;
}

/****************************************************************************
 Function:
 uint32_t LL_CountLowerNode(LINKED_LIST_NODE *node)
 Description:
 This function counts all lower nodes of a linked list
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 The number of lower nodes inside a linked list
 ***************************************************************************/
uint32_t LL_CountLowerNode(LINKED_LIST_NODE *node) {
    uint32_t count = 0;
    if (node != NULL) {
        do {
            count++;
        } while((node = LL_GetNext(node)) != NULL);
    }
    return count;
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_Push(LINKED_LIST_NODE *node, void *data)
 Description:
 This function adds an element to the bottom of the linked list
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 Return the added node in the linked list
 ***************************************************************************/
LINKED_LIST_NODE * LL_Push(LINKED_LIST_NODE *node, void *data) {
    return LL_AppendNode(node, data);
}

/****************************************************************************
 Function:
 LINKED_LIST_NODE * LL_Pop(LINKED_LIST_NODE *node, void *data)
 Description:
 This function rmeoves an element from the top of the linked list
 Precondition:
 LL_Init() must be called and a linked list must be created
 Parameters:
 node a linked list node
 Returns:
 Return the removed node in the linked list
 ***************************************************************************/
void * LL_Pop(LINKED_LIST_NODE *node) {
    if (node != NULL) {
        // Get first element of the queue
        LINKED_LIST_NODE * prev;
        do {
            prev = node;
        } while((node = LL_GetNext(node)) != NULL);
        LL_RemoveNode(node);
        return prev;
    }
    return NULL;
}

void* my_malloc(size_t length) {
    return malloc(length);
}

void my_free(void* ptr) {
    return free(ptr);
}
