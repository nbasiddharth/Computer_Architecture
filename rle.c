#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char **argv){
    int count;
    int error;
    int check;
    int num;
    char d;
    int length;
    int begin;
    int j;
    int t;
    int r;
    int k;
    int digit;
    int countB;
    if(argc < 2){
        return 0;
    }
    else if(argv[1][0] == '\0'){
        return 0;
    }
    else{
        char* clon = (char*)malloc((strlen(argv[1])+1) * sizeof(char));
        strcpy(clon, argv[1]);
        count = 0;
        error = 0;
        num = 0;
        d = '0';
        while(argv[1][count] != '\0'){
            for(num = 0; num < 10; num++){
                d = num +'0';
                if(argv[1][count] == d ){
                    error++;
                    break;
                }
                }
            count++;
        }
        if(error > 0){
            printf("error\n");
            free(clon);
            return 0;
        }
        else{
            begin = 0;
            length = 1;
            check =0;
            r =0;
            t =0;
            int countA = strlen(argv[1]);
            char* B = (char*)malloc((countA+1) * sizeof(char));
           // printf("%d\n", countA);
            if(countA > 1){
                for(j = 1; j < countA; j++){
                    if(argv[1][j] == argv[1][begin]){
                        length++;
                        if(j == (countA -1)){
                            *(B + t) = argv[1][begin];
                            t = t+1;
                            if(t >= (countA)){
                                check = 1;
                                break;
                            }
                            else{
                                digit = length;
                                countB =0;
                                while(digit != 0){
                                    countB++;
                                    digit = digit/10;
                                 }
                                char* c = (char*) malloc((countB+1)*sizeof(char));
                                sprintf(c, "%d", length);
                                k = 0;                            
                                while(c[k] != '\0'){
                                    *(B+t) = c[k];
                                    t++;
                                    k++;
                                    }
                                free(c);
                            }
                    }
                    }
                    else{
                       *(B + t) = argv[1][begin];
                       t = t+1;
                     //  printf("%d\n", t);
                       if(t >= (countA)){
                         check = 1;
                         break;
                       }
                       else{
                            digit = length;
                            countB =0;
                            while(digit != 0){
                                countB++;
                                digit = digit/10;
                            }
                            char* c = (char*) malloc((countB+1)*sizeof(char));
                            sprintf(c, "%d", length);
                            k =0;
                            while(c[k] != '\0'){
                              //  printf("%d\n", k);
                                *(B+t) = c[k];
                                t++;
                                k++;
                            }
                            free(c);
                            if(t >= (countA)){
                                check =1;
                                break;
                            }
                            length = 1;
                            begin = j;
                            if(j == (countA -1)){
                                *(B+t) = argv[1][j];
                                t++;
                              //  printf("%d\n", t);
                                if(t >= countA){
                                    check =1;
                                    break;
                                }
                                char g[2];
                                sprintf(g, "%d", length);
                                *(B+t) = g[0];
                                t++;
                             //   printf("%c\n",*(B+t));
                            }
                            
                        }
                    }
                }
             if(check > 0){
                 printf("%s\n", clon);
                 free(B);
                 free(clon);
                 return 0;
                }
            else{
                for(r = 0; r < t; r++){
                    printf("%c", *(B+r));
                }
                printf("\n");
                free(B);
                free(clon);
                return 0;
                 }
            }
            else{
                printf("%s", argv[1]);
                free(B);
                free(clon);
                return 0;
            }
            }
return 0;
}
}