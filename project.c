#include <stdio.h>
#include <stdlib.h> //<---------- check allows using exit()
#include <stdbool.h> // line in C is used to include the standard C library header that defines the boolean data type along with its constants true and false.
#include <pthread.h> // allows using threads and commands pthread_create, pthread_t, pthread_join
#include <unistd.h> // allows using sleep() and exit()
#include <time.h>  // allows using srand(time(NULL))
int waterTemp = 25, saunaTemp = 25, airTemp = 25;  // creating initial values
bool isAirConditioner, isLightOn, isSaunaOn, isCoffeeMachineOn, isCameraOn, isGateOpen = false;
bool checkForDamage(int randomValue2){
    if(randomValue2 == 1){
    	return true;
	} else {
		return false;
	}                                          
}
bool checkForInondation(int randomValue1){
    if(randomValue1 == 1){
    	return true;
	} else {
		return false;
	}
}
bool checkForFire(int randomValue){
	if(randomValue == 1){
		return true;
	} else {
		return false;
	}
}
void generateRandFire() {                              //<---- function to randomly generate 1 or 0 and print in a file
    srand(time(NULL));
    int randomValue = rand() % 2;
    FILE *fireInfo = fopen("fire_check.txt", "w");
    if (fireInfo == NULL) {
        printf("Error");
        return;
    } else {
        fprintf(fireInfo, "%d", randomValue);
        fclose(fireInfo);
    }
}
void generateRandInondation() {                          //<---- function to randomly generate 1 or 0 and print in a file
    srand(time(NULL));
    int randomValue1 = rand() % 2;
    FILE *inondationInfo = fopen("inondation_check.txt", "w");
    if (inondationInfo == NULL) {
        printf("Error");
        return;
    } else {
        fprintf(inondationInfo, "%d", randomValue1);
        fclose(inondationInfo);
    }
}
void generateRandDamage() {                              //<---- function to randomly generate 1 or 0 and print in a file
    srand(time(NULL));
    int randomValue2 = rand() % 2;
    FILE *damageInfo = fopen("damage_check.txt", "w");
    if (damageInfo == NULL) {
        printf("Error");
        return;
    } else {
        fprintf(damageInfo, "%d", randomValue2);
        fclose(damageInfo);
    }
}
void adjustWaterTemperature(int desiredWaterTemp) {                        // creating functions that our code will do 
    waterTemp = desiredWaterTemp;
    printf("Water temperature adjusted to %d°C.\n", waterTemp);
}
void adjustAirTemperature(int desiredAirTemp) {
    airTemp = desiredAirTemp;
    printf("Air temperature adjusted to %d°C.\n", airTemp);
    if (airTemp > 28) {
        isAirConditioner = true;
        printf("Air conditioner is turned on.\n");
    } else {
        isAirConditioner = false;
        printf("Air conditioner is turned off.\n");
    }
}
void adjustSaunaTemperature(int desiredSaunaTemp) {
    saunaTemp = desiredSaunaTemp;
    printf("Sauna temperature adjusted to %d°C.\n", saunaTemp);
    if (saunaTemp > 40) {
        isSaunaOn = true;
        printf("Sauna is turned on.\n");
    } else {
        isSaunaOn = false;
        printf("Sauna is turned off.\n");
    }
}
void controlAirConditioner(bool on) {
    if (on) {
        printf("Air conditioner is turned on.\n");
    } else {
        printf("Air conditioner is turned off.\n");
    }
}
void controlCameras(bool on) {
   if (on) {
       printf("Cameras are turned on.\n");
    } else {
        printf("Cameras are not turned on.\n");
    }
}
void controlSauna(bool on) {
    if (on) {
        printf("Sauna is turned on.\n");
    } else {
        printf("Sauna is turned off.\n");
    }
}
void controlLights(bool on) {
    if (on) {
        printf("Lights are turned on.\n");
    } else {
        printf("Lights are turned off.\n");
    }
}
void controlCoffeeMachine(bool on){
  if(on){
    printf("Coffee machine in turned on \n");
  } else {
    printf("Coffee machine in not turned on \n");
  }
}
void controlGate(bool on){
  if(on){
    printf("Gates are open \n");
  } else {
    printf("Gates are not open \n");
  }
}
FILE *myFile;
void writeInFile(){                                              //<------- function to write in a file our initial information
	myFile = fopen("house_info.txt", "w");
	if(myFile == NULL){
		printf("ERROR");
	} else {
		fprintf(myFile, "INITIAL VALUES \n");
		fprintf(myFile, "water value: %d\n", waterTemp);
		fprintf(myFile, "sauna temp: %d\n", saunaTemp);
		fprintf(myFile, "air temp: %d\n", airTemp);
		fprintf(myFile, "Light is %d (1 is on, 0 is off)\n", isLightOn);
        fprintf(myFile, "Cameras are %d (1 is on, 0 is off)\n", isCameraOn);
        fprintf(myFile, "Coffee machine is %d (1 is on, 0 is off)\n", isCoffeeMachineOn);
        fprintf(myFile, "Gates are %d (1 is on, 0 is off)", isGateOpen);
		fclose(myFile);
  }
}
void saveChangedValuesToFile(int *ptr1, int *ptr2, bool *ptr3, int *ptr4, bool *ptr5, bool *ptr6, bool *ptr7) {   //<------- creating pointers for changed values
    FILE *newFile = fopen("house_updated.txt", "w");   //<------- creating new file
    if (newFile == NULL) {
        printf("Error opening file.\n");
    }
    fprintf(newFile, "CHANGE VALUES \n");
    fprintf(newFile, "Water Temperature is  = %d\n", *ptr1);
    fprintf(newFile, "Air Temperature is  = %d\n", *ptr2); 
    fprintf(newFile, "Gates are %d (1 is on, 0 is off)\n", *ptr3);
    fprintf(newFile, "Sauna Temperature is  = %d\n", *ptr4);
    fprintf(newFile, "Light is %d\n", *ptr5);
    fprintf(newFile, "Cameras are %d (1 is on, 0 is off)\n", *ptr6);
    fprintf(newFile, "Coffee machine is %d (1 is on, 0 is off)\n", *ptr7);
    fclose(newFile);
}

