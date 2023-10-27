#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char * argv[]){
    // check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }


    //open infile for reading
    FILE *infile = fopen(argv[1], "r");
    //open outfile for writing
    FILE *outfile = fopen(argv[2], "w");

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
        fclose(outfile);
        return 0;
    }
    //initialize the graph after getting the size from the first line
    Graph G = newGraph(size);
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

    fprintf(outfile, "Adjacency list representation of G:\n");
    printGraph(outfile, G);

    //create a newlist and fill it with ints
    List S = newList();

    for(int i = 1; i<= size; i++){
        append(S, i);
    }

    DFS(G, S);

    Graph T = transpose(G);
    DFS(T, S);

    int stronglyconnected = 0;
    List connectedTree = newList();
    moveBack(S);

    for (int i=0; i<length(S); i++){
        //tested all colors are made white
        if(getParent(T, get(S))==NIL){
            stronglyconnected += 1;
        }
        movePrev(S);
    }
   
    fprintf(outfile, "\n\nG contains %d strongly connected components:\n", stronglyconnected);
    //reset stronglyconnected in order to print the right thing to file
    stronglyconnected = 0;
    moveBack(S);
    for (int i=0; i<length(S); i++){
        prepend(connectedTree, get(S));
        //tested all colors are made white
        if(getParent(T, get(S))==NIL){
            stronglyconnected++;
            fprintf(outfile, "Component %d: ", stronglyconnected);
            printList(outfile, connectedTree);
            fprintf(outfile, "\n");
            clear(connectedTree);
            
        }
        movePrev(S);
    }

    //free everything
    fclose(infile);
    fclose(outfile);
    freeGraph(&T);
    freeGraph(&G);
    freeList(&S);
    freeList(&connectedTree);
}