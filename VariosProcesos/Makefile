
MergeSort: MergeSort.o ProcessWritter.o ProcessReader.o
	gcc MergeSort.o -o MergeSort
	gcc ProcessWritter.o -o ProcessWritter
	gcc ProcessReader.o -o ProcessReader
MergeSort.o: MergeSort.c
	gcc -c MergeSort.c
ProcessWritter.o: ProcessWritter.c
	gcc -c ProcessWritter.c
ProcessReader.o: ProcessReader.c
	gcc -c ProcessReader.c
clean:
	rm *.o
