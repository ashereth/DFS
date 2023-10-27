#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"

/*** type definitions ***/
#define WHITE 2
#define GRAY 1
#define BLACK 0

typedef struct GraphObj{
    int order;//define the number of vertices of the graph
    int size;//define the number of edges
    int source;//define the source of the graph
    List* AdjList;//create an array of Lists for the Adjacency List
    int* parent; //array to store the parents/predecessors for every vertex
    int* discover_time;//array to store the discover time for each vertex
    int* finish_time;//array to store finish time for each vertex
    int* colors;//array to keep track of which vertices have been discovered
}GraphObj;

/*** Constructors-Destructors ***/
//create a new graph with n vertices
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj));
    assert(G!=NULL);
    G->order = n;//set the number of vertices
    G->size = 0;//set number of edges to 0 initially
    G->source = NIL;//set source to invalid initially
    //allocate memory for all needed arrays
    G->parent = (int*)malloc((n + 1) * sizeof(int));
    G->discover_time = (int*)malloc((n + 1) * sizeof(int));
    G->finish_time = (int*)malloc((n + 1) * sizeof(int));
    G->AdjList = (List*)malloc((n + 1) * sizeof(List));
    G->colors = (int*)(malloc((n+1) * sizeof(int)));
    //set all needed values in the arrays
    for (int i = 1; i <= n; i++) {//make sure to create enough room in arrays to be able to index all the way to n
        G->parent[i] = NIL;
        G->discover_time[i] = UNDEF;
        G->finish_time[i] = UNDEF;
        G->colors[i] = WHITE;
        G->AdjList[i] = newList(); // Create a new List for each vertex
    }
    return G;
}

//free all memory associated with a graph pointer
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL) {
        Graph G = *pG;

        // Free memory for the adjacency lists and their elements
        for (int i = 1; i <= G->order; i++) {
            freeList(&(G->AdjList[i]));
        }

        // Free other dynamically allocated arrays
        free(G->parent);
        free(G->discover_time);
        free(G->finish_time);
        free(G->colors);
        free(G->AdjList);

        //free the Graph object itself
        free(G);

        // Set the pointer to NULL
        *pG = NULL;
    }
}
/*** Access functions ***/

//returns the number of Vertices in the graph
int getOrder(Graph G){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get Graph Order.\n");
        return -1;
    }
    return G->order;
}

//returns the number of edges in the graph
int getSize(Graph G){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get Graph Size.\n");
        return -1;
    }
    return G->size;
}

//get the parent of the given vertecy if it has been set
int getParent(Graph G, int u){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get parent of vertex %d.\n", u);
        return -1;
    }else if(u<1 || u>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Graph Error: cannot get parent because given vertex is out of bounds.\n");
        return -1;
    }
    //if parent hasn't been set for the given vertex then it will return NIL/0
    return G->parent[u];
}

/*get the discover time for given vertex Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get discover time of vertex %d.\n", u);
        return -1;
    }else if(u<1 || u>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Graph Error: cannot get discover time because given vertex is out of bounds.\n");
        return -1;
    }
    //if all preconditions are met return discover time of vertex
    return G->discover_time[u];
} 

/*get the finish time for given vertex Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
    if(G==NULL){
        fprintf(stderr, "Graph Error: unable to get finish time of vertex %d.\n", u);
        return -1;
    }else if(u<1 || u>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Graph Error: cannot get finish time because given vertex is out of bounds.\n");
        return -1;
    }
    //if all preconditions are met return finish time of vertex
    return G->finish_time[u];
}

/*** Manipulation procedures ***/

//add an edge v to the adjacency list of u and visca versa
void addEdge(Graph G, int u, int v){
    if (G==NULL){
        fprintf(stderr, "Graph Error: Unable to add edge because graph doesn't exist.\n");
        return;
    }else if(u<1 || u>G->order || v<1 || v>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Path Error: cannot add edge because given vertex is out of bounds.\n");
        return;
    }
    //increment the size of the graph
    G->size++;
    //add u to adjlist v
    List Lv = G->AdjList[v];
    int added = 0;//keep track if edge has been added
    if(length(Lv)==0){//if list is empty just insert u
        append(Lv, u);
    }else{
        moveFront(Lv);
        //while u>curser element and curser isnt at the end
        while(u>get(Lv)){
            //if we are at the end of the List append to the end
            if(index(Lv)==length(Lv)-1){
                append(Lv, u);
                added++;
            }
            moveNext(Lv);
        }
        //once u is less than curser element add u before curser
        if(added==0){
            insertBefore(Lv, u);
            added+=1;
        }
        
    }
    //add v to adjlist u
    List Lu = G->AdjList[u];
    added = 0;
    if(length(Lu)==0){//if list is empty just insert u
        append(Lu, v);
    }else{
        moveFront(Lu);
        //while u>curser element and curser isnt at the end
        while(v>get(Lu)){
            //if we are at the end of the List append to the end
            if(index(Lu)==length(Lu)-1){
                append(Lu, v);
                added++;
            }
            moveNext(Lu);
        }
        //once u is less than curser element add u before curser
        if(added==0){
            insertBefore(Lu, v);
            added+=1;
        }
        
        return;
    }
}

