#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

struct node {
   int fromX, fromY;
   int toX, toY;
   unsigned int stencilIndex;
   int key;
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//display the list
void printList() {
   struct node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d,%d,%d,%d) : ",ptr->key,ptr->fromX,ptr->fromY,ptr->toX,ptr->toY,ptr->stencilIndex);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert link at the first location
void insertFirst(int key, int fromX, int fromY, int toX, int toY, unsigned int stencilIndex) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->fromX = fromX;
   link->fromY = fromY;
   link->toX = toX;
   link->toY = toY;
   link->stencilIndex = stencilIndex;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//delete first item
struct node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
struct node* findInList(int key) {

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}

//delete a link with given key
struct node* delete(int key) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}
/*
void sort() {

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;
	
   int size = length();
   k = size ;
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

         if ( current->data > next->data ) {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}*/

void reverse(struct node** head_ref) {
   struct node* prev   = NULL;
   struct node* current = *head_ref;
   struct node* next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   *head_ref = prev;
}

void resetList(){
    int len = length();
    int i;
    for(i = 1; i < len; i++){
        printf("%d", i);
        delete(i);
    }
}

int isInList(int fromX, int fromY, int toX, int toY, unsigned int stencilIndex){
    int len = length();
    int i = 0;
    printf("ISINLIST?");
    for(i = 0; i < len; i++){
        printf("%d", i);
        struct node *thisNode = findInList(i);
        if((thisNode->fromX == fromX) && (thisNode->fromY == fromY) && (thisNode->toX == toX) && (thisNode->toY == toY) && (thisNode->stencilIndex == stencilIndex)){
            return TRUE;
        }
    }
    return FALSE;
}