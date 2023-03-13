#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>

int  count=0; /* to count the number of comparisions */

 int merge( int arr [ ], int l, int m, int r)
{
 int i=l; /* left subarray*/
 int j=m+1; /* right  subarray*/
 int k=l; /* temporary array*/
 int temp[r+1];
 while( i<=m && j<=r)
 {
   if ( arr[i]<= arr[j])
  {
    temp[k]=arr[i];
    i++;
  }
   else
  {
    temp[k]=arr[j];
    j++;
  }
    k++;
    count++;

  }
   while( i<=m)
  {
    temp[k]=arr[i];
    i++;
    k++;
  }
    while( j<=r)
  {
    temp[k]=arr[j];
    j++;
    k++;
  }
  for( int p=l; p<=r; p++)
  {
    arr[p]=temp[p];
  }
   return count;
  }


  int  mergesort( int arr[ ], int l, int r)
  {
    int comparisons;
    if(l<r)
  {
   int m= ( l+r)/2;
   mergesort(arr,l,m);
   mergesort(arr,m+1,r);
   comparisons = merge(arr,l,m,r);
  }
   return comparisons;
  }


//main

int main() {
        
  FILE *file1;
  FILE *file2;
  printf("Choose file for data(eg. normal.txt):");
  char data_file;
  gets(data_file);
  printf("Choose file for result(eg. mergeSort_result.txt):");
  char result_file;
  gets(result_file);
  file1 = fopen(data_file, "r+");
  file2 = fopen(result_file, "a");

  int sample=50;
  int resultU[200];
  int arr1[100000];
  int num1;
  for(long long int i=0;i<100000;i++){
    fscanf(file1,"%d", &num1);
    arr1[i]=num1;

  }  
    
  int count=0;
  for(int ex=12;ex<=16;ex++){

    long long int n=pow(2,ex);

    for(int j=0;j<sample+1;j++){  

      time_t t;
      srand((unsigned)time(&t));
      int arr2[100000];
      for(long long int i=0;i<n;i++){
        long long int index=rand()*(j+1);
        if(index>100000){
          index=index/1000;
        }
        arr2[i]=arr1[index];
      }

      for(long long int i=0;i<n;i++){
        printf("%d  ", arr2[i]);
      }

      printf("\nSorted:\n");
      //merge sort
      int comp1 = mergesort(arr2,0,n-1);
      for(int i=0;i<n;i++){
        printf("%d  ", arr2[i]);
      }
      
      printf("\nno. of comparisons:%d\n\n",comp1);
      resultU[j]=comp1;
    }

    for(long long int i=(sample-1);i>=0;i--){
      if(i>0){
        resultU[i]=resultU[i]-resultU[i-1];
      }
    } 

    for(long long int i=1;i<sample;i++){
      printf("%d  ", resultU[i]);
    }  

    fprintf(file2,"\n");
    for(long long int i=0;i<sample-1;i++){
      fprintf(file2,"%d ",resultU[i+1]);
    }
        
    fclose(file1);
    fclose(file2);
  }

}