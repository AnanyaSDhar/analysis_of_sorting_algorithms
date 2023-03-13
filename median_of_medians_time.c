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
int main()
{
    srand(time(0));

    int arr_size = 100000;
    int num_iter = 100;
    float start_time, end_time, time_taken;
    double avg_time;

    FILE *fout = fopen("MoM_obs.csv", "w");
    fprintf(fout, "div_size,avg_time\n");

    int divide_size;

    short arr[arr_size];

    for (int obs_counter = 0; obs_counter <= 1000; obs_counter++)
    {
        divide_size = 2 * obs_counter + 3;
        avg_time = 0;

        for (int i = 0; i < num_iter; i++)
        {
            for (int j = 0; j < arr_size; j++)
                arr[j] = rand() % 100;

            start_time = clock();
            int temp = median_of_median(arr, arr_size, divide_size);
            end_time = clock();

            time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
            avg_time += time_taken;
        }

        avg_time = avg_time / num_iter;

        printf("divide_size: %4d avg_time: %3.4f ms\n", divide_size,avg_time);
        fprintf(fout, "%d,%f\n", divide_size, avg_time);
    }

    fclose(fout);
    return 0;
}