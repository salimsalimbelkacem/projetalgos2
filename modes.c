#include "minor_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void encrypt(){
  int size, auxilary;
  char* string = NULL;
  
  //input the string ------------------------------------------------------------
  printf("Enter the message: ");
  int i = -1;
  fflush(stdin);

  do { 
    i++; // en gros il lis la chaine letre par letre et a chauque fois il aloue
    string = (char*)realloc(string, sizeof(char) * (i + 2));
    string[i] = getchar();
    
    if (string[i] == '\n')
      string[i] = '\0';

  } while (string[i] != '\0');


  size = strlen(string);
  //-----------------------------------------------------------------------------

  clock_t begin = clock(); //tic

  // Convert into ASCII ---------------------------------------------------------
  int *x;
  x = (int *)malloc(size * sizeof(int));
  for (int j = 0; j < size; j++) {
    x[j] = string[j];

  }

  free(string);

  // Reverse the string from left to right to Right-to-Left ---------------------
  i = 0;
  int j = size - 1;
  while (i < j) {
    auxilary = x[i];
    x[i] = x[j];
    x[j] = auxilary;
    i++;
    j--;
  }

  // Convert each character of the string into binary + la somme ----------------
  
  //⚠️🚨wiiiwoooowiiiiwooo🚨⚠️ et non je ne suis pas un bout de code nule
  //ceci est une decente de police, bien joué jo!
  int private_key[size];
  
  for (int k = 0; k < size; k++) {
    private_key[k] = generate_key(BIN(x[k]));
    x[k] = sum_binary(BIN(x[k]));
  }
  // integral_Reiman ------------------------------------------------------------
  float integrale[size];

  for (int i = 0; i < size; i++) {
    integrale[i] = riemann_sum(i) * x[i];
  }
  
  free(x);

  // Matrice --------------------------------------------------------------------
  
  int half_size;
  if (size % 2 == 0)  half_size =   size/ 2;
  else                half_size = (size/ 2)+1;
  
  float Matrix[half_size][2], transposed[2][half_size];
  
  if (half_size * 2 > size) Matrix[half_size-1][2]=-1.00;

  int k = 0;
  for (i = 0; i < half_size; i++) {
    for (j = 0 ; j < 2; j++){
      if (i==half_size-1 && j == 1 && size % 2 != 0) break;
      Matrix[i][j] = integrale[k];
      k++;
    }
  }
  printf("your encrypted message:\n");
  for (i = 0; i < 2; i++) {
    for (j = 0; j < half_size; j++) {
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



void decrypt() {
  int half_size = 0, i, j, k, size;
  float *temporary_array = NULL;

  printf("Enter the encrypted matrix values (Enter a non-numeric value to finish):\n");
  
  i = -1;
  fflush(stdin);

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
