BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindComponents GraphClient FindComponents.o GraphClient.o $(BASE_OBJECTS)

checkFind : FindComponents
	$(MEMCHECK) FindComponents in8 junk8

checkClient : GraphClient
	$(MEMCHECK) GraphClient