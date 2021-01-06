#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

struct Performance *newPerformance(){
   struct Performance *perf; 
   perf = (struct Performance*) malloc(sizeof(struct Performance));
   // check if array is not empty, set reads, write, mallocd and frees to zero 
   if(perf != 0){
       perf->reads = 0;
       perf->writes = 0;
       perf->mallocs = 0;
       perf->frees = 0;
   }
   else {
       printf("Make newPreformance Error! Malloc Fail!\n");
       exit(0);
   }
    return perf;
}
// add node to a pointer 
void attachNode( struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width ){
   if(node_ptr == 0){
        printf("attachNode Error! Malloc Fail!\n");
        exit(0);
   }
    // allocate space in memory and set variables to null
    int i = 0;
    struct Node *newNode;
    newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = malloc(width);
    
    // copy width bytes of data from the parameter src to the variable data in the new Node
    for (i = 0; i < width; i++){
        ((unsigned char*)newNode->data)[i] = ((unsigned char*) src)[i];
    }

    newNode->lt = NULL;
    newNode->gte = NULL;
    (*node_ptr) = newNode;

    // increment writes and mallocs 
    performance->writes++;
    performance->mallocs++;
}

int comparNode( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target ){
    int result = 0;
    void* dest;
    // allocate memory
    if (!isEmpty(performance,node_ptr)) 
    {   
        dest = (*node_ptr)->data;
        result = (*compar)(target,dest);
    } 
    performance->reads++;
   return result;
}
//determine the next node in the tree to visit
struct Node **next( struct Performance *performance, struct Node **node_ptr, int direction ){
   // check if list is empty then exit
    if(isEmpty(performance,node_ptr)){
        printf("Next Function Error!! empty list\n");
        exit(1);
    } else {
        // get pointer to the pointer to the second item in a list.
        if(direction < 0){
            node_ptr = &((*node_ptr)->lt);
        } else {
            node_ptr = &((*node_ptr)->gte);
        }
    }
    performance->reads++;
   return node_ptr;
}
void readNode( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width ){
  int i = 0;
    struct Node *newNode = *node_ptr;
    if(node_ptr == 0){
        printf("readNode Error! Malloc Fail!\n");
        exit(0);
    }

    // copy width bytes of data from the parameter src to the variable data in the new Node
    for (i = 0; i < width; i++){
        ((char*)dest)[i] = ((char*)newNode->data)[i];
    }
    
    // increment reads
    performance->reads++;

}
//Remove an item from a tree consisting of only one node
void detachNode( struct Performance *performance, struct Node **node_ptr ){
    if(!isEmpty(performance,node_ptr)){
        free((*node_ptr)->data);
        free(*node_ptr);
        (*node_ptr) = NULL;
    } 
    else {
        printf("detachNode Error! tree is empty!!\n");
        exit(0);
    }
    performance->frees++;
}
int isEmpty( struct Performance *performance, struct Node **node_ptr ){

    return ((*node_ptr) == NULL) ? 1: 0;
}

void addItem( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width ){
    int result = 0;
    while(!isEmpty(performance,node_ptr)){
        result = comparNode(performance,node_ptr,compar,src);
        node_ptr = next(performance,node_ptr,result);
    }
    attachNode(performance,node_ptr, src, width);
}
// free the whole tree
void freeTree( struct Performance *performance, struct Node **node_ptr ){
    if(!isEmpty(performance,node_ptr)){
        freeTree(performance,next(performance,node_ptr,-1));
        freeTree(performance,next(performance,node_ptr,1));
        detachNode(performance,node_ptr);
    }
}
int searchItem( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width ){

    while(!isEmpty(performance,node_ptr)){        
        int result = comparNode(performance,node_ptr,compar,target);
        if (result < 0 || result > 0) {
        // Visit left, or right depending on direction specified, repeat
            node_ptr = next(performance,node_ptr,result);

        }
        else {
            readNode(performance,node_ptr,target,width);
            return 1;
        }
    }

    return 0;
}
