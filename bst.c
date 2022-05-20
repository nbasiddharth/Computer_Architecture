#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right; 
};
struct Node* root = NULL;
struct Node* insert(int n, struct Node* start, int* a){
    if(start == NULL){
        struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
        temp -> data =  n;
        temp -> left = NULL;
        temp -> right = NULL;
        start = temp;
    }
    else if(n < start ->data){
        start -> left = insert(n,start -> left,a);
    }
    else if(n > start -> data){
        start -> right = insert(n, start -> right,a);
    }
    else{
        *a = 1;
    }
    return start;
}
void search(int n, struct Node* start, int* a){
    if(start == NULL){
        ;
    }
    else if(n < start ->data){
        search(n,start -> left,a);
    }
    else if(n > start -> data){
        search(n, start -> right,a);
    }
    else{
        *a = 1;
    }
}
void delete(struct Node* begin, int num, int* a, int* b){
    if(begin == NULL){
        ;
    }
    else if(begin == root && *b == 1){
        if(*a == 1){
            struct Node* temp;
            temp = root;
            root = NULL;
            free(temp);
            *a = 0;
        }
        else if(*a == 2){
            struct Node* temp;
            temp = begin;
            root = begin -> right;
            free(temp);
            *a =0;
        }
        else{
            struct Node* temp;
            temp = begin;
            root = begin -> left;
            free(temp);
            *a =0;
        }

    }
    else if(num < begin -> data){
        delete(begin -> left, num,  a, b);
        if(*a == 1){
            struct Node* temp;
            temp = begin -> left;
            begin -> left = NULL;
            free(temp);
            *a = 0;
        }
        else if(*a == 2){
            struct Node* temp;
            temp = begin -> left;
            begin -> left = (begin -> left) -> right;
            free(temp);
            *a = 0;
        }
        else if(*a == 3){
            struct Node* temp;
            temp = begin -> left;
            begin -> left = (begin -> left) -> left;
            free(temp);
            *a =0;
        }
        else{
            ;
        }
    }
    else if(num > begin -> data){
        delete(begin -> right, num, a, b);
        if(*a == 1){
            struct Node* temp;
            temp = begin -> right;
            begin -> right = NULL;
            free(temp);
        }
        else if(*a == 2){
            struct Node* temp;
            temp = begin -> right;
            begin -> right = (begin -> right) -> right;
            free(temp);
        }
        else if(*a == 3){
            struct Node* temp;
            temp = begin -> right;
            begin -> right = (begin -> right) -> left;
            free(temp);
        }
        else{
            ;
        }
    }
    else{
        *b = 1;
        if(begin -> left == NULL && begin -> right == NULL){
            *a = 1;
            if(begin == root){
                delete(root, num, a,b);
            }
        }
        else if(begin -> left == NULL){
            *a = 2;
            if(begin == root){
                delete(root, num, a, b);
            }
        }
        else if(begin -> right == NULL){
            *a = 3;
            if(begin == root){
                delete(root, num, a, b);
            }
        }
        else{
            struct Node* x = begin -> left;
            struct Node* y = begin;
            while(x -> right != NULL){
                y = x;
                x = x-> right;
            }
            begin -> data = x -> data;
            struct Node* temp;
            temp = x;
            if( y == begin){
                y -> left  = x -> left;
                free(temp);
            }
            else{            
                y -> right = x -> left;
                free(temp);
            }
        }
    }
}

void print(struct Node* head){
    if(head == NULL){
        ;
    }
    else{
        printf("(");
        print(head -> left);
        printf("%d", head -> data);
        print(head -> right);
        printf(")");
    }
}
void freedom(struct Node* top){
     if(top == NULL){
        ;
    }
    else{
        freedom(top -> left);
        freedom(top -> right);
        free(top);
    }
}
int main(int argc, char **argv){
    char letter;
    int num;
    int counter = 0;
    int check = 0;
    while(1){
        if(scanf("\n%c", &letter) == -1){
            break;
        }
        if(letter != 'p'){
            if(scanf("%d", &num) == -1){
                break;
            }
        }
        if(letter == 'i'){
            root = insert(num, root, &counter);
            if(counter != 1){
                printf("inserted\n");
            }
            else{
                printf("not inserted\n");
            }
            counter = 0;
        }
        else if(letter == 'p'){   
            print(root);
            printf("\n");
        
        }
        else if(letter == 's'){
            search(num, root, &counter);
            if(counter == 1){
                printf("present\n");
            }
            else{
                printf("absent\n");
            }
            counter =0;
        }
        else if(letter == 'd'){
            delete(root, num, &counter, &check);
            if(check == 1){
                printf("deleted\n");
            }
            else{
                printf("absent\n");
            }
            counter = 0;
            check = 0;
        }
      
        else{
            continue;
        }
            
    }
    freedom(root);
    return 0;

}