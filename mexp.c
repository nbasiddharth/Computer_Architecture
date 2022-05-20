#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv){
   int b =0;
   int i =0;
   int j =0;
   int k =0;
   int r = 0;
   int s = 0;
   int start = 0;
   FILE *f = fopen(argv[1], "r");
   fscanf(f,"%d",&b);
   int size =b;
   int *rows = (int*)malloc(sizeof(int)*(size*size));
   int *columns = (int*)malloc(sizeof(int)*(size*size));
   for(i = 0; i< size; i++){
       for(j =0; j < size; j++){
           fscanf(f,"%d", &b);
           rows[k] = b;
           k =k+1;

       }
   }
   fscanf(f, "%d", &b);
   int power = b;
   int x = 0;
   int y = 0;
   int count =0;
   int t = 0;
   for(t = 0; t< size; t++){
       x = y;
       for(r = 0; r< size; r++){
           columns[count] = rows[x];
           x= x+size;
           count++;
       }
       y++;
   }
int length = size *size;
if(power == 0){
    int begin = 0;
    int end = 0;
    int tap =0;
    for(begin = 0; begin < size; begin++){
        for(end = 0; end < size; end++){
            if(begin == end){
                rows[tap] = 1;
                tap++;
            }
            else{
                rows[tap] = 0;
                tap++;
            }
        }
    }
}
else{
   int counter = 0;
   int track = 0;
   int inner = 0;
   int sum =0;
   int app = 0;
    for(app = 0; app < (power-1); app++){
        int *product = (int *)malloc(sizeof(int)*(size*size));
        for(start = 0; start < size; start++){
            for(inner = 0; inner < length; inner++){
                sum = sum + columns[inner] * rows[counter];
                counter++;
                if(counter != 0 && counter % size == 0){
                    product[track] = sum;
                    sum = 0;
                    counter = counter -size;
                    track = track +1;
                }
            }
             counter = counter+size;
        }
        int* temp;
        temp = rows;
        rows = product;
        product = NULL;
        free(temp);
        free(product);
        counter = 0;
        track = 0;
    }
}
   int tick = 0;
   for(s =0; s< (size*size); s++){
       printf("%d", rows[s]);
       tick++;
       if(tick % size == 0){
           printf("\n");
       }
       else{
           printf(" ");
       }
   }
    free(rows);
    free(columns);
    return 0;
}