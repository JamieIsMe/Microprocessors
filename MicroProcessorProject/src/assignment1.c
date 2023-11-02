/*
Program Description: Gives the user 4 options in a main menu, option one allows the user to verify if their PIN is correct, option 2
allows the user to change their current PIN to a new one by making them enter their new desired PIN twice, if they match the PIN will
be changed, if they dont the PIN will remain the same. Option 3 shows the user how many times they entered their PIN correctly and 
incorrectly while using option 1. Option 4 allows the user to exit the program.

Author: Jamie Turpin C22375486

Date: 1/11/2022
*/
#define SIZE 4

#include <stdio.h>
int main(){
    int i, right, option = 0, correct = 0, incorrect = 0, status = 1, num[SIZE], pin[SIZE] = {1, 2, 3, 4};
    


    //Allows to whole program to run and terminate when option 4 is selected
    do {
        printf("\nPlease select an option from below by entering the correct number\n");
        printf("1. Enter PIN and verify correct\n");
        printf("2. Change PIN\n");
        printf("3. Display number of correct and incorrect pin entries\n");
        printf("4. Exit the program\n");
        
        scanf("%d", &option);

        //if the option entered is a character, the menu will reset and be redisplayed
        if (option == getchar()){
            option = 0;
        }

        //Allows user to verify PIN if 1 is entered
        if (option == 1){
            printf("Please enter your PIN digit by digit\n");

            //Lets the user input 4 digits
            for (i=0; i<SIZE; i++){
                scanf("%d", &num[i]);
                if (num[i] > 9 || num[i] < 0 || num[i] == getchar()){
                    printf("Invalid Input. Please only enter a number 0-9\n");
                    option = 0;
                    break;
                } else if (num[i] == pin[i]){
                    right++;
                }
            }

            //Checks if the numbers entered are equal to the PIN
            if (num[0] == pin[0] && num[1] == pin[1] && num[2] == pin[2] && num[3] == pin[3]){
                printf("The PIN you entered is correct\n\n");
                correct++;
            }   else{
                printf("The PIN you entered is incorrect\n\n");
                incorrect++;
            }
            option = 0;
        }//End if

        //Allows user to change PIN if 2 is entered
        else if (option == 2){
            int check[SIZE];
            printf("Please enter your new PIN digit by digit\n");
            
            //Lets the user enter 4 new digits
            for (i=0; i<SIZE; i++){
                scanf("%d", &num[i]);
            }

            printf("Please re-enter your new PIN digit by digit\n");

            //Lets the user enter 4 digits again to check if its equal to the first 4
            for (i=0; i<SIZE; i++){
                scanf("%d", &check[i]);
            }
            
            if (num[0] == check[0] && num[1] == check[1] && num[2] == check[2] && num[3] == check[3]){
                for (i=0; i<SIZE; i++){
                    pin[i] = num[i];
                }
                printf("Your PIN has been changed\n\n");
            }
            else{
                printf("PINs do not match\n\n");
            }
            option = 0;
        } 

        //Tells reader how many correct and incorrect PIN inputs there have been
        else if (option == 3){
            printf("Your PIN has been entered %d times correctly and %d times incorrectly\n\n", correct, incorrect);
            option = 0;
        }

        //Ends the program when user enters 4
        else if (option == 4){
            break;
        } 

        //if the option entered isnt 1-4 this error is displayed
        else{
            printf("Invalid Input\n\n");
            option = 0;
        }

    } while (option != 4); //End do while

    return 0;
}//end main