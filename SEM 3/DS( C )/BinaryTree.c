#include <stdio.h>
#include <stdlib.h>

struct listNode {
    char info;
    struct listNode *next;
} *preptr = NULL, *inptr = NULL, *postptr = NULL;

struct treeNode {
    struct treeNode *lchild;
    char info;
    struct treeNode *rchild;
};

struct treeNode *constructINPRE(struct listNode *preptr, struct listNode *inptr, int n) {
    if (n <= 0 || preptr == NULL)
        return NULL;

    struct treeNode *root = (struct treeNode *)malloc(sizeof(struct treeNode));
    root->info = preptr->info;
    root->lchild = root->rchild = NULL;

    if (n == 1)
        return root;

    struct listNode *in = inptr;
    int leftTreeSize = 0;
    while (in != NULL && in->info != root->info) {
        leftTreeSize++;
        in = in->next;
    }

    if (in == NULL) {
        printf("\nTraversals don't match\n");
        exit(1);
    }

    int rightTreeSize = n - leftTreeSize - 1;
    root->lchild = constructINPRE(preptr->next, inptr, leftTreeSize);

    struct listNode *rightIn = in->next;
    struct listNode *nextPreptr = preptr;
    for (int i = 0; i <= leftTreeSize; i++)
        nextPreptr = nextPreptr->next;

    root->rchild = constructINPRE(nextPreptr, rightIn, rightTreeSize);
    return root;
}

struct treeNode *constructINPOS(struct listNode *postptr, struct listNode *inptr, int n) {
    if (n == 0 || postptr == NULL || inptr == NULL)
        return NULL;

    struct listNode *p = postptr;
    for (int i = 1; i < n; i++) {
        p = p->next;
    }

    struct treeNode *tmp = (struct treeNode *)malloc(sizeof(struct treeNode));
    tmp->info = p->info;
    tmp->lchild = tmp->rchild = NULL;

    if (n == 1)
        return tmp;

    struct listNode *q = inptr;
    int i = 0;
    while (q != NULL && q->info != p->info) {
        i++;
        q = q->next;
    }

    tmp->lchild = constructINPOS(postptr, inptr, i);

    struct listNode *postptrRight = postptr;
    for (int j = 0; j < i; j++) {
        postptrRight = postptrRight->next;
    }

    tmp->rchild = constructINPOS(postptrRight, q->next, n - i - 1);
    return tmp;
}

void sp(int n) {
    for (int i = 0; i < n; i++)
        printf(" ");
}

void printTree(struct treeNode *root, int d, char e) {
    if (root == NULL) {
        sp(4 * d);
        printf("~\n");
        return;
    }

    printTree(root->rchild, d + 1, '/');
    sp(4 * d);
    printf("%c--%c\n", e, root->info);
    printTree(root->lchild, d + 1, '\\');
}

struct listNode *createList(const char *str) {
    struct listNode *head = NULL, *tail = NULL;
    while (*str) {
        struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));
        newNode->info = *str;
        newNode->next = NULL;

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        str++;
    }
    return head;
}

int countNodes(struct listNode *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

int main() {
    const char *preorder = "ABDECFG";
    const char *inorder = "DBEAFCG";
    const char *postorder = "DEBFGCA";

    preptr = createList(preorder);
    inptr = createList(inorder);
    postptr = createList(postorder);

    int n = countNodes(inptr);

    printf("Constructing tree from Inorder and Preorder:\n");
    struct treeNode *root1 = constructINPRE(preptr, inptr, n);
    printTree(root1, 0, 'R');

    printf("\nConstructing tree from Inorder and Postorder:\n");
    struct treeNode *root2 = constructINPOS(postptr, inptr, n);
    printTree(root2, 0, 'R');

    return 0;
}