//add a directed edge from u to v
void addArc(Graph G, int u, int v){
    if (G==NULL){
        fprintf(stderr, "Graph Error: Unable to add edge because graph doesn't exist.\n");
        return;
    }else if(u<1 || u>G->order || v<1 || v>G->order){//print error if vertex is out of bounds
        fprintf(stderr, "Path Error: cannot add edge because given vertex is out of bounds.\n");
        return;
    }
    //increment the size of the graph
    G->size++;
    //add v to adjlist of u
    List Lu = G->AdjList[u];
    if(length(Lu)==0){//if list is empty just insert u
        append(Lu, v);
    }else{
        moveFront(Lu);
        //while u>curser element and curser isnt at the end
        while(v>get(Lu)){
            //if we are at the end of the List append to the end
            if(index(Lu)==length(Lu)-1){
                append(Lu, v);
                return;
            }
            moveNext(Lu);
        }
        //once u is less than curser element add u before curser
        insertBefore(Lu, v);
        return;
    }
}

//visit() helper function for DFS
/*The second approach is to lettime be a local variable in DFS(), 
then pass the address of time to Visit(), making it an input-output
variable to Visit(). This is perhaps the simplest option, and is recommended.*/
void Visit(Graph G, int* time, int x, List S){
    G->discover_time[x] = (++*time);
    G->colors[x] = GRAY;
    //loop through adjlist of x
    List edges = G->AdjList[x];
    moveFront(edges);
    for(int i = 0; i<length(edges); i++){
        int y = get(edges);
        if (G->colors[y]==WHITE){
            G->parent[y] = x;
            Visit(G, time, y, S);
        }
        //move to the next edge in the list
        moveNext(edges);
    }
    G->colors[x] = BLACK;
    //prepend finished vertex to S
    prepend(S, x);
    G->finish_time[x] = (++*time);
}

/*Runs DFS on given graph and uses list S as a stack Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S){
    if(length(S)!=getOrder(G)){
        fprintf(stdout, "Unable to run DFS List S is of incorrect size.\n");
        exit(EXIT_FAILURE);
    }
    //make a copy of list S
    List order = copyList(S);
    //clear  List S in order to fill up with finished  vertices
    clear(S);
    //loop through order List
    moveFront(order);
    for (int i=0; i<length(order); i++){
        int x = get(order);
        //tested all colors are made white
        G->colors[x] = WHITE;
        G->parent[x] = NIL;
        moveNext(order);
    }
    int time = 0;
    //loop through order List
    moveFront(order);
    for (int i=0; i<length(order); i++){//main DFS loop
        int x = get(order);
        if (G->colors[x] == WHITE){
            //pass visit the emtpied list so that visit can fill it up
            Visit(G, &time, x, S);
        }
        moveNext(order);
    }
    //free the copied list
    freeList(&order);
}

/*** Other operations ***/
//returns the transpose of the graph G
Graph transpose(Graph G){
    //make a new graph to be the transpose of G
    Graph T = newGraph(G->order);
    //loop through all vertices of G
    for (int i = 1; i<=G->order; i++){
        //loop through all edges of i
        moveFront(G->AdjList[i]);
        for (int j=0; j<length(G->AdjList[i]); j++){
            addArc(T, get(G->AdjList[i]), i);
            moveNext(G->AdjList[i]);
        }
    }
    return T;
}

//returns a copy of the graph G
Graph copyGraph(Graph G){
    if(G==NULL){
        fprintf(stderr, "Graph Error: Unable to add edge because graph doesn't exist.\n");
        return NULL;
    }
    //make a graph thats the same size
    Graph copy = newGraph(G->order);
    copy->size = G->size;

    //copy the adjLists from G into the copy
    for(int i = 1; i<=copy->order; i++){
        copy->AdjList[i] = copyList(G->AdjList[i]);
    }

    return copy;
}

void printGraph(FILE* out, Graph G){
    if (out == NULL || G == NULL) {
        fprintf(stderr, "Error: Invalid file pointer or NULL list reference\n");
        return;
    }
    for (int i = 1; i<=getOrder(G); i++){
        fprintf(out, "%d: ", i);//print out each vertex
        printList(out, G->AdjList[i]);//then print out each edge of that vertex
        if(i<getOrder(G)){
            fprintf(out, "\n");
        }
    }
}