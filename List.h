#ifndef List_H_INCLUDE_
#define List_H_INCLUDE_
#include<stdbool.h>
#include<stdio.h>


#define FORMAT "%d"


// Exported types -------------------------------------------------------------
typedef int ListElement;
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList();

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pQ);


// Access functions -----------------------------------------------------------

// getLength()
// Returns the length of Q.
int length(List Q);

int index(List L); // Returns index of cursor element if defined, -1 otherwise.

int front(List L); // Returns front element of L. Pre: length()>0

int back(List L); // Returns back element of L. Pre: length()>0

int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0

bool equals(List A, List B); // Returns true iff Lists A and B are in same
 // state, and returns false otherwise.

// Manipulation procedures ----------------------------------------------------

void clear(List L); // Resets L to its original empty state.

void set(List L, int x); // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0

void moveFront(List L); // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.

void moveBack(List L); // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.

void movePrev(List L); // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing

void moveNext(List L); // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing

void prepend(List L, int x); // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.

void append(List L, int x); // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.

void insertBefore(List L, int x); // Insert new element before cursor.
 // Pre: length()>0, index()>=0

void insertAfter(List L, int x); // Insert new element after cursor.
 // Pre: length()>0, index()>=0

void deleteFront(List L); // Delete the front element. Pre: length()>0

void deleteBack(List L); // Delete the back element. Pre: length()>0

void delete(List L); // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0



// Other Functions ------------------------------------------------------------

void printList(FILE* out, List L); // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.

List copyList(List L); // Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.

List concatList(List A, List B); // Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A and B.
 // The states of A and B are unchanged.

#endif
