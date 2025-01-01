#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    struct node *left;
    bool lthread;
    int info;
    bool rthread;
    struct node *right;
};
struct node *case_c(struct node *root,struct node *par,struct node *ptr);
struct node *case_b(struct node *root,struct node *par,struct node *ptr);
struct node *case_a(struct node *root, struct node *par, struct node *ptr);

struct node *in_succ(struct node *ptr){
    if(ptr->rthread==true)
        return ptr->right;
    else{
        ptr=ptr->right;
        while(ptr->lthread==false){
            ptr=ptr->left;
        }
        return ptr;
    }
}
struct node *in_pred(struct node *ptr){
    if(ptr->lthread)
        return ptr->left;
    else{
        ptr=ptr->left;
        while(ptr->rthread==false)
            ptr=ptr->right;
        return ptr;
    }
}

struct node *insert(struct node *root,int ikey){
    struct node *tmp,*par,*ptr;
    int found=0;
    ptr=root;
    par=NULL;
    while(ptr!=NULL){
        if(ikey==ptr->info){
            found=1;
            break;
        }
        par=ptr;
        if(ikey<ptr->info){
            if(ptr->lthread==false)
                ptr=ptr->left;
            else
                break;
        }
        else{
            if(ptr->rthread==false)
                ptr=ptr->right;
            else
                break;
        }
    }
    if(found)
        printf("\nDuplicate Key");
    else{
        tmp=(struct node *)malloc(sizeof(struct node));
        tmp->info=ikey;
        tmp->lthread=tmp->rthread=true;

        if(par==NULL){
            root=tmp;
            tmp->left=tmp->right=NULL;
        }
        else if(ikey<par->info){
            tmp->left=par->left;
            tmp->right=par;
            par->lthread=false;
            par->left=tmp;
        }
        else{
            tmp->right=par->right;
            tmp->left=par;
            par->rthread=false;
            par->right=tmp;
        }
    }
    return root;
}
struct node *search(struct node *root,int skey){
    struct node *ptr=root;
    while(ptr!=NULL){
        if(skey==ptr->info)
            return ptr;
        else if(skey<ptr->info){
            if(ptr->lthread==false)
                ptr=ptr->left;
            else
                return NULL;
        }
        else{
            if(ptr->rthread==false)
                ptr=ptr->right;
            else
                return NULL;
        }
    }
    return NULL;
}
struct node *del(struct node *root, int dkey){
    struct node *par,*ptr;
    int found=0;
    ptr=root;
    par=NULL;
    while(ptr!=NULL){]
        if(dkey==ptr->info){
            found=1;
            break;
        }
        par=ptr;
        if(dkey<ptr->info){
            if(ptr->lthread==false)
                ptr=ptr->left;
            else
                break;
        }
        else{
            if(ptr->rthread==false)
                ptr=ptr->right;
            else
                break;
        }
    }
    if(found==0)
        printf("Element not found");
    else if(ptr->lthread==false && ptr->rthread==false)
        root=case_c(root,par,ptr);
    else if(ptr->lthread==false || ptr->rthread==false)
        root=case_b(root,par,ptr);
    else
        root=case_a(root,par,ptr);
    return root;
}
struct node *case_a(struct node *root, struct node *par, struct node *ptr){
    if(ptr==NULL)
        root=NULL;
    else if(par->left==ptr){
        par->lthread=true;
        par->left=ptr->left;
    }
    else{
        par->rthread=true;
        par->right=ptr->right;
    }
    free(ptr);
    return root;
}
struct node *case_b(struct node *root,struct node *par,struct node *ptr){
    struct node *child, *p,*s;
    if(ptr->lthread ==false)
        child=ptr->left;
    else
        child=ptr->right;
    if(par==NULL)
        root=child;
    else if(par->left==ptr)
        par->left=child;
    else
        par->right=child;
    s=in_succ(ptr);
    p=in_[red(ptr];
    if(ptr->lthread==false)
        p->right=s;
    else if(ptr->rthread==false)
        s->left=p;
    free(ptr);
    return root;
}
struct node *case_c(struct node *root,struct node *par,struct node *ptr){
    struct node *succ, *parsucc;
    parsucc=ptr;
    succ=ptr->right;
    while(succ->left!=NULL){
        parsucc=succ;
        succ=succ->left;
    }
    ptr->info=succ->info;
    if(succ->lthread==true && succ->rthread==true)
        root=case_a(root,parsucc,succ);
    else
        root=case_b(root,parsucc,succ);
    return root;
}
