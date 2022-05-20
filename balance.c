#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char **argv){
    int length = strlen(argv[1]);
    char* t = (char*)malloc((length+1) * sizeof(char));
    int k = 0;
    int i;
    int errorA;
    for(i = 0; i< strlen(argv[1]); i++){
        if(argv[1][i] == '(' || argv[1][i] == '{' || argv[1][i] == '['){
            t[k] = argv[1][i];
            k++;
        }
        else if( argv[1][i] == ')' || argv[1][i] == '}' || argv[1][i] == ']'){
            if(k == 0){
                errorA =1;
                k =i;
                t[k] = argv[1][i];
                break;
            }
            else if(argv[1][i] == ')'){ 
                if(t[k-1] == '('){
                        k = k-1;
                    }
                
                else{
                    errorA =1;
                    k =i;
                    t[k] = argv[1][i];
                    break;
                }
            }
            else if(argv[1][i] == '}'){
                if(t[k-1] == '{'){
                        k = k-1;
                    }
                
                else{
                    errorA =1;
                    k =i;
                    t[k] = argv[1][i];
                    break;
                }
            }
            else{
                if(t[k-1] == '['){
                    k = k-1;
                    }
                
                else{
                    errorA =1;
                    k =i;
                    t[k] = argv[1][i];
                    break;
                }
             }
        }
        else{
            continue;
        }
        }
    if(k == 0 && i == strlen(argv[1])){
        free(t);
        return EXIT_SUCCESS;        
    }
    
    else if(errorA == 1){
        printf("%d: %c\n", i, t[i]);
        free(t);
        return EXIT_FAILURE;
    }
    else if(k > 0 && i == strlen(argv[1])){
        int r;
        printf("open: ");
        for(r = (k-1); r >= 0; r--){
            if(t[r] == '('){
                printf(")");
            }
            else if(t[r] == '{'){
                printf("}");
            }
            else{
                printf("]");
            }
        }
    printf("\n");
    free(t);
    return EXIT_FAILURE;
    }
    else{
        printf("error");
        free(t);
        return EXIT_FAILURE;
    }

    }
    

