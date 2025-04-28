#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

void main()
{
	int choice = 0; 

	printf("\n=========================================\n");
	printf("   MACHINERY MANAGEMENT FLEET SYSTEM\n");
	printf("=========================================\n");

	do {
        printf("\nMAIN MENU:\n");
        printf("1) Add machine\n");
        printf("2) Display all machines to screen\n");
        printf("3) Display machine details\n");
        printf("4) Update a machine's details\n");
        printf("5) Delete machine\n");
        printf("6) Generate statistics\n");
        printf("7) Print all machine details into a report file\n");
        printf("8) List all the machinery in order of current valuation\n");
        printf("0) Exit\n");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);
    } while (choice != 0); 
}