#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Vanilla.h"

node *smallestnode(BST);

node *newPatient(int, hospital);
 

void init(BST *T){
     *T = NULL;
     return;
};


struct node *newPatient(int key, hospital H){
     node *temp = (node *)malloc(sizeof(node));
     if(temp == NULL)
        return NULL;
     temp->key = key;
     char *name = calloc(1,sizeof(char));
     strcpy(name, H.name);
     temp->info.name = name;
     temp->info.age = H.age;
     temp->info.ID = H.ID;
     temp->info.phone = H.phone;
     temp->info.gender = H.gender;
     temp->left = NULL;
     temp->right = NULL;
     temp->parent = NULL;
     return temp;
};

void AdmitPatient(BST *T, int key, hospital H){
     node *nn = (node *)malloc(sizeof(node));
     if(nn == NULL)
        return;
     nn = newPatient(key, H);
     if((*T) == NULL){
        nn->parent = NULL;
        (*T) = nn;
        return;
     }
    
     node *p = *T;
     node *q = NULL;
     while(p != NULL){
         if(p->key == nn->key){
            free(nn);
            return;  
         }
         q = p;
         if(p->key < nn->key)
            p = p->right;
         else
            p = p->left;
    }
    nn->parent = q;
    if(q->key > nn->key)
        q->left = nn;
    else
        q->right = nn;
    return;       
}





node *SearchPatient(BST *T, int d){
    node *p = *T;
    node *q = NULL;
    int count = 0;
    while(p != NULL){
        if(p->key == d){
           printf("Level number: %d\n", count);
           return p;  
        }
        q = p;
        if(p->key < d){
           p = p->right;
           count++;
        }
        else{
           p = p->left;
           count++;
        }
   }
   return NULL;
}


void postorder(BST T){
    if(T == NULL)
       return;
    printf("%d\n", T->key);
    postorder(T->left);
    postorder(T->right);
}

node *smallestnode(BST T){
    while(T->left != NULL){
        T = T->left;
    }
    return T;
};

void DischargePatient(BST *T, int d){
      if((*T) == NULL)
          return;
      node *p = *T;
      node *q = NULL;
      //Search the node in BST
      while(p != NULL){
          if(p->key == d)
             break;
          q = p;   
          if(p->key > d)
             p = p->left;
          else
             p = p->right;
      }
      //If node not found then return
      if(p == NULL){
          return;
      }
      //Remove a leaf node having no child
      else if(p->left == NULL && p->right == NULL){
        if((*T) == p){
           free(*T);
           *T = NULL;
           return;
        }
        if(p == q->left)
           q->left = NULL;
        else
           q->right = NULL;
        p->parent = NULL;
        free(p);
      }	
      //Remove a node having only one left child
      else if(p->left != NULL && p->right == NULL){
          if(p == (*T)){
             (*T) = (*T)->left;
             (*T)->parent = NULL;
             free(p);
             return;
          }
          if(p == q->left)
             q->left = p->left;
          else
             q->right = p->left;
          (p->left)->parent = q;
          free(p);
      }	
      //Remove a node having only one right child
      else if(p->left == NULL && p->right != NULL){
          if(p == (*T)){
             (*T) = (*T)->right;
             (*T)->parent = NULL;
             free(p);
             return;
          }
          if(p == q->left)
             q->left = p->right;
          else
             q->right = p->right;
          (p->right)->parent = q;
          free(p);
      }
      //Remove a node having both right and left children
      else{
          node *temp = smallestnode(p->right);
          p->key = temp->key;
          q = temp->parent;
          if(temp->right){
              if(temp == q->left)
                  q->left = temp->right;
              else
                  q->right = temp->right;
              (temp->right)->parent = q;
          }
          else{
               if(temp == q->left)
                  q->left = NULL;
               else
                  q->right = NULL;
          } 
          temp->parent = NULL;
          free(temp);
      }
      return;	
}

void Display(BST T){
     if(!T)
	 return;	
     Display(T->left);
     printf("Sr no: %d\n",T->key);
     printf("Pateint's name: %s\n", T->info.name);
     printf("Pateint's age: %d\n", T->info.age);
     printf("Pateint's gender: %s\n", T->info.gender);
     printf("Pateint's ID: %d\n", T->info.ID);
     printf("Pateint's mobile No: %ld\n", T->info.phone);
     printf("\n");
     Display(T->right);
     return;
}

















