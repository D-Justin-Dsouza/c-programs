#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 7
enum type_of_record { EMPTY, DELETED, OCCUPIED };

struct record {
    int key;
    enum type_of_record status;
    struct record *next;
};
struct record table1[MAX], *table2[MAX];
void insert_double_hashing(struct record table[], int key);
int search_double_hashing(struct record table[], int key);
void delete_double_hashing(struct record table[], int key);
void insert_separate_chaining(struct record *table[], int key);
int search_separate_chaining(struct record *table[], int key);
void delete_separate_chaining(struct record *table[], int key);
void display_double_hashing(struct record table[]) {
    for(int i=0;i<MAX;i++){
        printf("-------------\n");
        printf("|%-2d",i);
        if(table[i].status==OCCUPIED)
            printf("|%8d|",table[i].key);
        else if(table[i].status==DELETED)
            printf("| DELETED|");
        else
            printf("|   EMPTY|");
        printf("\n");
    }
    printf("-------------\n");
}
void display_separate_chaining(struct record *table[]) {
    for(int i=0;i<MAX;i++){
        printf("\n%5s\n","-----");
        printf("|%-2d | -> ",i);
        if(table[i]!=NULL){
            struct record *ptr=table[i];
            while(ptr!=NULL){

                printf("|%5d| -> ",ptr->key);
                ptr=ptr->next;
            }
            printf("|NULL|");
            printf("\n%5s","-----");
        }
        else{
            printf("|EMPTY|");
            printf("\n%5s","-----");
        }
    }
}
int hash(int key) {
    return key % MAX;
}
int hashsec(int key) {
    return (5 + (key % 5));
}
void insert_double_hashing(struct record table[], int key) {
    int i, h, h_, loc;
    h = hash(key);
    h_ = hashsec(key);
    loc = h;
    for (i = 0; i < MAX; i++) {
        if (table[loc].status == EMPTY || table[loc].status == DELETED) {
            table[loc].key = key;
            table[loc].status = OCCUPIED;
            return;
        }
        if (table[loc].key == key) {
            printf("Duplicate key\n");
            return;
        }
        loc = (h + i * h_) % MAX;
    }
    printf("Table is full\n");
}
int search_double_hashing(struct record table[], int key) {
    int i, h, h_, loc;
    h = hash(key);
    h_ = hashsec(key);
    loc = h;
    for (i = 0; i < MAX; i++) {
        if (table[loc].status == EMPTY)
            return -1;
        if (table[loc].key == key)
            return loc;
        loc = (h + i * h_) % MAX;
    }
    return -1;
}
void delete_double_hashing(struct record table[], int key) {
    int loc = search_double_hashing(table, key);
    if (loc == -1) {
        printf("Record not found\n");
        return;
    }
    table[loc].status = DELETED;
}
void insert_separate_chaining(struct record *table[], int key) { // Correct function name
    int h;
    struct record *newrec;
    if (search_separate_chaining(table, key) != -1) {
        printf("Duplicate key\n");
        return;
    }
    h = hash(key);
    newrec = (struct record *)malloc(sizeof(struct record));
    newrec->key = key;
    newrec->next = table[h];
    table[h] = newrec;
}
int search_separate_chaining(struct record *table[], int key) {
    int h;
    struct record *ptr;
    h = hash(key);
    ptr = table[h];
    while (ptr != NULL) {
        if (ptr->key == key)
            return h;
        ptr = ptr->next;
    }
    return -1;
}
void delete_separate_chaining(struct record *table[], int key) {
    int h;
    struct record *temp, *ptr;
    h = hash(key);
    if (table[h] == NULL) {
        printf("Record not found\n");
        return;
    }
    if (table[h]->key == key) {
        temp = table[h];
        table[h] = table[h]->next;
        free(temp);
        return;
    }
    ptr = table[h];
    while (ptr->next != NULL) {
        if (ptr->next->key == key) {
            temp = ptr->next;
            ptr->next = temp->next;
            free(temp);
            return;
        }
        ptr = ptr->next;
    }
    printf("Record not found\n");
}
int main() {
    int key;
    for(int i=0;i<MAX;i++){
        table1[i].status=EMPTY;
        table2[i]=NULL;
    }
 // int keys[]={6822,1574,6443,4179,3067,3667,2051};
//    int keys[]={8293, 5341, 7624, 4917, 3281, 4532, 2078};
  int keys[]={9254, 3378, 7842, 5631, 2947, 6195, 4520};
    printf("Keys are: ");
    for(int i=0;i<MAX;i++){
        printf("%d ",keys[i]);
    }
    for(int i=0;i<MAX;i++){
        insert_double_hashing(table1,keys[i]);
        insert_separate_chaining(table2,keys[i]);
    }
    printf("Displaying Double hashing\n");
    display_double_hashing(table1);
    printf("Displaying Separate chaining\n");
    display_separate_chaining(table2);
    return 0;
}
