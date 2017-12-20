
//  sorted-list.c
//  Sorted-List
//
//  Created by Connor on 9/26/15.
//  Copyright (c) 2015 Connor. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "sorted-list.h"

SortedListPtr list;

int flag = 0;
struct node* createNode(char* data)
{
    /**
     0.Input Check
     1.Allocate space large enough for each of the fields
     2.Give initial values.
     3. Return
     **/
    if(data == NULL){
        printf("Error: Invalid Input for createNode\n");
        return NULL;
    }
    struct node* newNode = NULL;
    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->filehead = NULL;
    return newNode;
}

struct filenode* createFileNode(char* filename)
{
    /**
 *      0.Input Check
 *           1.Allocate space large enough for each of the fields
 *                2.Give initial values.
 *                     3. Return
 *                          **/
    if(filename == NULL){
        printf("Error: Invalid Input for createNode\n");
        return NULL;
    }
    struct filenode* newNode = NULL;
    newNode = (struct filenode*)malloc(sizeof(struct filenode));
    newNode->filename = filename;
    newNode->next = NULL;
    newNode->count = 1;
    return newNode;

}
void destroyNode(struct node* destroyMe)
{
    /**Destroy the node**/
    
}



SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
   

    SortedListPtr creation = (SortedListPtr)malloc(sizeof(SortedListPtr));
    creation->head = NULL;
    creation->comparator = compareChar;
    creation->destructionator = df;
       
    return creation;
    
}
/*
 * SLDestroy destroys a list, freeing all dynamically allocated memory.
 *
 * You need to fill in this function as part of your implementation.
 */
void SLDestroy(SortedListPtr list)
{
    struct node* curr;
    
    while(1) {
        curr = list->head;
        if(curr == NULL) {
            break;
        }
        list->head = list->head->next;
        free(curr);
    }
}
/*
 * SLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list.  If the new object is equal to an object
 * already in the list (according to the comparator function), then the operation should fail.
 *
 * If the function succeeds, it returns 1, otherwise it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

int SLInsert( char *newObj, char* filename)
{     
    if(list == NULL || newObj == NULL)
    {
        printf("Error: invalid input\n");
        return 0;
    }
    else if (flag== 0) {
	flag = 1;
 		
        list->head = createNode(newObj);
        struct filenode* newnode2= createFileNode(filename);
        list->head->filehead = newnode2;
        newnode2->count = 1;
        return 1;
    }
    
    else
    {
        
        return SLaddNode( newObj,filename);
        
    }
    
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
    /** 
     0. Valid input check
     1. Allocate memory
     2. Initialize Fields
     3. Return
     **/
    if(list == NULL || list->head == NULL){
        printf("Error: Invalid input for SLCreateIterator\n");
        return NULL;
    }
    SortedListIteratorPtr tempIter;
    tempIter = (SortedListIteratorPtr)malloc(sizeof(SortedListIteratorPtr));
    //tempIter->SortedList = list;
    tempIter->curr = list->head;
    //If we decide to keep the previous, should we set it INITIALLY to head also?

    return tempIter;
    
}
void SLDestroyIterator(SortedListIteratorPtr iter)
{
    free(iter);
    return;
}

int SLaddFileCount( char* filename, struct node* curr)
{   
      
      struct filenode* currFile = curr->filehead;

    
     
     while(currFile != NULL)
     { 
      int compare = compareChar(filename,currFile->filename);		
     
	if(compare == 0)
	{//TODO: Add sorting by count after you increase count.
	 
         currFile->count = currFile->count + 1;

     	return 1; 

	}else if (currFile->count >= 1)
	{ 
		
	    if(currFile->next == NULL)
	     {
                struct filenode* newnode2 = createFileNode(filename);
		currFile->next = newnode2;
		newnode2->count =1;
		return 1;
	     }
 	 currFile = currFile->next; 

	}
     } 
    return 1;
}
int SLaddNode(char *newObj, char* filename){
                      
    struct node* curr = list->head;
    struct node* prev = list->head;
    int compare;
    compare = compareChar(newObj,list->head->data);
 if(compare < 0) {


        struct node* newnode = createNode(newObj);
        newnode->next = curr;
        list->head = newnode;
        struct filenode* newnode2 = createFileNode(filename);
        newnode->filehead = newnode2;
        newnode2->count = 1;
        return 1;

    }else if (compare== 0){
    // printf("%s, %d", newObj, strcmp(newObj, list->head->data));   
   SLaddFileCount(filename,curr);    
          	        



        return 0; //TODO: implement when same character. Using filecount pointer
                  //Implement when only one node. on curr
    }
    else if (compare > 0 && list->head->next == NULL) {
        
	list->head->next = createNode(newObj);
        struct filenode* newnode2 = createFileNode(filename);
        list->head->next->filehead = newnode2;
        newnode2->count = 1;

        return 1;
        }
                       
    curr = list->head->next;
    prev = list->head;
    //int count = 0;
    while(1) {
        compare = compareChar(newObj, curr->data);
                //The case where the new object is greater than curr.
        if(compare < 0)
        {   
            struct node* newnode = createNode(newObj);
            newnode->next = curr;
            prev->next = newnode;
            struct filenode* newnode2 = createFileNode(filename);
            newnode->filehead = newnode2;
            newnode2->count = 1;
            return 1;
                                //The case where there exists the same number.
        }
    else if(compare == 0)
        { 
              
            SLaddFileCount(filename, curr);
            return 0;  //TODO: implement when same character. Using filecount pointer.
                       //Implement on curr.
                                
            
        }
    else if(curr->next == NULL)
        {
	        struct node* newnode = createNode(newObj);
        curr->next = newnode;
        struct filenode* newnode2 = createFileNode(filename);
        newnode->filehead = newnode2;
        newnode2->count = 1;
        return 1;
        }
                            
    prev = curr;
    curr = curr->next;
    }
                        
    return 0;
}
int compareChar(char* newObj, char* oldObj)
{
   int compare = strcmp(newObj,oldObj); 
   
   if(compare > 0){
//     printf("%s, %s, %d\n", newObj, oldObj,compare);
	   return 1;
    }
    else if(compare == 0){
//     printf("%s, %s, %d\n", newObj, oldObj,compare);
        return 0;
    }
    else if(compare < 0)
    {
// 	printf("%s, %s, %d\n", newObj, oldObj,compare);
        return -1;
    }
    return 2;
}
