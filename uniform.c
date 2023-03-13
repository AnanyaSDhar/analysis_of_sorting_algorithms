#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>


int random_num(){
        printf("in random\n");
        int number;
        srand(time(NULL));
        number=rand()%10;
        return number;
}


int main(){
        FILE * file;
        file = fopen("uniform100.txt", "w");
        if(file == NULL){
        printf("Error!");
        exit(1);
        }
        int num;
        for(long long int i=0;i<1000000;i++){
                num=rand()%100;
                fprintf(file,"%d ",num);
        }


        fclose(file);

}