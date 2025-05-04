#include "modes.h"
#include <stdio.h>
#include <stdbool.h>

bool keep_going ();

int main() {
    int choice;
    printf("welcome to the second part of the project\n");
    do {
        printf("please select one of the following mode\n");
        printf("1. encrypt\n2. decrypt\n>>");

        if (scanf(" %d", &choice) == 0) {
            printf("type 1 for the 'encrypt mode'\n and 2 for the 'decrypt mode'\n");
        }

        (choice-1)?  decrypt() : encrypt();

    }while(keep_going());

}


/*
   _ -        
   C(o|O)D
   \o/  <(!)
   */

bool keep_going (){
    fflush(stdin);
    char choice;
    do{
        printf("do you want to continue? ");

        choice = getchar();
    } while( choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    if ( choice == 'y' || choice == 'Y' ) return true;
    return false;
}