void* userControlThread(void* arg) {   // creating thread function
    char userInput[50];
    bool exitControl = false;
    int newTemp;
    while (!exitControl) {
        printf("Enter a command to change the parameters ('water', 'air', 'lights', 'coffee', 'sauna', 'cameras', 'gate' 'exit'): ");
        scanf("%s", userInput);
		if (strcmp(userInput, "water") == 0) {
            printf("Enter the new water temperature: ");
            scanf("%d", &newTemp);
            adjustWaterTemperature(newTemp);
        } else if (strcmp(userInput, "air") == 0) {
            printf("Enter the new air temperature: ");
            scanf("%d", &newTemp); 
            adjustAirTemperature(newTemp);
        }  else if (strcmp(userInput, "exit") == 0) {
        	saveChangedValuesToFile(&waterTemp, &airTemp, &isGateOpen, &saunaTemp, &isLightOn, &isCameraOn, &isCoffeeMachineOn);   // <--------- write infos after exiting user control
            printf("Exiting user control.\n");
            exit(0);
        } else if(strcmp(userInput, "lights") == 0){
            isLightOn = !isLightOn;
            controlLights(isLightOn);
        } else if(strcmp(userInput, "coffee") == 0){
          isCoffeeMachineOn = !isCoffeeMachineOn; 
          controlCoffeeMachine(isCoffeeMachineOn);
		} else if(strcmp(userInput, "gate") == 0){
			isGateOpen = !isGateOpen;
			controlGate(isGateOpen);
		} else if(strcmp(userInput, "sauna") == 0){
		printf("Enter the sauna temperature: ");
            scanf("%d", &newTemp);
            adjustSaunaTemperature(newTemp);
		}else if(strcmp(userInput, "cameras") == 0){
             isCameraOn = !isCameraOn;
             controlCameras(isCameraOn);
        } else {
		   printf("Unknown command. Please try again.\n");
        }
}
    return NULL;
}
void* fireMonitoringThread(void* arg) {
    int randomValue;  // Declare randomValue here

    while (1) {
        generateRandFire();  // Regenerate randomValue
        FILE *fireInfo = fopen("fire_check.txt", "r");
        if (fireInfo == NULL) {
            printf("Error reading fire check file.\n");
            exit(1);
        }

        fscanf(fireInfo, "%d", &randomValue);  // Read randomValue from the file
        fclose(fireInfo);

        if (checkForFire(randomValue)) {
            for(int j = 0; j < 3; j++){
            	printf("\nFire detected! Activate fire safety protocols.\n");
			}
        }
        sleep(60);
    }
    return NULL;
}
void* inondationMonitoringThread(void* arg) {
    int randomValue1;  // Declare randomValue1 here

    while (1) {
        generateRandInondation();  // Regenerate randomValue1
        FILE *inondationInfo = fopen("inondation_check.txt", "r");
        if (inondationInfo == NULL) {
            printf("Error reading fire check file.\n");
            exit(1);
        }

        fscanf(inondationInfo, "%d", &randomValue1);  // Read randomValue1 from the file
        fclose(inondationInfo);

        if (checkForFire(randomValue1)) {
            for(int k = 0; k < 3; k++){
            	printf("\nInondation detected! Activate inondation safety protocols.\n");
			}
        }
        sleep(60);
    }
    return NULL;
}
void* damageMonitoringThread(void* arg) {
    int randomValue2;  // Declare randomValue2 here

    while (1) {
        generateRandDamage();  // Regenerate randomValue2
        FILE *damageInfo = fopen("damage_check.txt", "r");
        if (damageInfo == NULL) {
            printf("Error reading fire check file.\n");
            exit(1);
        }

        fscanf(damageInfo, "%d", &randomValue2);  // Read randomValue2 from the file
        fclose(damageInfo);

        if (checkForDamage(randomValue2)) {
        	for(int i = 0; i < 3; i++){
        		printf("\nDamage detected! Activate damage safety protocols.\n");
			}
        }
        sleep(60);
    }
    return NULL;
}

int main(){
    printf("                              SMART HOUSE CONTROL PANEL \n ");
    writeInFile();                                                             //<-------------- calling the function
    pthread_t userControl, fireThread, inondationThread, damageThread;
    pthread_create(&userControl, NULL, userControlThread, NULL); 
    pthread_create(&fireThread, NULL, fireMonitoringThread, NULL);
    pthread_create(&damageThread, NULL, damageMonitoringThread, NULL);
    pthread_create(&inondationThread, NULL, inondationMonitoringThread, NULL);
    generateRandFire();
    generateRandInondation();
    generateRandDamage();
    pthread_join(userControl, NULL);
    pthread_join(fireThread, NULL);
    pthread_join(damageThread, NULL);
    pthread_join(inondationThread, NULL);

return 0;
}
//thread is not a function but thread allows us to run functions simulatenously.