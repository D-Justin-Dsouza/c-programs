
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 7
enum type_of_record{EMPTY, DELETED, OCCUPIED};
struct record{
    int key;
    enum type_of_record status;
};
struct record table1[MAX],table2[MAX];
void insert_linear_hashing(struct record table[], int key);
int search_linear_hashing(struct record table[], int key);
void delete_linear_hashing(struct record table[], int key);
void insert_quadratic_hashing(struct record table[],int key);
int search_quadratic_hashing(struct record table[],int key);
void delete_quadratic_hashing(struct record table[],int key);
void display(struct record table[]){
    for(int i=0;i<MAX;i++){
        printf("-------------\n");
        printf("|%-2d",i);
        if(table[i].status==OCCUPIED){
            printf("|%8d|",table[i].key);
        }
        else if(table[i].status==DELETED)
            printf("| DELETED|");
        else
            printf("|   EMPTY|");
        printf("\n");
    }
    printf("-------------\n");
}
int hash(int key){
    return key % MAX;
}
void insert_linear_hashing(struct record table[],int key){
    int i,h,loc;
    h=hash(key);
    loc=h;
    for(i=1;i!=MAX-1;i++){
        if(table[loc].status==EMPTY || table[loc].status==DELETED){
            table[loc].key=key;
            table[loc].status=OCCUPIED;
            return;
        }
        if(table[loc].key==key){
            printf("Duplicate key\n");
            return;
        }
        loc=(h+i)%MAX;
    }
}
int search_linear_hashing(struct record table[],int key){
    int i,h,loc;
    h=hash(key);
    loc=h;
    for(i=1;i!=MAX-1;i++){
        if(table[loc].status==EMPTY)
            return -1;
        if(table[loc].key==key)
            return loc;
        loc=(h+i)%MAX;
    }
    printf("Key not found\n");
}
void delete_linear_hashing(struct record table[], int key){
    int loc=search_linear_hashing(table,key);
    if(loc==-1)
        printf("Key not found\n");
    else
        table[loc].status=DELETED;
}
void insert_quadratic_hashing(struct record table[],int key){
    int i,h,loc;
    h=hash(key);
    loc=h;
    for(i=1;i!=MAX-1;i++){
        if(table[loc].status==EMPTY || table[loc].status==DELETED){
            table[loc].key=key;
            table[loc].status=OCCUPIED;
            return;
        }
        if(table[loc].key==key){
            printf("Duplicate key\n");
            return;
        }
        loc=(h+(i*i))%MAX;
    }
}
int search_quadratic_hashing(struct record table[],int key){
    int i,h,loc;
    h=hash(key);
    loc=h;
    for(i=1;i!=MAX-1;i++){
        if(table[loc].status==EMPTY)
            return -1;
        if(table[loc].key==key)
            return loc;
        loc=(h+(i*i))%MAX;
    }
    printf("Key not found\n");
}
void delete_quadratic_hashing(struct record table[], int key){
    int loc=search_linear_hashing(table,key);
    if(loc==-1)
        printf("Key not found\n");
    else
        table[loc].status=DELETED;
}
int main(){
    int key;
    for(int i=0;i<MAX;i++){
        table1[i].status=EMPTY;
        table2[i].status=EMPTY;
    }
//    int keys[]={6822,1574,6443,4179,3067,3667,2051,4065,2661,1739};
  int keys[]={8293, 5341, 7624, 4917, 3281, 4532, 2078, 6116};
//  int keys[]={9254, 3378, 7842, 5631, 2947, 6195, 4520, 8391, 2104, 6782}
    printf("Keys are: ");
    for(int i=0;i<MAX;i++)
        printf("%d ",keys[i]);
    for(int i=0;i<MAX;i++){
        insert_linear_hashing(table1,keys[i]);
        insert_quadratic_hashing(table2,keys[i]);
    }
    printf("\nLinear Probing\n");
    display(table1);
    printf("\nQuadratic Probing\n");
    display(table2);
    return 0;
}
