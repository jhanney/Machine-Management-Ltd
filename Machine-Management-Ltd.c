#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_CHASSIS_LENGTH 20
#define MAX_MAKE_LENGTH 30
#define MAX_MODEL_LENGTH 30
#define MAX_OWNER_NAME_LENGTH 50
#define MAX_OWNER_EMAIL_LENGTH 50
#define MAX_OWNER_PHONE_LENGTH 20
#define MAX_MACHINE_TYPE_LENGTH 20

//forward declarartion, i was getting an identifier error 2061
//only resolved when i did this
typedef struct Machine Machine;

//machine struct
 struct Machine{
    char chassisNumber[MAX_CHASSIS_LENGTH];  //unique chassis number
    char make[MAX_MAKE_LENGTH];
    char model[MAX_MODEL_LENGTH];
    int yearOfManufacture;
    float cost;
    float currentValuation;
    int currentMileage;
    int nextServiceMileage;
    char ownerName[MAX_OWNER_NAME_LENGTH];
    char ownerEmail[MAX_OWNER_EMAIL_LENGTH];
    char ownerPhoneNumber[MAX_OWNER_PHONE_LENGTH];
    char machineType[MAX_MACHINE_TYPE_LENGTH]; // e.g., Tractor, Excavator
    int breakdownsThisYear;
    Machine* next;  //pointer to the next machine in the list
    Machine* prev; //points to previous machine in the list 
};

 //login structure
 typedef struct {
     char username[7];//username (6 characters + null terminator)
     char password[7];//password (6 characters + null terminator)
 } Login;

 //function will read 3 login records (username and password) from the specified file
 void readLoginFile(Login loginRecords[3], const char* filename) {

     FILE* file = fopen(filename, "r");
     if (file == NULL) { 
         printf("Error opening login file!\n");
         exit(1);
     }

     //read 3 login records from the file (username and password)
     // reads 6 characters for the username and password each, since the max length is 6 (with null terminator)
     for (int i = 0; i < 3; i++) {
         fscanf(file, "%6s %6s", loginRecords[i].username, loginRecords[i].password);
     }

     //close the file after reading all the records
     fclose(file);
 }

 //function to mask password input with asterisks using scanf
     //this function hides the password input by showing asterisks (*) while the user types
 void getPassword(char* password) {
     char ch;
     int i = 0;

     //loop to read characters until the user types the password (max 6 characters)
     while (i < 6) {
         ch = getchar();  //read character from user input

         //if Enter key is pressed, finish the password input
         if (ch == '\n') {
             password[i] = '\0';  //null-terminate the password string
             break;
         }
         else {
             password[i] = ch;  //stre the character in the password array
             i++;  //move to the next character in the password
             printf("*");  //display an asterisk (*) for each character typed
         }
     }
     printf("\n");  // Move to the next line after the password input
 }


 //read machines from the file
 void readMachinesFromFile(Machine** head, const char* filename) {
     //open the file in read mode
     FILE* file = fopen(filename, "r");
     if (file == NULL) {
         //if the file cannot be opened, print an error message and return
         printf("Error opening file %s for reading!\n", filename);
         return;
     }

     //loop to read each line of the file until the end of the file is reached
     while (!feof(file)) {
         //assign memory for a new Machine node
         Machine* newMachine = (Machine*)malloc(sizeof(Machine));
         if (newMachine == NULL) {
             //ifmemory allocation fails, print an error message and close the file
             printf("Memory allocation failed!\n");
             fclose(file);
             return;
         }

         //read machine data from the file using fscanf
         //the format string specifies how to read each field in the line
         if (fscanf(file, "%19[^,],%29[^,],%29[^,],%d,%f,%f,%d,%d,%49[^,],%49[^,],%19[^,]\n",
             newMachine->make,                 //read all details
             newMachine->chassisNumber,
             newMachine->model,
             &newMachine->yearOfManufacture,
             &newMachine->cost,
             &newMachine->currentValuation,
             &newMachine->currentMileage,
             &newMachine->nextServiceMileage,
             newMachine->ownerName,
             newMachine->ownerEmail,
             newMachine->ownerPhoneNumber) != 11) {
             //ff the number of fields read is not 11, it means the line is not in the expected format
             free(newMachine); //free the allocated memory for the current machine
             break; //exit the loop
         }
         //add the new machine to the linked list
         newMachine->next = *head; //makw the new machine point to the current head of the list
         newMachine->prev = NULL;//the new machine doesn't have a previous node 
         if (*head != NULL) {
             //if the list is not empty, update the previous pointer of the current head to point to the new machine
             (*head)->prev = newMachine;
         }
         *head = newMachine; //update the head of the list to the new machine
     }
     
    
     //close the file after reading all the data
     fclose(file);
     printf("Machines data has been successfully loaded from the file.\n");
 }


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
    /*scanf("%s", newMachine->machineType);*/
    printf("1) Tractor\n2) Excavator\n3) Roller\n4) Crane\n5) Mixer\n");
    int typecChoice;
    printf("Enter your choice (1-5): ");
    scanf("%d", &typecChoice); 
    //swicth statement to track choice 
    switch (typecChoice) {
        //assign typechoice to machine string
    case 1: 
        strcpy(newMachine->machineType, "Tractor"); 
        break;
    case 2: 
        strcpy(newMachine->machineType, "Excavator"); 
        break;
    case 3: 
        strcpy(newMachine->machineType, "Roller");
        break;
    case 4: 
        strcpy(newMachine->machineType, "Crane"); 
        break;
    case 5: 
        strcpy(newMachine->machineType, "Mixer"); 
        break;
    default: printf("Invalid choice, defaulting to Tractor.\n"); strcpy(newMachine->machineType, "Tractor"); break;
    }



    //breakdown frequency 
    printf("Enter breakdown count this year: ");
   /* scanf("%d", &newMachine->breakdownsThisYear);*/
    printf("1) Never\n2) Less than three times\n3) Less than five times\n4) More than five times\n");
    int breakdownChoice;
    printf("Enter your choice (1-4): ");
    scanf("%d", &breakdownChoice);
    //switch statement for breakdown choice 
    switch (breakdownChoice) {
    case 1: 
        newMachine->breakdownsThisYear = 0; 
        break; //never
    case 2: 
        newMachine->breakdownsThisYear = 1; 
        break; //less than three times
    case 3: newMachine->breakdownsThisYear = 2; 
        break; //less than five times
    case 4: 
        newMachine->breakdownsThisYear = 3; 
        break; //more than five times
    default: printf("Invalid choice, defaulting to Never (0).\n"); newMachine->breakdownsThisYear = 0; break;
    }

    //insert new machine at the beginning
    newMachine->next = *head;
    if (*head != NULL) {
        (*head)->prev = newMachine; //set the prev pointer of the old head
    }
    *head = newMachine; 
}

