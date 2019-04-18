/** **************************************************************************
 @Company
 LP Systems https://lpsystems.eu
 
 @File Name
 LL.h
 
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

#ifndef ll_h
#define ll_h

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct _LINKED_LIST {
    struct _LINKED_LIST *prev;
    struct _LINKED_LIST *next;
    void *data;
} LINKED_LIST_NODE;


void LL_Init(void) ;
LINKED_LIST_NODE * LL_CreateNew(void *data);
LINKED_LIST_NODE * LL_AppendNode(LINKED_LIST_NODE *ll, void *data);
LINKED_LIST_NODE * LL_AddNode(LINKED_LIST_NODE *node, void *data);
LINKED_LIST_NODE * LL_RemoveNode(LINKED_LIST_NODE *node);
LINKED_LIST_NODE * LL_GetNext(LINKED_LIST_NODE * node);
LINKED_LIST_NODE * LL_GetPrev(LINKED_LIST_NODE * node);
uint32_t LL_CountAllNode(LINKED_LIST_NODE *node);
uint32_t LL_CountUpperNode(LINKED_LIST_NODE *node);
uint32_t LL_CountLowerNode(LINKED_LIST_NODE *node);

void* my_malloc(size_t length);
void my_free(void* ptr);


#endif /* ll_h */
