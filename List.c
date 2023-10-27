#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node curser;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = N->prev =  NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List Q;
   Q = malloc(sizeof(ListObj));
   assert( Q!=NULL );
   Q->front = Q->back = Q->curser = NULL;
   Q->length = 0;
   Q->index = -1;
   return(Q);
}

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
// Function to free memory for the entire list and set the list reference to NULL
void freeList(List* pQ) {
    if (pQ != NULL && *pQ != NULL) {
        while ((*pQ)->front != NULL) {
            Node temp = (*pQ)->front;
            (*pQ)->front = (*pQ)->front->next;
            freeNode(&temp);
        }
        free(*pQ);
        *pQ = NULL;
    }
}


// Access functions -----------------------------------------------------------

// getLength()
// Returns the length of Q.
int length(List Q){
   if( Q==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(Q->length);
}

//returns index of curser element of list
int index(List L){
    if(L->curser != NULL){
        return L->index;
    }
   //if curser wasnt found return -1
   return -1;
}

// Returns front element of L. Pre: length()>0
int front(List L){
   if (L->length<=0){
      printf("List error: Length of List is 0 so there is no front");
      exit(EXIT_FAILURE);
   }
   return L->front->data;
}

// Returns back element of L. Pre: length()>0
int back(List L){
   if (L->length<=0){
      printf("List error: Length of List is 0 so there is no back");
      exit(EXIT_FAILURE);
   }
   return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
   if (L->length<=0 || index(L)<0){
      printf("List error: Cannot get curser, length of list is 0 or index of curser element is less than 0");
      exit(EXIT_FAILURE);
   }
   return L->curser->data;
}

// Returns true iff Lists A and B are in same
// state, and returns false otherwise.
bool equals(List A, List B){
    //traverse both lists making sure each node value is the same
    Node currentA = A->front;
    Node currentB = B->front;
    while(currentA && currentB){
        if(currentA->data!=currentB->data){
            return 0;
        }
        currentA = currentA->next;
        currentB = currentB->next;
    }
    //if both values are now Null then the lists were equal
    if(!currentA &&  !currentB){
        return 1;
    }
    return 0;
}


// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L){
    //traverse all nodes and free them
    while(L->front!=NULL){
        Node temp = L->front;
        L->front = L->front->next;
        freeNode(&temp);
    }
    L->length = 0;
    L->index = -1;
    L->back = L->curser = NULL;
}

// Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
 void set(List L, int x){
    if(length(L)<=0 || index(L)<0){
        fprintf(stderr, "List error: cannot set curser because the list is too small or the given index is too small.");
        exit(EXIT_FAILURE);
    }
    //set the data value of the curser to x
    L->curser->data = x;
 }

// If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L){
    if (length(L)>0){
        L->curser = L->front;
        L->index = 0;
    }
    //set index value of curser
    L->index = 0;
}

// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L){
    if (length(L)>0){
        L->curser = L->back;
        L->index = length(L)-1;
    }
    //set index value of curser
    L->index = L->length-1;
}

// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L){
   if (L == NULL || L->curser == NULL) {
        fprintf(stderr, "List Error: calling movePrev on NULL list reference or an undefined curser.\n");
        exit(EXIT_FAILURE);
    }
    if(L->curser!=NULL){
        if(L->curser==L->front){
            //set curser and index to undefined
            L->curser = NULL;
            L->index = -1;
        }
        else{
            L->curser = L->curser->prev;
            L->index--;
        }
    }
}

// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L) {
    if (L == NULL || L->curser == NULL) {
        fprintf(stderr, "List Error: calling moveNext on NULL list reference or an undefined curser.\n");
        exit(EXIT_FAILURE);
    }
    //if curser is already at the back of the List
    if (L->curser == L->back) {
        //set curser and index to undefined
        L->curser = NULL;
        L->index = -1;
    } else {
        L->curser = L->curser->next;
        L->index++;
    }
    
}


// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, int x){
    if( L==NULL ){
      fprintf(stderr, "List Error: calling prepend on NULL list reference\n");
      exit(EXIT_FAILURE);
   }
    Node new = newNode(x);

    if (new == NULL) {
        fprintf(stderr, "List Error: failed to allocate memory for a new node\n");
        exit(EXIT_FAILURE);
    }
    if(length(L)==0){
        L->front = L->back = new;
    }
    else{
        L->front->prev = new;
        new->next = L->front;
        L->front = new;
    }
    //increment length and index if curser is defined
    if(L->curser!=NULL){
        L->index++;
    }
    L->length++;
}

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append on NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    Node new = newNode(x);
    if (new == NULL) {
        fprintf(stderr, "List Error: failed to allocate memory for a new node\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 0) {
        L->front = L->back = new;
    } else {
        L->back->next = new;
        new->prev = L->back;
        L->back = new;
    }
    // Increment length
    L->length++;
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    if(L->length<=0 || index(L)<0){
        fprintf(stderr, "List Error: failed to add a node before curser\n");
        exit(EXIT_FAILURE);
    }
    Node new = newNode(x);
    if (new == NULL) {
        fprintf(stderr, "List Error: failed to allocate memory for a new node\n");
        exit(EXIT_FAILURE);
    }
    if(index(L)==0){
        prepend(L, x);
    }
    else{
        Node temp = L->curser->prev;
        temp->next = L->curser->prev = new;
        new->prev = temp;
        new->next = L->curser;
        L->index++;
        L->length++;
    }
    //increment curser index and length
    
}

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x){
    if(L->length<=0 || index(L)<0){
        fprintf(stderr, "List Error: failed to add a node before curser\n");
        exit(EXIT_FAILURE);
    }
    Node new = newNode(x);
    if (new == NULL) {
        fprintf(stderr, "List Error: failed to allocate memory for a new node\n");
        exit(EXIT_FAILURE);
    }
    if(index(L)==length(L)-1){
        append(L, x);
    }
    else{
        Node temp = L->curser->next;
        temp->prev = L->curser->next = new;
        new->next = temp;
        new->prev = L->curser;
        //increment length
        L->length++;
    }
    
}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if(length(L)<=0){
        fprintf(stderr, "List Error: failed to delete first element because list is empty\n");
        exit(EXIT_FAILURE);
    }
    if (index(L)==0)
    {
        L->index = -1;
    }
    
    else if(index(L)>0){
        L->index--;
    }
    //if length is 1 reset List
    if (length(L)==1){
        clear(L);
    }else{
        Node temp = L->front;
        L->front = L->front->next;
        temp->next = NULL;
        L->front->prev = NULL;
        freeNode(&temp);
        //decrement length
        L->length--;
    }

}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if(length(L)<=0){
        fprintf(stderr, "List Error: failed to delete last element because list is empty\n");
        exit(EXIT_FAILURE);
    }
    if (index(L)==L->length-1)
    {
        L->index = -1;
    }
    //if length is 1 reset List
    if (length(L)==1){
        clear(L);
    }else{
        Node temp = L->back;
        L->back = L->back->prev;
        temp->prev = NULL;
        L->back->next = NULL;
        freeNode(&temp);
        //decriment length 
        L->length--;
    }
}

// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
void delete(List L){
    if(length(L)<=0 || index(L)<0){
        fprintf(stderr, "List Error: failed to delete curser element because list is empty\n");
        exit(EXIT_FAILURE);
    }
    if(L->curser==L->front){
        deleteFront(L);
    }
    else if(L->curser==L->back){
        deleteBack(L);
    }
    else{
        Node temp = L->curser;
        L->curser = NULL;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next = temp->prev = NULL;
        freeNode(&temp);
        L->index = -1;
        L->length--;
    }
}

// Other Functions ------------------------------------------------------------

// Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    List new = newList();
    Node current = L->front;
    while(current!=NULL){
        append(new, current->data);
        current = current->next;
    }
    return new;
}

// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
    if (out == NULL || L == NULL) {
        fprintf(stderr, "Error: Invalid file pointer or NULL list reference\n");
        return;
    }

    Node current = L->front;

    while (current != NULL) {
        fprintf(out, "%d", current->data);
        current = current->next;
        if (current != NULL) {
            fprintf(out, " ");
        }
    }
}

// Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A and B.
 // The states of A and B are unchanged.
List concatList(List A, List B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "Error: cannot combine list because one or more are undefined.");
        exit(EXIT_FAILURE);
    }
    List new = newList();
    Node currenta = A->front;
    while(currenta!=NULL){
        append(new, currenta->data);
        currenta = currenta->next;
    }
    Node currentb = B->front;
    while(currentb!=NULL){
        append(new, currentb->data);
        currentb = currentb->next;
    }
    return new;
}

