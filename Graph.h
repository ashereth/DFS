#include "List.h"

/*** type definitions ***/
typedef struct GraphObj* Graph;
#define NIL 0
#define UNDEF -1

/*** Constructors-Destructors ***/
//create a new graph and allocate memory for everything needed
Graph newGraph(int n);
//free all memory associated with give graph pointer
void freeGraph(Graph* pG);
/*** Access functions ***/
//returns the order of the graph
int getOrder(Graph G);
//returns the number of edges in the graph
int getSize(Graph G);
//return the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() has not yet been called
//pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/*** Other operations ***/
//prints the vertices and edges to the given file
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);
