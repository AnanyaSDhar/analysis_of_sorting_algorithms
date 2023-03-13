#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>


static int count=0;
//quicksort
int comp=0, s=0;
//function for swaping two elements
void swap(int *i,int *j){
        int c = *i;
	*i = *j;
	*j = c;
}

//a function to make pivots
int partion(int array[], int left,int right){
	int ref,i,j;
    ref = array[right];// taking the last element as pivot element.
    i = left-1;

    for(j=left; j<right; j++){//taking all the element less than pivot in one side before the elements greater than pivot element.

        if(array[j] <= ref){
			i++;
			swap(&array[i],&array[j]);
			s++;
        }
		comp++;
    }
	swap(&array[i+1],&array[right]);	// taking the pivort element at its place or say between the partition.
    s++;
	return (i+1);
}

//function to sort the elements.
void QuickSort(int array[],int lef,int rig){
        if(lef < rig){
                int p = partion(array,lef,rig);	//to find the index of pivot element
                QuickSort(array,lef,p-1);		//recursively sort the second half (elements after the pivot)
                QuickSort(array,p+1,rig);		//recursively sort the first half (elements before the pivot)
        }
}


//main

int main() {
        
        FILE *file1;
        FILE *file2;
        printf("Choose file for data(eg. normal.txt):");
        char data_file;
        gets(data_file);
        printf("Choose file for result(eg. qs_result.txt):");
        char result_file;
        gets(result_file);
        file1 = fopen(data_file, "r+");
        file2 = fopen(result_file, "a");
        
        int sample=50;
        int result[200];
        int arr1[100000];
        int num1;
        for(long long int i=0;i<100000;i++){
                fscanf(file1,"%d", &num1);
                arr1[i]=num1;

        }

        for(int ex=2;ex<=16;ex++){
                long long int n=pow(2,ex);

                for(int j=0;j<sample;j++){                        
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
                        
                        QuickSort(arr2,0,n);
                        int comp1=comp;
                        for(int i=0;i<n;i++){
                                printf("%d  ", arr2[i]);
                        }
                        
                        printf("\nno. of comparisons:%d\n\n",comp1);
                        result[j]=comp1;
                }

        }
        
            
        for(long long int i=(sample-1);i>=0;i--){
                if(i>0){
                        result[i]=result[i]-result[i-1];
                }
        }

        printf("\n");

        for(int i=0;i<sample;i++){
                printf("%d  ", result[i]);
        }

        fprintf(file2,"\n");    
        for(long long int i=0;i<sample;i++){
                fprintf(file2,"%d ",result[i]);
        }
                
        fclose(file1);
        fclose(file2);
}