// Bucket sort in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct Node {
  float data;
  struct Node *next;
};

void BucketSort(float arr[],int n,int b,int u);
struct Node *InsertionSort(struct Node *list);
void print(float arr[], int n);
int printBuckets(struct Node *list);
int getBucketIndex(float value);

// Sorting function
void BucketSort(float arr[],int n,int b,int u) {
  int i, j;
  struct Node **buckets;

  // Create buckets and allocate memory size
  buckets = (struct Node **)malloc(sizeof(struct Node *) * b);

  // Initialize empty buckets
  for (i = 0; i < b; ++i) {
    buckets[i] = NULL;
  }

  // Fill the buckets with respective elements
  for (i = 0; i < n; ++i) {
    struct Node *current;
    float pos = arr[i]*10;
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = arr[i];
    current->next = buckets[(int)pos];
    buckets[(int)pos] = current;
  }

  // Print the buckets along with their elements
  for (i = 0; i < b; i++) {
    printf("Bucket[%d]: ", i);
    float d=printBuckets(buckets[i]);
    printf("\n");
  }

  // Sort the elements of each bucket
  for (i = 0; i < b; ++i) {
    buckets[i] = InsertionSort(buckets[i]);
  }

  printf("-------------\n");
  printf("Bucktets after sorting\n");
  for (i = 0; i < b; i++) {
    printf("Bucket[%d]: ", i);
    printBuckets(buckets[i]);
    printf("\n");
  }

  // Put sorted elements on arr
  for (j = 0, i = 0; i < b; ++i) {
    struct Node *node;
    node = buckets[i];
    while (node) {
      arr[j++] = node->data;
      node = node->next;
    }
  }
    return ;
}

// Function to sort the elements of each bucket
struct Node *InsertionSort(struct Node *list) {
  struct Node *k, *nodeList;
  if (list == 0 || list->next == 0) {
    return list;
  }

  nodeList = list;
  k = list->next;
  nodeList->next = 0;
  while (k != 0) {
    struct Node *ptr;
    if (nodeList->data > k->data) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = nodeList;
      nodeList = tmp;
      continue;
    }

    for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
      if (ptr->next->data > k->data)
        break;
    }

    if (ptr->next != 0) {
      struct Node *tmp;
      tmp = k;
      k = k->next;
      tmp->next = ptr->next;
      ptr->next = tmp;
      continue;
    } else {
      ptr->next = k;
      k = k->next;
      ptr->next->next = 0;
      continue;
    }
  }
  return nodeList;
}

int getBucketIndex(float value) {
    return value*10;
}

void print(float ar[], int n) {
  int i;
  for (i = 0; i < n; ++i) {
    printf("%.1f ", ar[i]);
  }
  printf("\n");
}

// Print buckets
int printBuckets(struct Node *list) {
    int count=0;
  struct Node *cur = list;
  while (cur) {
    printf("%f ", cur->data);
    cur = cur->next;
    count++;
  }
  return count;
}

int main() {
  srand(time(0));
  FILE *file1;
  FILE *file2;
  printf("Choose file for data(eg. normal.txt):");
  char data_file[100];
  gets(data_file);
  printf("Choose file for result(eg. bs_result.csv):");
  char result_file[100];
  gets(result_file);
  file1 = fopen(data_file, "r+");
  file2 = fopen(result_file, "w");
  fprintf(file2,"Arr_size,Exe_time")  ;   
        
  int sample=50;
  float result;
  float arr1[100000];
  float num1;
  for(long long int i=0;i<100000;i++){
    fscanf(file1,"%f", &num1);
    arr1[i]=num1/10;
  }

  for(int ex=1;ex<16;ex++){
    for(int j=0;j<sample;j++){ 
      long long int n=pow(2,ex);

      time_t t;
      srand((unsigned)time(&t));
      float arr2[100000];
      for(long long int i=0;i<n;i++){
        long long int index=rand()*(j+1);
        if(index>100000){
            index=index/1000;
        }
        arr2[i]=arr1[index];
      }

      
      printf("\narr: ");
      print(arr2,n);    
      clock_t start, end;
      float cpu_time_used;
      
      start = clock();
      BucketSort(arr2, n, 10, 1000);
      end = clock();

      cpu_time_used = ((end - start))*1000 / CLOCKS_PER_SEC;

      printf("\nExecution time: %f",cpu_time_used);
      print(arr2,n);
      result+=cpu_time_used;  
    }

    result=result/sample;
    fprintf(file2,"\n");    
    fprintf(file2,"%d,%f",ex,result);
    
  }
        
  fclose(file1);
  fclose(file2);
}