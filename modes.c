#include "minor_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_STRING_SIZE 100

void encrypt(){
    int size, auxilary;
    char string[INPUT_STRING_SIZE];

    printf("%d\n", getchar());

    //input the string ------------------------------------------------------------
    puts("Enter the message: ");

    /* note from 2025 salim: fgets is a function that reads pure strings from the
     * a given file, in here the given file is stdin (standard input) by inputing 
     * something in the cli it writes it to this file which is somewhere in the os
     * (/dev/stdin for unix idk about windows) then fgets reads until the n 1st characters
     * in that file, in our case the INPUT_STRING_SIZE 1st chars in that file and no more
     * */
    fgets( string, INPUT_STRING_SIZE, stdin );
    

    /* note from 2025 salim: the problem with fgets is that it read the data as it is in
     * stdin so when you press enter it reads the enter character \n so you have to remplace
     * it with \0
     *
     * strcspn returns the index of \n in string (not really that but technicaly is that)
     * */
    string[strcspn(string, "\n")] = '\0';
    size = strlen(string);

    //-----------------------------------------------------------------------------

    clock_t begin = clock(); //tic

    // Convert into ASCII ---------------------------------------------------------

    /* note from 2025 salim: don't need to convert the characters into an ascii
     * interger values because it is already an integer value, the `char` variable 
     * type is the same as `int`!!!
     * the only difference is that char has a size of one byte and int has a size of 4
     * you can check the 1st commit to see what we did but yeah whatever
     * */

    // Reverse the string from left to right to Right-to-Left ---------------------

#define GOOD_I string[i]
#define EVIL_I string[size-(i+1)]

    // note from 2025 salim: just swapping, the macros are for readability
    for(int i=0; i<size/2; i++){
        GOOD_I = GOOD_I + EVIL_I;
        EVIL_I = GOOD_I - EVIL_I;
        GOOD_I = GOOD_I - EVIL_I;
    }

    // Convert each character of the string into binary + la somme ----------------

    //⚠️🚨wiiiwoooowiiiiwooo🚨⚠️ et non je ne suis pas un bout de code nule
    //ceci est une decente de police, bien joué jo!

    int private_key[size];

    for (int i = 0; i < size; i++) {
        private_key[i] = generate_key(BIN(string[i]));
        string[i] = sum_binary(BIN(string[i]));
    }
    // integral_Reiman ------------------------------------------------------------
    float integrale[size];

    /* note from 2025 salim: you can look in the `minor_functions.c` file for how
     * we computed it but tbh it's a stupid constant we've been asked to compute 
     * a constant just don't do that it's stupid, anywayyyy
     * */
#define RIEMANN_SUM 2.295573
    for (int i = 0; i < size; i++) {
        integrale[i] = RIEMANN_SUM * string[i];
    }

    // Matrice --------------------------------------------------------------------

    /* note from 2025 salim: converted it into a matrix!!!
     * basicaly a matrix is a array or addresses,
     * an array of the 1st address of other arrays
     *
     * so  `float matrix[2][]` is the same as `float* matrix[2]`
     * and `float integrale[]` is the same as `float* integrale`
     *
     * therefore we can store integral in the 1st element of the matrix (array of addresses)
     * and the address of the HALF_SIZEth element in the second element of matrix
     *
     * it's just fancy bullshit to mean the same thing basicaly, we're just playing with addresses
     * */

#define HALF_SIZE  size / 2 + size % 2

    float* matrix[2], transposed[HALF_SIZE];

    /*kinda useless*/

    /*matrix[0] = integrale;*/
    /*matrix[1] = integrale + HALF_SIZE;*/

    /*
     * can be writen like the transposed one, we just know that the matrix has only two elements so 
     * it's kinda the same as writing it twice since a for loop would take 2 lines
     *
     * where as in the transposed one, we can't know the size since it is a variable
     * */

    /* then we transpose the matrix (the matrix part was kinda useless so i commented it)
     * even the transpose part is useless because it just the pair index on one side and the 
     * odd ones on the other side 
     * it means at the end you'll need to print the elements with a pair index first then 
     * the element with an odd index, but whatever man
     * */
    for(int i = 0; i<size; i+=2)
        transposed[i/2] = integrale[i];
    

    puts("your encrypted message:");

    for(int i = 0; i<HALF_SIZE; i++)
        printf("%f ", transposed[0]);
    
    for(int i = 0; i<HALF_SIZE; i++)
        printf("%f ", transposed[1]);

    /*alternatively

    for(int i = 0; i<size; i+=2)
        printf("%f ", integrale[i]);
    
    for(int i = 1; i<size; i+=2)
        printf("%f ", integrale[i]);

        or 

#define PRINT_MESSAGE(START_INDEX)\
    for(int i =START_INDEX; i<size; i+=2)\
        printf("%f ", integrale[i]);

        PRINT_MESSAGE(0)
        PRINT_MESSAGE(1)
     * */

    // Generate a private key ----------------------------------------------------
    puts("\nyour private key: ");
    for (int k = 0; k<size; k++){ printf("%d ", private_key[k]);
    }
    // Print encrypted text ------------------------------------------------------

    puts("");
    clock_t end = clock(); // tac
    float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;
    printf("execution time: %fs\n", time_spent);
    //----------------------------------------------------------------------------
}

