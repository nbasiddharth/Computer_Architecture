#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv){
    int i;
    if(argc < 2){
        return 0;
    }
    else if(argv[1][0] == '\0'){
        return 0;
    }
    else if(argv[1][0] == ' '){
        printf("! !\n");
    }

    else{
        i = 0;
        while(argv[1][i] != '\0'){
              printf("%c", toupper(argv[1][i])); 
              i++;
        }
        printf("!!\n");
        return 0;
    }
}
