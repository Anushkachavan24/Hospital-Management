#ifndef SPLAY_H_INCLUDED
#define SPLAY_H_INCLUDED

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

typedef node *splay;

void init(splay *);

void AdmitPatient(splay *, int, hospital);

node *SearchPatient(splay *, int);

void Display(splay);

void DischargePatient(splay *, int);

#endif //SPLAY_H_INCLUDED
