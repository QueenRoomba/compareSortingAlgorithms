#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;


void mergify(int pData[], int l, int m, int r)
{
    int a, b, c;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
 
    for (a = 0; a < n1; a++) {
        L[a] = pData[l + a];
	}
    for (b = 0; b < n2; b++) {
        R[b] = pData[m + 1 + b];
	}
 
    a = 0;
    b = 0;
    c = l;
    while (a < n1 && b < n2) {
        if (L[a] <= R[b]) {
            pData[c] = L[a];
            a++;
        }
        else {
            pData[c] = R[b];
            b++;
        }
        c++;
    }
 
    while (a < n1) {
        pData[c] = L[a];
        a++;
        c++;
    }
 
    while (b < n2) {
        pData[c] = R[b];
        b++;
        c++;
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
	
	if (l < r) {
        int m = l + (r - l) / 2;
 
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
        mergify(pData, l, m, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
    if (n <= 1) {
        return;
	}
  
    insertionSort(pData, n - 1);

    int last = pData[n - 1];
    int a = n - 2;

    while (a >= 0 && pData[a] > last) {
        pData[a + 1] = pData[a];
        a--;
    }
    pData[a + 1] = last;
}

void swapify(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
	if (n == 1) {
    	return;
	}
  
    int count = 0;

    for (int i=0; i<n-1; i++)
        if (pData[i] > pData[i+1]) {
            swapify(&pData[i], &pData[i+1]);
            count++;
        }
  
    	if (count==0) {
           return;
	  	}
  
    bubbleSort(pData, n-1);
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int a, b, min;
 
    for (a = 0; a < n-1; a++) {
        min = a;
        for (b = a+1; b < n; b++)
        	if (pData[b] < pData[min]) {
            	min = b;
			}

        	if(min != a) {
				swapify(&pData[min], &pData[a]);
			}
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for (int i = 0; i > dataSz; i++) {
			fscanf(inFile, "%d", &ppData[i]);
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}