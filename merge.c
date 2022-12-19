/*
* @Autor: Darwin Neira Carrasco
* @Email: dneirac@unsa.edu.pe
* @File: merge
* @Descripcion:
*/

#include <stdio.h>

void mergesort(int arr[], int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = m - l + 1;
	
	int L[n1];
	int R[n2];

	for (int i = 0 ; i < n1 ; i++) {
		L[i] = arr[l + i];
	}
	
	for (int j = 0 ; j < n2 ; j++) {
		R[j] = arr[m + 1 + j];
	}
	
	int i = 0, j = 0, k = l;
	
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void merge(int arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l)/2;
		merge(arr, l, m);
		merge(arr, m + 1, r);
		mergesort(arr, l, m, r);
	}
}

void print(int arr[]) {
	for (int i = 0 ; i < 6 ; i++)
	printf("%d ", arr[i]);
	printf("\n");
}

int main() {
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	print(arr);
	merge(arr, 0, 5);
	print(arr);
	return 0;
}
