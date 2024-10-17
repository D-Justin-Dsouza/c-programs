
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
        printf("%-2d",i);
        if(table[i].status==OCCUPIED){
            printf("|%5d|",table[i].key);
        }
        else if(table[i].status==DELETED)
            printf("|DELETED|");
        else
            printf("|EMPTY|");
        printf("\n");
    }
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
            printf("Record inserted at location %d\n",loc);
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
            printf("Record inserted at location %d\n",loc);
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
    //menu driven for quadratic and linear hashing
    int choice,key;
    while(1){
        printf("1. Insert in linear hashing\n");
        printf("2. Search in linear hashing\n");
        printf("3. Delete in linear hashing\n");
        printf("4. Insert in quadratic hashing\n");
        printf("5. Search in quadratic hashing\n");
        printf("6. Delete in quadratic hashing\n");
        printf("7. Display\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter the key: ");
                scanf("%d",&key);
                insert_linear_hashing(table1,key);
                break;
            case 2:
                printf("Enter the key: ");
                scanf("%d",&key);
                search_linear_hashing(table1,key);
                break;
            case 3:
                printf("Enter the key: ");
                scanf("%d",&key);
                delete_linear_hashing(table1,key);
                break;
            case 4:
                printf("Enter the key: ");
                scanf("%d",&key);
                insert_quadratic_hashing(table2,key);
                break;
            case 5:
                printf("Enter the key: ");
                scanf("%d",&key);
                search_quadratic_hashing(table2,key);
                break;
            case 6:
                printf("Enter the key: ");
                scanf("%d",&key);
                delete_quadratic_hashing(table2,key);
                break;
            case 7:
                printf("Linear hashing\n");
                display(table1);
                printf("Quadratic hashing\n");
                display(table2);
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}