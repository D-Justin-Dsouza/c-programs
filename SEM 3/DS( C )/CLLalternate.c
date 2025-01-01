#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* addEnd(struct node *last, int data) {
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    temp->data = data;
    if (last == NULL) {
        last = temp;
        last->next = last;
    } else {
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
    return last;
}

struct node* createList(struct node *last) {
    int data;
    printf("Enter number of nodes: ");
    int n;
    scanf("%d", &n);
    if (n == 0) return last;
    for (int i = 1; i <= n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &data);
        last = addEnd(last, data);
    }
    return last;
}

void display(struct node *last) {
    if (last == NULL) {
        printf("List is empty\n");
        return;
    }
    struct node *p = last->next;
    do {
        printf("|%3d|%03d| -> ", p->data, (int)p->next%1000);
        p = p->next;
    } while (p != last->next);
    printf("\n<----------------------------------------------------------------\n");
}
struct node *delAlt(struct node *last) {
    if (last == NULL || last->next == last)
        return last;
    struct node *p = last->next, *q;
    do {
        q = p->next;
        if (q == last)
            last = p;
        p->next = q->next;
        free(q);
        p = p->next;
    } while (p != last->next && p->next != last->next);
    return last;
}

int main() {
    struct node *last = NULL;
    last = createList(last);
    printf("Original list:\n ");
    display(last);
    last = delAlt(last);
    printf("List after deleting alternate nodes: \n");
    display(last);
    return 0;
}
