
MergeSort: MergeSort.o ProcessWritter.o ProcessReader.o
	gcc MergeSort.o -o MergeSort
	gcc ProcessWritter.o -o ProcessWritter -lrt
	gcc ProcessReader.o -o ProcessReader -lrt
MergeSort.o: MergeSort.c
	gcc -c MergeSort.c
ProcessWritter.o: ProcessWritter.c
	gcc -c ProcessWritter.c
ProcessReader.o: ProcessReader.c
	gcc -c ProcessReader.c
clean:
	rm *.o
