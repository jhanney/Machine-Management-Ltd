#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

//machine struct
struct Machine {
    char chassisNumber[20];  //unique chassis number
    char make[30];
    char model[30];
    int yearOfManufacture;
    float cost;
    float currentValuation;
    int currentMileage;
    int nextServiceMileage;
    char ownerName[50];
    char ownerEmail[50];
    char ownerPhoneNumber[20];
    char machineType[20]; // e.g., Tractor, Excavator
    int breakdownsThisYear;
    struct Machine* next;  //pointer to the next machine in the list
};

void main()
{
	int choice = 0; 

	printf("\n=========================================\n");
	printf("   MACHINERY MANAGEMENT FLEET SYSTEM\n");
	printf("=========================================\n");

    //main menu
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

        // Process menu choice
        switch (choice) {
        case 1:
            printf("\nAdd machine selected\n");
            //implement addMachine() function here
            break;

        case 2:
            printf("\nDisplay all machines selected\n");
            //implement displayAllMachines() function here
            break;

        case 3:
            printf("\nDisplay machine details selected\n");
            //implement displayMachineDetails() function here
            break;

        case 4:
            printf("\nUpdate machine selected\n");
            //implement updateMachine() function here
            break;

        case 5:
            printf("\nDelete machine selected\n");
            //implement deleteMachine() function here
            break;

        case 6:
            printf("\nGenerate statistics selected\n");
            //implement generateStatistics() function here
            break;

        case 7:
            printf("\nPrint report selected\n");
            //implement printReport() function here
            break;

        case 8:
            printf("\nSort by valuation selected\n");
            //implement sortByValuation() function here
            break;

        case 0:
            printf("\nExiting program. Goodbye!\n");
            break;

        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 0); //loops until 0 selected

    return 0;
}

void addMachine() {

}