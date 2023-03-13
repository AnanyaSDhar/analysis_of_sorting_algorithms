#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Median of Median approach taking 3,5,7,9... elements in each group

#define MAX 100
#define ROUNDS 12

void insertion_sort(int *arr, int start, int final){
  for (int i = start; i <= final; i++){
    int temp = arr[i];
    int pos = i - 1;
    while (pos >= start && arr[pos] > temp){
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = temp;
  }
}

int median(int *arr, int start, int final){
  insertion_sort(arr, start, final);
  int mid = (start + final) / 2;
  return arr[mid];
}

int median_of_medians(int *arr, int size, int div_size){
  if (size < div_size){
    return median(arr, 0, size - 1);
  }
  int total = size / div_size;
  int last = size % div_size;

  int next;

  if (last == 0){
    next = total;
  }
  else{
    next = total + 1;
  }

  int next_arr[next];

  for (int i = 0; i < next; i++){
    if (i == next - 1){
      next_arr[i] = median(arr, div_size * i, size - 1);
    }
    else{
      next_arr[i] = median(arr, div_size * i, div_size * (i + 1) - 1);
    }
  }
  return median_of_medians(next_arr, next, div_size);
}
int main(){
  //srand(time(0));
  int size = 1000;
  int partition_size;
  int arr[size];
  int copy[size];
  printf("Choose file for data(eg. normal.txt):");
  char data_file[100];
  gets(data_file);
  printf("Choose file for result(eg. mom_result.txt):");
  char result_file[100];
  gets(result_file);
  FILE *file=fopen(data_file, "r");
  int num;
  for(int i=0;i<size;i++){
    fscanf(file,"%d", &num);
    arr[i]=num;
  }
  for(int i=0;i<size;i++){
    printf("%d ", arr[i]);
  }
  int mid=median(arr,0,size);
  
  FILE *f2 = fopen(result_file,"a");
  fprintf(f2,"Partition_size,Diff_median_MoM\n");

  for(int k=0;k<=14;k++){
    
    partition_size= 2 * k + 3;
    int m=0;
    int diff=0;
    
    for (int j = 0; j < 1000; j++){
      for (int i = 0; i < size; i++){
        copy[i] = arr[rand()%size];
      }
      m=m+median_of_medians(copy, size, partition_size);
      diff=diff+abs((mid-median_of_medians(copy, size, partition_size)));
    }
    m=m/1000;
    diff=diff/1000;
    printf("%d ", diff);
    //fprintf(f1, "%d,%d,%d",partition_size, mid,m);
    fprintf(f2, "%d,%d",partition_size, diff);
    //fprintf(f1,"\n");
    fprintf(f2,"\n");

  }
  
  printf("File has been generated successfully\n");
  //fclose(f1);
  fclose(f2);
  fclose(file);
  return 0;
}