//method to display all machines 
void displayAll(Machine* head, FILE* reportFile) {
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

        //print to file 
        fprintf(reportFile, "Chassis Number: %s\n", temp->chassisNumber);
        fprintf(reportFile, "Make: %s\n", temp->make);
        fprintf(reportFile, "Model: %s\n", temp->model);
        fprintf(reportFile, "Year of Manufacture: %d\n", temp->yearOfManufacture);
        fprintf(reportFile, "Cost: %.2f\n", temp->cost);
        fprintf(reportFile, "Current Valuation: %.2f\n", temp->currentValuation);
        fprintf(reportFile, "Current Mileage: %d\n", temp->currentMileage);
        fprintf(reportFile, "Next Service Mileage: %d\n", temp->nextServiceMileage);
        fprintf(reportFile, "Owner Name: %s\n", temp->ownerName);
        fprintf(reportFile, "Owner Email: %s\n", temp->ownerEmail);
        fprintf(reportFile, "Owner Phone: %s\n", temp->ownerPhoneNumber);
        fprintf(reportFile, "Machine Type: %s\n", temp->machineType);
        fprintf(reportFile, "Breakdowns This Year: %d\n\n", temp->breakdownsThisYear);


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

void generateStatistics(Machine* head, FILE* reportFile) {
    int totalTractors = 0, noBreakdownsTractors = 0;
    int totalExcavators = 0, noBreakdownsExcavators = 0;
    int totalRollers = 0, noBreakdownsRollers = 0;
    int totalCrane = 0, noBreakdownsCrane = 0;
    int totalMixers = 0, noBreakdownsMixers = 0;


    int totalMachines = 0; 
    Machine* temp = head; 

    while (temp != NULL) {
        totalMachines++; //if temp is not null increment machine count

        //check machine type and increment statistics
        if (strcmp(temp->machineType, "Tractor") == 0) {
            totalTractors++;
            if (temp->breakdownsThisYear == 0) {
                noBreakdownsTractors++;
            }
        }
        else if (strcmp(temp->machineType, "Excavator") == 0) {
            totalExcavators++;
            if (temp->breakdownsThisYear == 0) {
                noBreakdownsExcavators++;
            }
        }
        else if (strcmp(temp->machineType, "Roller") == 0) {
            totalRollers++;
            if (temp->breakdownsThisYear == 0) {
                noBreakdownsRollers++;
            }
        }
        else if (strcmp(temp->machineType, "Crane") == 0) {
            totalCrane++;
            if (temp->breakdownsThisYear == 0) {
                noBreakdownsCrane++;
            }
        }
        else if (strcmp(temp->machineType, "Mixer") == 0) {
            totalMixers++;
            if (temp->breakdownsThisYear == 0) {
                noBreakdownsMixers++;
            }
        }
        temp = temp->next; //move to the next machine in the list
    }

    //print statistics for each machine type
    //prints to console and file 
    printf("\n=== Machinery Statistics Based on Machine Type ===\n");

    //tractor statistcis 
    if (totalTractors > 0) {
        printf("\nTractors: %d\n", totalTractors);
        fprintf(reportFile, "\nTractors: %d\n", totalTractors);//prints to file
        printf("Tractors with no breakdowns: %d\n", noBreakdownsTractors);
        fprintf(reportFile, "Tractors with no breakdowns: %d\n", noBreakdownsTractors); 
        printf("Percentage of Tractors with no breakdowns: %.2f%%\n",
            (float)noBreakdownsTractors / totalTractors * 100);
        fprintf(reportFile, "Percentage of Tractors with no breakdowns: %.2f%%\n",
            (float)noBreakdownsTractors / totalTractors * 100); 
    }

    //excavator statistics
    if (totalExcavators > 0) {
        printf("\nExcavators: %d\n", totalExcavators);
        fprintf(reportFile, "\nExcavators: %d\n", totalExcavators);
        printf("Excavators with no breakdowns: %d\n", noBreakdownsExcavators);
        fprintf(reportFile, "Excavators with no breakdowns: %d\n", noBreakdownsExcavators);
        printf("Percentage of Excavators with no breakdowns: %.2f%%\n",
            (float)noBreakdownsExcavators / totalExcavators * 100);
        fprintf(reportFile, "Percentage of Excavators with no breakdowns: %.2f%%\n",
            (float)noBreakdownsExcavators / totalExcavators * 100);
    }

    //Roller statistics
    if (totalRollers > 0) {
        printf("\nRollers: %d\n", totalRollers);
        fprintf(reportFile, "\nRollers: %d\n", totalRollers);

        printf("Rollers with no breakdowns: %d\n", noBreakdownsRollers);
        fprintf(reportFile, "Rollers with no breakdowns: %d\n", noBreakdownsRollers);
        printf("Percentage of Rollers with no breakdowns: %.2f%%\n",
            (float)noBreakdownsRollers / totalRollers * 100);
        fprintf(reportFile, "Percentage of Rollers with no breakdowns: %.2f%%\n",
            (float)noBreakdownsRollers / totalRollers * 100);
    }

    //crane statistics
    if (totalCrane > 0) {
        printf("\nCrane: %d\n", totalCrane);
        fprintf(reportFile, "\nCrane: %d\n", totalCrane);

        printf("Crane machines with no breakdowns: %d\n", noBreakdownsCrane);
        fprintf(reportFile, "Crane machines with no breakdowns: %d\n", noBreakdownsCrane);
        printf("Percentage of Crane machines with no breakdowns: %.2f%%\n",
            (float)noBreakdownsCrane / totalCrane * 100);
        fprintf(reportFile, "Percentage of Crane machines with no breakdowns: %.2f%%\n",
            (float)noBreakdownsCrane / totalCrane * 100);
    }

    //mixer statistics
    if (totalMixers > 0) {
        printf("\nMixers: %d\n", totalMixers);
        fprintf(reportFile, "\nMixers: %d\n", totalMixers);
        printf("Mixers with no breakdowns: %d\n", noBreakdownsMixers);
        fprintf(reportFile, "Mixers with no breakdowns: %d\n", noBreakdownsMixers);
        printf("Percentage of Mixers with no breakdowns: %.2f%%\n",
            (float)noBreakdownsMixers / totalMixers * 100);
        fprintf(reportFile, "Percentage of Mixers with no breakdowns: %.2f%%\n",
            (float)noBreakdownsMixers / totalMixers * 100);
    }



    //print message if no machines found 
    if (totalMachines == 0) {
        printf("No machines found, unable to generate statistics");
        fprintf(reportFile, "No machines found, unable to generate statistics");

    }
}

void printReport(Machine* head) {
    //open file in write mode
    FILE* reportFile = fopen("Fleet.txt", "a");
    if (reportFile == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    // Write header to the file
    fprintf(reportFile, "=== Machinery Report ===\n\n");
        //print machine details to file
    displayAll(head, reportFile); 

    // Print performance statistics to the file
    fprintf(reportFile, "\n=== Performance Statistics Based on Machine Type ===\n");
    generateStatistics(head, reportFile);  // This will print statistics to the file

    // Close the file after writing all data
    fclose(reportFile);
    printf("Report generated and saved to 'Fleet.txt'.\n"); 
    
}

void listMachinesByValuation(Machine* head) {
    //count the number of machines
        int count = 0;
    Machine* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    //create an array to store pointers to all machines
        Machine** machineArray = (Machine**)malloc(count * sizeof(Machine*));
    if (machineArray == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    //fill the array with machine pointers
        temp = head;
    int i = 0;
    while (temp != NULL) {
        machineArray[i] = temp;
        i++;
        temp = temp->next;
    }

    //sort the array based on current valuation in descending order
        Machine* tempMachine;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (machineArray[i]->currentValuation < machineArray[j]->currentValuation) {
                //swap the pointers if the current valuation is smaller
                tempMachine = machineArray[i];
                machineArray[i] = machineArray[j];
                machineArray[j] = tempMachine;
            }
        }
    }
    //display the machines in the sorted order
        printf("\n===== MACHINERY LIST SORTED BY CURRENT VALUATION =====\n");
    for (int i = 0; i < count; i++) {
        printf("\nChassis Number: %s\n", machineArray[i]->chassisNumber);
        printf("Make: %s\n", machineArray[i]->make);
        printf("Model: %s\n", machineArray[i]->model);
        printf("Year: %d\n", machineArray[i]->yearOfManufacture);
        printf("Cost: %.2f\n", machineArray[i]->cost);
        printf("Current Valuation: %.2f\n", machineArray[i]->currentValuation);
        printf("Current Mileage: %d\n", machineArray[i]->currentMileage);
        printf("Next Service Mileage: %d\n", machineArray[i]->nextServiceMileage);
        printf("Owner: %s\n", machineArray[i]->ownerName);
        printf("Owner Email: %s\n", machineArray[i]->ownerEmail);
        printf("Owner Phone: %s\n", machineArray[i]->ownerPhoneNumber);
        printf("Machine Type: %s\n", machineArray[i]->machineType);
        printf("Breakdowns This Year: %d\n", machineArray[i]->breakdownsThisYear);
    }

    //free the allocated memory for the machine array
    free(machineArray);

}

void main()
{
	int choice = 0; 
    Machine* head = NULL; 

    //load machines from the file at the start of the program
    readMachinesFromFile(&head, "Fleet.txt");

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
            displayAll(head, stdout); //stdout writes info the the console
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
            generateStatistics(head, stdout); 
            break;

        case 7:
            printf("\nPrint report selected\n");
            printReport(head);
            break;

        case 8:
            printf("\nSort by valuation selected\n");
            listMachinesByValuation(head); 
            break;

        case 0:
            printf("\nExiting program. Goodbye!\n");
            printReport(head); 
            break;

        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    
    } while (choice != 0); //loops until 0 selected

    return 0;
    
}