//******************************************************************************
//******************************************************************************


/* note from 2025: this is some mad crazy broken code
 * i'm kinda tired now so i'll take a look at it another time
 * but yeah the decrypt part is fucked up
 * */

void decrypt() {
    int half_size = 0, i, j, k, size;
    float *temporary_array = NULL;

    printf("Enter the encrypted matrix values (Enter a non-numeric value to finish):\n");

    /*TODO: write code to input the list of numbers, the numbers are 
     * */

    clock_t begin = clock();


    //matrix ---------------------------------------------------

    //                3amring the matrix
    float Matrix[half_size][2];
    k = 0;
    for (i = 0; i<2; i++){
        for (j = 0; j<half_size; j++){
            Matrix[j][i] = temporary_array[k];
            k++;
        }
    }

    //              transposing the matrix
    float transposed[2][half_size];
    for (j = 0; j<half_size; j++){
        for (i = 0; i<2; i++){
            transposed[i][j] = Matrix[j][i];
        }
    }
    //integral -------------------------------------------------
    //              3amring the intergral array 
    float integral[size];
    k=0;
    for (j = 0; j<half_size; j++){
        for (i = 0; i<2; i++){
            integral[k] = transposed [i][j];
            k++;
        }
    }

    /*
sum:   integral:
1      2.295572
2      4.591144
3      6.886716
4      9.182288
5     11.477860
6     13.773432
*/
    int x[size];
    float integ[] = {2.295572, 4.591144, 6.886716, 9.182288, 11.477860, 13.773432};

    for (i = 0; i < size; i++) {
        for (j = 0; j<6; j++){
            if(integral[i] == integ[j]){
                x[i] = j+1;
                break;
            }
        }
    }

    // sum -----------------------------------------------------

    char string[size];
    for (i = 0; i < size; i++) {
        string[i] = decrypte_key( x[i], private_key[i] );
    }
    // reverse string -------------------------------------------

    char auxiliary;
    i = 0;
    j = size - 1;
    while (i < j) {
        auxiliary = string[i];
        string[i] = string[j];
        string[j] = auxiliary;
        i++;
        j--;
    }

    string[size]='\0';

    clock_t end = clock();

    float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;

    printf("Decrypted message: %s\n", string);
    printf("Execution time: %f ms\n", time_spent/1000);
}


/*
   _________________________________________________________
   | * *      *    *     *    *               *     *    *   |
   |*   *   *   *            *   *        *        *   *   * |
   |  *  *               *      *     *     *  *     *     * |
   | *     *       *  *           *     * *     *    *       |
   |  *               *   *       *   *       *   *   *   *  |
   |           *        *      *   *                    *    |
   | *   *   *       *   *       *     *           *   *     |
   |            *     *   tu me connais  *       *           |
   |*        *                     *       * *            *  |
   |*  *  *                *                  *            * |
   | *     *         *     *    *          *        *        |
   |____________________________.____________________________|
   |.......................... /|\ ..........................|
   |_.__.__.__.__.__.__.__.__/__|__\__.__.__.__.__.__.__.__._|
   |   .    .    .    .    /    |    \    .    .    .    .   |
   |.      .      .      /      |      \      .      .      .|
   |_.________.________/________|________\________.________._|
   |      .          /          |          \          .      |
   |  .            /            |            \            .  |
   |             /              |              \             |
   |           /                |                \           |
   |         /                  |                  \         |
   |_______/____________________|____________________\_______|
   */
