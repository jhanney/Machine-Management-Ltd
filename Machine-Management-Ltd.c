#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//machine struct
typedef struct node {
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
}Machine;

//functiion to add new machine 
void addMachine(Machine** head) {
    Machine* newMachine = (Machine*)malloc(sizeof(Machine)); //create space for new machine

    printf("Enter chasis number: ");
    scanf("%s", newMachine->chassisNumber); 

    //identify if chasis number is unique
    Machine* tmp = *head; 
    while (tmp != NULL) {
        if (strcmp(tmp->chassisNumber, newMachine->chassisNumber) == 0) {
            printf("ERROR: Chasis number must be unique");
            free(newMachine); //free memeory
            return; 
        }
        tmp = tmp->next; 
    }

    //collect the rest of the machine data
    printf("Enter make: ");
    scanf("%s", newMachine->make);
    printf("Enter model: ");
    scanf("%s", newMachine->model);
    printf("Enter year of manufacture: ");
    scanf("%d", &newMachine->yearOfManufacture);
    printf("Enter cost: ");
    scanf("%f", &newMachine->cost);
    printf("Enter current valuation: ");
    scanf("%f", &newMachine->currentValuation);
    printf("Enter current mileage: ");
    scanf("%d", &newMachine->currentMileage);
    printf("Enter next service mileage: ");
    scanf("%d", &newMachine->nextServiceMileage);
    printf("Enter owner name: ");
    scanf("%s", newMachine->ownerName);
    printf("Enter owner email: ");
    scanf("%s", newMachine->ownerEmail);
    printf("Enter owner phone number: ");
    scanf("%s", newMachine->ownerPhoneNumber);
    printf("Enter machine type (e.g., Tractor): ");
    scanf("%s", newMachine->machineType);
    printf("Enter breakdown count this year: ");
    scanf("%d", &newMachine->breakdownsThisYear);

    //insert new machine at begginning 
    newMachine->next = *head; 
    *head = newMachine; 
}

void displayAll(Machine* head) {
    Machine* temp = head; 
    while (temp != NULL) {
        printf("\nChassis Number: %s\n", temp->chassisNumber);
        printf("Make: %s\n", temp->make);
        printf("Model: %s\n", temp->model);
        printf("Year: %d\n", temp->yearOfManufacture);
        printf("Cost: %.2f\n", temp->cost);
        printf("Current Valuation: %.2f\n", temp->currentValuation);
        printf("Current Mileage: %d\n", temp->currentMileage);
        printf("Next Service Mileage: %d\n", temp->nextServiceMileage);
        printf("Owner: %s\n", temp->ownerName);
        printf("Owner Email: %s\n", temp->ownerEmail);
        printf("Owner Phone: %s\n", temp->ownerPhoneNumber);
        printf("Machine Type: %s\n", temp->machineType);
        printf("Breakdowns This Year: %d\n", temp->breakdownsThisYear);
        temp = temp->next;
    }
}

void main()
{
	int choice = 0; 
    Machine* head = NULL; 

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
            addMachine(&head); 
            break;

        case 2:
            printf("\nDisplay all machines selected\n");
            displayAll(head); 
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

