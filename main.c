#include "modes.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool keep_going();

int main() {
    int choice;

    /* note from 2025 salim: puts is a function that prints pure
     * strings and not formated string like printf, it's a little
     * faster when you print a string that does not need to be 
     * formatted, and it also automatically prints the return 
     * character '\n' at the end
     * so printf may also be useful for printing strings that you
     * don't want to finish with \n but there is probably another
     * function that only prints pure strings without the trailing \n
     * la flem to check do it yourself
     * */

    puts("welcome to the second part of the project");
    do {
        puts("please select one of the following mode");
        printf("1. encrypt\n2. decrypt\n>>");

        if (scanf(" %d", &choice) == 0) 
            puts("type 1 for the 'encrypt mode'\n and 2 for the 'decrypt mode'");

        /* note from 2025 salim: this is a short if, or a ternary operator
         *
         * basicaly it's if:
         * (condition) ? what might be if true : what might be if false;
         *
         * it's a pre-compilation thing (i'm not sure) so it remplaces in the code before compiling
         *
         * examples:
         *  bool condition = true; puts( condition ? "true" : "false" );
         *  (here it prints true bc the variable named condition is set to true)
         *
         *  bool stupid(bool a){
         *      return a ? true : false;
         *  }
         * kinda stupid function returns what it is given but yeah just to show you how it interacts with return
         *
         * condition may be in between parenthesis or or may not be it doesnt matter (better for readability),
         * the condition can be a boolean statement example:
         * int a, b; puts((a > b)? "a": "b";);
         *
         * in here choice-1 is the condition, choice-1 is either 1-1 which is 0 (false), or 2-1 which is 1 (true)
         * so 2 would trigger the decrypt function call, and 2 would trigger the other
         *
         * TODO: the program doesnt check if the in inputed interger is 1 or 2, 3 would be an accepted answer here
         * and would probably call the decrypt function
         * */

        (choice-1)?  decrypt() : encrypt();
    }while(keep_going());

}


/*
     _ -        
   C(o|O)D
     \o/  <(!)
   */

/* note from 2025 salim: generally in cli programs
 * when a y/n choice is presented, the one in uppercase
 * is the default, which means it is the choice choosen when
 * the user writes nothing and presses enter
 *
 * also the tolower() function is a function from the ctype library,
 * in case he writes a upper case y or n, it would be still valid
 * idk if its faster, but it makes the code slightly more readable
 * bc you check once for each letter not twice (can see the 1st commit)
 * */
bool keep_going(){
    char choice='\0';
    
    while(  choice != 'y' &&
            choice != 'n' &&
            choice != '\n'
         ) {
        printf("do you want to continue?[y/N] ");
        choice = tolower(getchar());
    }

    return choice == 'y';
}
