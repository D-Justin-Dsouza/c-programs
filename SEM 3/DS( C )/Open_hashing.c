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
    for (int i = 0; i < MAX; i++) {
        printf("%-2d", i);
        if (table[i].status == OCCUPIED) {
            printf("|%5d|", table[i].key);
        } else if (table[i].status == DELETED) {
            printf("|DELETED|");
        } else {
            printf("|EMPTY|");
        }
        printf("\n");
    }
}

void display_separate_chaining(struct record *table[]) {
    struct record *ptr;
    for (int i = 0; i < MAX; i++) {
        printf("\n[%d]", i);
        if (table[i] != NULL) {
            ptr = table[i];
            while (ptr != NULL) {
                printf("%d->", ptr->key);
                ptr = ptr->next;
            }
        }
    }
    printf("\n");
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
            printf("Record inserted at location %d\n", loc);
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
        if (ptr->key == key) {
            return h;
        }
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
    int choice, key;
    for (int i = 0; i < MAX; i++) {
        table1[i].status = EMPTY;
        table2[i] = NULL;
    }
    while (1) {
        printf("\n1. Insert using double hashing\n");
        printf("2. Search using double hashing\n");
        printf("3. Delete using double hashing\n");
        printf("4. Display using double hashing\n");
        printf("5. Insert using separate chaining\n");
        printf("6. Search using separate chaining\n");
        printf("7. Delete using separate chaining\n");
        printf("8. Display using separate chaining\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insert_double_hashing(table1, key);
                break;
            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                if (search_double_hashing(table1, key) == -1)
                    printf("Key not found\n");
                else
                    printf("Key found\n");
                break;
            case 3:
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                delete_double_hashing(table1, key);
                break;
            case 4:
                display_double_hashing(table1);
                break;
            case 5:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insert_separate_chaining(table2, key);
                break;
            case 6:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                if (search_separate_chaining(table2, key) == -1)
                    printf("Key not found\n");
                else
                    printf("Key found\n");
                break;
            case 7:
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                delete_separate_chaining(table2, key);
                break;
            case 8:
                display_separate_chaining(table2);
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
