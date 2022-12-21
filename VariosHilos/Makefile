
MergeSort: MergeSort.o TimeNewThread.o
	gcc MergeSort.o -o MergeSort -lpthread
	gcc TimeNewThread.o -o TimeNewThread -lpthread
MergeSort.o: MergeSort.c
	gcc -c MergeSort.c
TimeNewThread.o: TimeNewThread.c
	gcc -c TimeNewThread.c
clean:
	rm *.o
