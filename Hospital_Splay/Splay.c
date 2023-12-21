#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Splay.h" 

void splay_node(splay *, node *);

node *newPatient(int, hospital);

void Rightrotation(splay *, node *);

void Leftrotation(splay *, node *);

node *smallestnode(splay );


void init(splay *T){
     *T = NULL;
     return;
};

void Rightrotation(splay *T, node *a){
     node* b= a->left;
     node *br=NULL, *ap=NULL;
	
     if (a==(*T))//if a is root node
	 (*T)=b;
     if(b->right)//when b->right is present
	 br = b->right;
	
     if(a->parent)//if a is not root node	
	 ap = a->parent;
     if(ap){ // check if a is left or right child of ap
	 if(ap->left == a)
	     ap->left = b;
	 else
	     ap->right = b;
     }
     b->parent = ap;
     b->right = a;
     a->left = br;
     a->parent = b;
	
     if(br)//when b->right is present
	 br->parent=a;
     return;	
}

void Leftrotation(splay *T, node *a){
     node *b = a->right;
     node *bl=NULL, *ap=NULL;
	
     if(a==(*T))//if a is root node
	(*T)=b;
		
     if(b->left)//when b->left is present
	bl=b->left;
	
     if(a->parent)//when a is not root node
	ap=a->parent;
     if(ap){// check if a is left or right child of ap
	if(ap->left == a)
	    ap->left = b;
	else
	    ap->right = b;
     }
     b->parent=ap;
     b->left=a;
     a->right=bl;
     a->parent=b;
	
     if(bl)//when b->left is present
	bl->parent=a;
		
     return;
}


void splay_node(splay *T, node *n){
      while(n->parent != NULL){
            if(n->parent == (*T)){
                 if((n->parent)->left == n){
                      Rightrotation(&(*T), n->parent);
                      return;
                 }
                 else{
                     Leftrotation(&(*T), n->parent);
                     return;
                 }
            }
            else{
                 node *p = n->parent;
                 node *gp = p->parent;
                 if((p->left == n) && (gp->left == p)){
                     Rightrotation(&(*T), gp);
                     Rightrotation(&(*T), p);
                 }
                 else if((p->right == n) && (gp->right == p)){
                     Leftrotation(&(*T), gp);
                     Leftrotation(&(*T), p);
                 }
                 else if((p->left == n) && (gp->right == p)){
                     Rightrotation(&(*T), p);
                     Leftrotation(&(*T), gp);
                 }
                 else{
                     Leftrotation(&(*T), p);
                     Rightrotation(&(*T), gp);
                 } 
                            
            }
       }
       return;
}

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

void AdmitPatient(splay *T, int key, hospital H){
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
    
    splay_node(&(*T), nn);
    return;       
}





node *SearchPatient(splay *T, int d){
    node *p = *T;
    node *q = NULL;
    int count = 0;
    while(p != NULL){
        if(p->key == d){
           splay_node(&(*T), p);//Splay the searched node to root
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
    splay_node(&(*T), q);//if node not found splay the last accessed node to search
    return NULL;
}



node *smallestnode(splay T){
    while(T->left != NULL){
        T = T->left;
    }
    return T;
};



void DischargePatient(splay *T, int d){
      if((*T) == NULL)
          return;
      node *p = *T;
      node *q = NULL;
      //Search the node in Splay tree
      while(p != NULL){
          if(p->key == d)
             break;
          q = p;   
          if(p->key > d)
             p = p->left;
          else
             p = p->right;
      }
      //If node not found then splay the parent node and return
      if(p == NULL){
          splay_node(&(*T), q);// if node is not present then splay the last accessed node to search
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
      splay_node(&(*T), q);//After deleting splay the parent of deleted node to root
      
      return;	
}


void Display(splay T){
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
}
















