#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node{
    int data;
    struct Node *next;
};
struct Node* first = NULL;
struct Node* t = NULL;
struct Node* trail = NULL;
void insert(int n, int* a, int size){
        int nothing =0;
        if(size == 0){
           struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
           temp -> data = n;
           temp -> next = NULL;
           first = temp;
        }
        else{
        t = first;
        trail = first;
        while(t -> next != NULL){
            if(t -> data < n){
                trail = t;
                t = t -> next;
            }
            else if( t-> data == n){
                nothing = 1;
                break;
            }
            else{
                break;
            }
        }
        if(nothing == 0){
            if(n > (t -> data)){
                struct Node* create = (struct Node*)malloc(sizeof(struct Node));
                create -> data = n;
                create -> next = t -> next;
                t -> next = create;
            }
            else if(t -> data > n){
                struct Node* create = (struct Node*)malloc(sizeof(struct Node));
                if(t == first){
                    create -> data = n;
                    create -> next = t;
                    first = create;
                }
                else{
                    create -> data = n;
                    create -> next = t;
                    trail -> next = create;
                }
            }
                else{
                    *a =1;
                }
            }
            else {
                *a = 1;
            }
            }
}

void delete(int k, int* b, int length){
    int match = 0;
    t = first;
    trail = first;
    if(length > 0){
        while( t != NULL){
            if(t -> data < k){
                trail = t;
                t = t-> next;
            }
            else if(t -> data == k){
                match =1;
                break;
            }
            else{
                break;
            }

        }
        if(match == 1){
            struct Node *temp;
            if(length == 1){
                temp = t;
                first = NULL;
                free(temp);
            }   
            else{
                if(t == first){
                    temp = t;
                    first = t-> next;
                    free(temp);
                }
                else{
                    temp = t;
                    trail -> next = t -> next;
                  //  printf("%d", temp -> data);
                    free(temp);
                }
            }
        }
        else{
            *b = 1;
        }
    }
}
int main(int argc, char **argv){
    struct Node *tracker;
    int counter = 0;
    int num;
    char letter;
    int length =0;
    while(1){
        if(scanf("\n%c %d",&letter, &num) == -1){
            break;
        }
        if(letter == 'i'){
            insert(num, &counter, length);
            if(counter != 1){
                length++;
            }
            else{
                counter = 0;
            }
            printf("%d :", length);
            tracker = first;
            while(tracker != NULL){
                printf(" %d", tracker -> data);
                tracker = tracker -> next;
            }
            printf("\n");
            tracker = first;
        }
        else if(letter == 'd'){
            delete(num, &counter, length);
            if(counter != 1){
                if(length > 0){
                    length--;
                }
            }
            else{
                counter = 0;
            }
            tracker = first;
            printf("%d :", length);
            while(tracker != NULL){
                printf(" %d", tracker -> data);
                tracker = tracker -> next;
            }
            printf("\n");
            tracker = first;
        }
        else{
            continue;
        }
            
    }
        
   struct Node *follow;
   while(first != NULL){
        follow = first;
        first = first -> next;
      //  printf("%d\n", follow -> data);
        free(follow);
    }
    return 0;

}