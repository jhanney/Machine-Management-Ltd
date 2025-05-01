#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//forward declarartion, i was getting an identifier error 2061
//only resolved when i did this
typedef struct Machine Machine;

//machine struct
 struct Machine{
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
    Machine* next;  //pointer to the next machine in the list
    Machine* prev; //points to previous machine in the list 
};

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

    //add machine type
    printf("Enter machine type (e.g., Tractor): ");
    scanf("%s", newMachine->machineType);
    printf("1) Tractor\n2) Excavator\n3) Roller\n4) Crane\n5) Mixer\n");
    int typecChoice;
    printf("Enter your choice (1-5): ");
    scanf("%d", &typecChoice); 




    printf("Enter breakdown count this year: ");
    scanf("%d", &newMachine->breakdownsThisYear);

    //insert new machine at begginning 
    newMachine->next = *head; 
    *head = newMachine; 
}

//method to display all machines 
void displayAll(Machine* head) {
    Machine* temp = head; //create temmp node at beginning 
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

//update the details of a machine
void updateMachine(Machine* head) {
    char chassis[20]; //chassis number to be compared

    printf("ENter the chassis number of the machine to update: ");
    scanf("%s", chassis); 

    Machine* temp = head; //node to traverse the linked list

    //traverse list to find match
    while (temp != NULL) {
        if (strcmp(temp->chassisNumber, chassis) == 0) {
            //allow details to be updated if match found 
            printf("Enter new make: ");
            scanf("%s", temp->make);
            printf("Enter new model: ");
            scanf("%s", temp->model);
            printf("Enter new year of manufacture: ");
            scanf("%d", &temp->yearOfManufacture);
            printf("Enter new cost: ");
            scanf("%f", &temp->cost);
            printf("Enter new valuation: ");
            scanf("%f", &temp->currentValuation);
            printf("Enter new mileage: ");
            scanf("%d", &temp->currentMileage);
            printf("Enter new next service mileage: ");
            scanf("%d", &temp->nextServiceMileage);
            printf("Enter new owner name: ");
            scanf("%s", temp->ownerName);
            printf("Enter new owner email: ");
            scanf("%s", temp->ownerEmail);
            printf("Enter new owner phone number: ");
            scanf("%s", temp->ownerPhoneNumber);
            printf("Enter new machine type (e.g., Tractor): ");
            scanf("%s", temp->machineType);
            printf("Enter new breakdown count this year: ");
            scanf("%d", &temp->breakdownsThisYear);

            return; 
        }
        temp = temp->next; //traverse to next node 
    }
    printf("Machine with chassis number %s not found!!\n", chassis); 
}

void deleteMachine(Machine** head) 
{
    char chasisToDelete[20]; 
    Machine* temp = *head; 

    printf("Enter the chasis number to delete: ");
    scanf("%s", chasisToDelete); 

    //check if list is empty
    if (*head == NULL) {
        printf("The machine list is empty.\n");
        return; 
    }

    //traverse list to find machine with matching chassis number
    while (temp != NULL) {
        //if matching chassis number is found
        if (strcmp(temp->chassisNumber, chasisToDelete) == 0) {
            //if the node to delete is the head
            if (temp == *head) {
                *head = temp->next; //move head node to the next node
                if (*head != NULL) {
                    (*head)->prev = NULL; //set prev pointer of head to NULL
                }
            }
            else {  //if node to delete is not the head
                if (temp->prev != NULL) {
                    temp->prev->next = temp->next;//link prev node to next node 
                }
                //link next node to prev node
                if (temp->next != NULL) {
                    temp->next->prev = temp->prev;
                }
            }
            free(temp); //free the memory
            printf("Machine with chassis number %s has been deleted.\n", chasisToDelete);
            return;
        }

        temp = temp->next;
    }

    //id machine not found 
    printf("Error: Machine with chassis number %s not found.\n", chasisToDelete);
}

//display a specific machines details 
void displayDetails(Machine* head) {
    char chassis[20];
    printf("Enter chassis number to display details of: ");
    scanf("%s", chassis); 


    Machine* temp = head;  

    while (temp != NULL) {
        if (strcmp(temp->chassisNumber, chassis) == 0) {
            // Display the machine details
            printf("\nChassis Number: %s\n", temp->chassisNumber);
            printf("Make: %s\n", temp->make);
            printf("Model: %s\n", temp->model);
            printf("Year of Manufacture: %d\n", temp->yearOfManufacture);
            printf("Cost: %.2f\n", temp->cost);
            printf("Current Valuation: %.2f\n", temp->currentValuation);
            printf("Current Mileage: %d\n", temp->currentMileage);
            printf("Next Service Mileage: %d\n", temp->nextServiceMileage);
            printf("Owner: %s\n", temp->ownerName);
            printf("Owner Email: %s\n", temp->ownerEmail);
            printf("Owner Phone: %s\n", temp->ownerPhoneNumber);
            printf("Machine Type: %s\n", temp->machineType);
            printf("Breakdowns This Year: %d\n", temp->breakdownsThisYear);
            return;
        }
        temp = temp->next; 
    }
    printf("Machine with chassis number %s not found!\n", chassis);

}

void generateStatistics(Machine* head) {
    int totalMachines = 0; 
    int noBreakdowns = 0; 

    Machine* temp = head; 

    while (temp != NULL) {
        totalMachines++; //if temp is not null increment machine count
        if (temp->breakdownsThisYear == 0) {
            noBreakdowns++; //increment if no breakdowns counted
        }
        temp = temp->next; //move to the next machine in the list
    }

    //print message if no machines found 
    if (totalMachines == 0) {
        printf("No machines found, unable to generate statistics");
    }

    printf("Total machines: %d\n", noBreakdowns);

    //num of machines with no breakdowns
    printf("Number of machines with no breakdowns: %d\n", noBreakdowns);

    //get the percentage of machines with no breakdowns
    //formula (moBreakdown / totalMachines) * 100
    printf("Percentage of machines with no breakdowns: %.2f%%\n", (float)noBreakdowns / totalMachines * 100); 
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
            displayDetails(head); 
            break;

        case 4:
            printf("\nUpdate machine selected\n");
            updateMachine(head);
            break;

        case 5:
            printf("\nDelete machine selected\n");
            deleteMachine(&head); 
            break;

        case 6:
            printf("\nGenerate statistics selected\n");
            generateStatistics(head); 
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


