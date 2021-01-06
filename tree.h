#ifndef TREE_H
#define TREE_H
// #define DEBUG 
struct Node {
void *data;
struct Node *lt; //left
struct Node *gte; //right
};

struct Performance {
unsigned int reads;
unsigned int writes;
unsigned int mallocs;
unsigned int frees;
};

// basic functions
struct Performance *newPerformance();
void attachNode( struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width );
int comparNode( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target );
struct Node **next( struct Performance *performance, struct Node **node_ptr, int direction );
void readNode( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width );
void detachNode( struct Performance *performance, struct Node **node_ptr );
int isEmpty( struct Performance *performance, struct Node **node_ptr );
// derived functions 
void addItem( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width );
void freeTree( struct Performance *performance, struct Node **node_ptr );
void readItem( struct Performance *performance, struct Node **node_ptr, void *target, void *dest, unsigned int width );
// last 20%
int searchItem( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width );
#endif // TREE_H
