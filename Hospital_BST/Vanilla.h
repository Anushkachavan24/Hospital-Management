#ifndef VANILLA_H_INCLUDED
#define VANILLA_H_INCLUDED

typedef struct hospital{
    long int phone;
    int ID;
    int age;
    char *name;
    char *gender;
}hospital;

typedef struct node{
    int key;
    hospital info;
    struct node *left;
    struct node *right;
    struct node *parent;
}node;

typedef node *BST;

void init(BST *);

void AdmitPatient(BST *, int, hospital);

node *SearchPatient(BST *, int);

void Display(BST);

void DischargePatient(BST *, int);


#endif //VANILLA_H_INCLUDED
