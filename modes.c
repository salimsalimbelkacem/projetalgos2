#include "minor_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_STRING_SIZE 100

void encrypt(){
    int size, auxilary;
    char string[INPUT_STRING_SIZE];

    //input the string ------------------------------------------------------------
    puts("Enter the message: ");

    /* note from 2025 salim: fgets is a function that reads pure strings from the
     * a given file, in here the given file is stdin (standard input) by inputing 
     * something in the cli it writes it to this file which is somewhere in the os
     * (/dev/stdin for unix idk about windows) then fgets reads until the n 1st characters
     * in that file, in our case the INPUT_STRING_SIZE 1st chars in that file and no more
     * */
    fgets(string, INPUT_STRING_SIZE, stdin);

    /* note from 2025 salim: the problem with fgets is that it read the data as it is in
     * stdin so when you press enter it reads the enter character \n so you have to remplace
     * it with \0
     *
     * strcspn returns the index of \n in string (not really than but technicaly is that)
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

    // note from 2025 salim: just swapping the macros are for readability
    for(int i=0; i<size/2; i++){
        GOOD_I = GOOD_I + EVIL_I;
        EVIL_I = GOOD_I - EVIL_I;
        GOOD_I = GOOD_I - EVIL_I;
    }

    // Convert each character of the string into binary + la somme ----------------

    //⚠️🚨wiiiwoooowiiiiwooo🚨⚠️ et non je ne suis pas un bout de code nule
    //ceci est une decente de police, bien joué jo!

    int private_key[size];

    for (int k = 0; k < size; k++) {
        private_key[k] = generate_key(BIN(string[k]));
        string[k] = sum_binary(BIN(string[k]));
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

    /* note from 2025 salim: la flem to continue to look up the rest of the code
     * it works that is what matters (sorry)
     * */

    int half_size;
    if (size % 2 == 0)  half_size =   size/ 2;
    else                half_size = (size/ 2)+1;

    float Matrix[half_size][2], transposed[2][half_size];

    if (half_size * 2 > size) Matrix[half_size-1][1]=-1.00;

    int k = 0;
    for (int i = 0; i < half_size; i++) {
        for (int j = 0 ; j < 2; j++){
            if (i==half_size-1 && j == 1 && size % 2 != 0) break;
            Matrix[i][j] = integrale[k];
            k++;
        }
    }
    printf("your encrypted message:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < half_size; j++) {
            if (j==half_size-1 && i == 1 && size % 2 != 0) break;
            transposed[i][j] = Matrix[j][i];
            printf("%f ", transposed[i][j]);
        }
    }

    // Generate a private key ----------------------------------------------------
    printf("\n\nyour private key: ");
    for (int k = 0; k<size; k++){ printf("%d ", private_key[k]);
    }
    // Print encrypted text ------------------------------------------------------

    printf("\n\n");
    clock_t end = clock(); // tac
    float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;
    printf("\nexecution time: %fs\n", time_spent);
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

    i = -1;

    do {
        i++;
        temporary_array= (float*) realloc(temporary_array, sizeof(float) * (i + 2));

    } while ( scanf("%f", &temporary_array[i]) == 1);
    fflush(stdin);

    size = i;

    if(size % 2 == 0)
        half_size = (int) size/2;
    else 
        half_size = (int) size/2 +1;

    printf("\n%d\n", size);


    // input private key ---------------------------------------
    int private_key[size] ;
    printf("Enter the private key:\n");
    for (int i = 0; i < size; i++) {
        private_key[i] = -1;
        do {
            if (scanf(" %d", &private_key[i]) == 0){
                fflush(stdin);
                printf("Error: Invalid input\n");
            }
        } while (private_key[i] == -1);
    }

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
