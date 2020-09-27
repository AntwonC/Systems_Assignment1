#include <stddef.h>
#include "mymalloc.h"

typedef struct Node {
    int size;
    char inUse;
    struct Node* next;
} Node;

struct Node* list;  // First thing in char array, cast void pointer for any type
struct Node* lastFree = NULL;

// Need to check if our array[0] is empty. If it is, then initialize for the first malloc, if not ignore.
void initialize()   {
    list = (void*)&myblock[0];
    list->size = 4096 - sizeof(struct Node); // Need to subtract the size from a struct Node
    list->inUse = 'f'; // 'a' means allocated, 'f' means free. ( Not allocated yet )
    list->next = NULL; //to keep track of last free'd node, and prevent redundant freeing.
}
// Returns a pointer to the spot in memory
void* mymalloc(size_t numberOfBytes, char* file, int line){
    if (list == NULL){
        initialize();
    }

    struct Node* ptr = list;
    int memLocation = sizeof(struct Node);
    int unsaturated = 0;

    while(ptr != NULL){
        if(ptr->size > numberOfBytes+sizeof(struct Node) && ptr->inUse == 'f'){
            //newNode to split off with excess memory
            memLocation += numberOfBytes;
            struct Node* newNode = (void*)&myblock[memLocation];
            newNode->size = ptr->size - numberOfBytes-sizeof(struct Node);
            newNode->inUse = 'f';
            newNode->next = ptr->next;

            //change node being modified to return to user
            if(lastFree == ptr) lastFree = NULL;
            ptr->size = numberOfBytes;
            ptr->next = newNode;
            ptr->inUse = 'a';
            return &myblock[memLocation-numberOfBytes];
        }
        else if(ptr->size >= numberOfBytes && ptr->inUse == 'f'){
            if(lastFree == ptr) lastFree = NULL;
            ptr->inUse = 'a';
            return &myblock[memLocation];
        }
        else{
            if(ptr->inUse == 'f') unsaturated = 1;
            memLocation += ptr->size + sizeof(struct Node);
            ptr = ptr->next;
        }
    }
    //printmyblock();
    if(!unsaturated) fprintf(stderr, "Error in %s at line %d: Saturation of dynamic memory.\n", file, line);
    return NULL;
}

void myfree(void* ptr, char* file, int line){
    if(list == NULL){
        fprintf(stderr, "Error in %s at line %d: Pointer not allocated.\n", file, line);
        return;
    }
    struct Node* temp = list;
    struct Node* prev = NULL;
    struct Node* next = temp->next;
    int memLocation = sizeof(struct Node);

    while(next != NULL && &myblock[memLocation] != ptr){
        memLocation += temp->size + sizeof(struct Node);
        prev = temp;
        temp = next;
        next = temp->next;
    }
    if(next == NULL && &myblock[memLocation] != ptr){
        fprintf(stderr, "Error in %s at line %d: Pointer not allocated.\n", file, line);
        return;
    }
    else if(lastFree == temp){
        fprintf(stderr, "Error in %s at line %d: Redundant free.\n", file, line);
    }
    else{
        //make free
        temp->inUse = 'f';
        lastFree = temp;
        //stitch surrounding nodes back together (if not in use)
        if(next != NULL && next->inUse == 'f'){
            temp->size = temp->size + next->size + sizeof(struct Node);
            temp->next = next->next;
        }
        if(prev != NULL && prev->inUse == 'f'){
            prev->size = prev->size + temp->size + sizeof(struct Node);
            prev->next = temp->next;
        }
    }
	//printmyblock();
}
void printmyblock(){
    struct Node* ptr = list;
    while(ptr != NULL){
            printf("(%c|%d)>", ptr->inUse, ptr->size);
            ptr = ptr->next;
    }
    printf("\n");
}
