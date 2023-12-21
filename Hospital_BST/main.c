#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Vanilla.h" 

int main(){
     BST T;
     hospital h;
     int choice;
     FILE *fp = fopen("HospitalData.csv", "r");
     if(fp == NULL)
         printf("unable to open");
     char line[200];
     int column = 0, no, del, ser;
     node *k;
     char *token, *mob;
     static int row = 0;
     char name[40] = {'\0'};
     char *gender = (char *)malloc(sizeof(char));
     init(&T);
     long int phone;
     fgets(line, sizeof(line), fp);
     while(1){
           printf("\n\n\t\t\t\t================================HOSPITAL MANAGEMENT SYSTEM================================\n\n");
                
           printf("1. Admit a new patient\n");
           printf("2. Search the patient\n");
           printf("3. Discharge a patient\n");
           printf("4. Display the patient's data\n");
           printf("5. Exit\n");
           
           printf("Enter your choice:\n");
           scanf("%d", &choice);
           
          
           switch(choice){
                case 1:
                    system("clear");
                    row++;
                    fgets(line, sizeof(line), fp);
                    column = 0;
                    token = strtok(line, ",");
                    while(token != NULL){
                         if(column == 0){
                              printf("Serial No: ");
                              no = atoi(token);
                              printf("%d\n", no);
                         }
                         if(column == 1){
                              printf("Name: ");
                              strcpy(name, token);
                              printf("%s\n",name);
                         }
                         if(column == 2){
                              printf("Age: ");
                              h.age = atoi(token);
                              printf("%d\n", h.age);
                         }
                         if(column == 3){
                              printf("Mobile No: ");
                              phone = strtol(token, &mob, 10);
                              printf("%ld\n", phone);
                         }
                         if(column == 4){
                              printf("Gender: ");
                              strcpy(gender, token);
                              printf("%s\n", gender);
                         }
                         if(column == 5){
                              printf("ID No: ");
                              h.ID = atoi(token);
                              printf("%d\n", h.ID);
                         }
                         token = strtok(NULL, ",");
                         column++;          
                    }
                    printf("\n");
                    h.name = name;
                    h.gender = gender;
                    h.phone = phone;
                    AdmitPatient(&T, no, h);
                    break;
                case 2:
                    system("clear");
                    printf("Enter the patient number:");
                    scanf("%d", &ser);
                    k = SearchPatient(&T, ser);
                    if(k != NULL){
                        printf("Found 1\n\nSr. No: %d\n", k->key);
                        printf("Pateint's name: %s\n", k->info.name);
                        printf("Pateint's age: %d\n", k->info.age);
                        printf("Pateint's gender: %s\n", k->info.gender);
                        printf("Pateint's ID: %d\n", k->info.ID);
                        printf("Pateint's mobile No: %ld\n", k->info.phone);
                    }
                    else{
                        printf("Patient Not Found 0\n");
                    }
                    break;
                case 3:
                    system("clear");
                    printf("Enter the patient number:");
                    scanf("%d", &del);
                    DischargePatient(&T, del); 
                    break;
                case 4:
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\tPATIENT DETAILS\n");
                    Display(T);
                    break;
                case 5:
                    system("clear");
                    exit(1);
                default:
                    system("clear");
                    printf("Wrong choice");           } 
     }
     return 0;
}
