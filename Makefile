CC=g++
CREATE_EXEC=create_files
SORT_EXEC=sort_file
CREATE_CPP=create_new_files.cpp
SORT_CPP=sort_integer_files.cpp

all: create.o sort.o

create.o: $(CREATE_CPP)
	$(CC) $(CREATE_CPP) -o $(CREATE_EXEC)

sort.o: $(SORT_CPP)
	$(CC) $(SORT_CPP) -o $(SORT_EXEC)

.PHONY: clean
clean:
	rm $(CREATE_EXEC) $(SORT_EXEC) *.o file*.txt

run:
	make; ./$(CREATE_EXEC) 1 10 10 1 10; ./$(SORT_EXEC) file0
