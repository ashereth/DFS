// compile:   gcc -std=c17 -Wall -o test Graph.c List.c GraphTest.c 
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main() {

    FILE *infile = fopen("input.txt", "r");

    //populate the graph
    char line[100];
    int size;

    //get the size of the graph from the first line
    if (fgets(line, sizeof(line), infile) != NULL) {
        // Use atoi to convert the line to an integer
        size = atoi(line);
    }else {
        // Handle the case where the file is empty or the first line is not an integer
        printf("Unable to read a size from the file.\n");
        fclose(infile);
        return 0;
    }
    //initialize the graph after getting the size from the first line
    Graph G = newGraph(size);
    // Create a new graph with an unspecified number of vertices
    printf("Number of vertices = %d\n", getOrder(G));
    printf("Number of edges = %d\n", getSize(G));
    //read all edges and populate graphs edges
    int num1, num2;
    while (fscanf(infile, "%d %d", &num1, &num2) == 2) {
        //break once you get to 2 0s
        if (num1 == 0 && num2 ==0){
            break;
        }
        // Process num1 and num2
        addArc(G, num1, num2);
    }

    //create a newlist and fill it with ints
    List S = newList();

    for(int i = 1; i<= size; i++){
        append(S, i);
    }

    DFS(G, S);

    printf("Number of directed edges after populating from infile = %d\n", getSize(G));
    printGraph(stdout, G);

    printf("\ncopy of G: \n");
    Graph copy = copyGraph(G);
    printGraph(stdout, copy);

    printf("\norder each vertex finished in decreasing order: ");
    printList(stdout, S);
    Graph T = transpose(G);
    printf("\nThe transpose of G is: \n");
    printGraph(stdout, T);
    DFS(T, S);
    printf("\norder each vertex finished after running DFS on transpose: ");
    printList(stdout, S);


    int stronglyconnected = 0;

    List connectedTree = newList();
    moveBack(S);
    for (int i=0; i<length(S); i++){
        prepend(connectedTree, get(S));
        //tested all colors are made white
        if(getParent(T, get(S))==NIL){
            stronglyconnected += 1;
            printf("\nComponent %d: ", stronglyconnected);
            printList(stdout, connectedTree);
            clear(connectedTree);
            
        }
        movePrev(S);
    }

    printf("\nThere are %d strongly connected components.", stronglyconnected);

    freeGraph(&T);
    freeGraph(&copy);
    freeGraph(&G);
    fclose(infile);
    return 0;
}
