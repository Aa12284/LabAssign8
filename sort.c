#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void heapSwap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heap(int arr[], int n, int a) {
	
	int maxInt = a;
	
	int l = 2 * a + 1;
	int r = 2 * a + 2;
	
	if (l < n && arr[l] > arr[maxInt]) {
		maxInt = l;
	}
	
	if (r < n && arr[r] > arr[maxInt]) {
		maxInt = r;
	}
	
	if (maxInt != a) {
		
		heapSwap(&arr[a], &arr[maxInt]);
		heap(arr, n, maxInt);
	}
	
	
}




void heapSort(int arr[], int n)
{
	
	extraMemoryAllocated = 0;
	
	for (int a = n / 1; a >= 0; a--) {
		heap(arr, n, a);
	}
	
	for (int a = n - 1; a >= 0; a--) {
		heapSwap(&arr[0], &arr[a]);		
		heap(arr, a, 0);
	}
	
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void merge(int pData[], int l, int m, int r) {
    int a; 
	int b; 
	int c;
	
	
    int num1 = m - l + 1;
    int num2 = r - m;

    int* left = (int*) malloc(num1 * sizeof(int));
    int* right = (int*) malloc(num2 * sizeof(int));

    for (a = 0; a < num1; a++) {
        left[a] = pData[l + a];
    }
        
        
    for (b = 0; b < num2; b++) {
        right[b] = pData[m + 1 + b];
    }

    a = 0;
    b = 0;
    c = l;
    
    
    while (a < num1 && b < num2) 
	{
        if (left[a] <= right[b]) {
            pData[c] = left[a];
            a++;
        }
        
        
        else {
            pData[c] = right[b];
            b++;
        }
        
        c++;
    }

    while (a < num1) {
        pData[c] = left[a];
        a++;
        c++;
    }

    while (b < num2) {
        pData[c] = right[b];
        b++;
        c++;
    }

    extraMemoryAllocated = extraMemoryAllocated + num1 * sizeof(int) + num2 * sizeof(int);
	
	

}

void mergeSort(int pData[], int l, int r) {
    if (l < r) {
        int middle = l + (r - l) / 2;
        mergeSort(pData, l, middle);
        mergeSort(pData, middle + 1, r);
        merge(pData, l, middle, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int a, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (a=0;a<dataSz;++a)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + a;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int a, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (a=0;a<100;++a)
	{
		printf("%d ",pData[a]);
	}
	printf("\n\t");
	
	for (a=sz;a<dataSz;++a)
	{
		printf("%d ",pData[a]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int a;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (a=0;a<4;++a)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[a], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
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
