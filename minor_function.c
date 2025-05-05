#include <math.h>
#include <stdbool.h>

// tout ce qui est binaire

long BIN(int N) {
  int x = N;
  int bits = 0;
  long bin = 0;

  for (int i = 1; pow(2, i) <= N; i++)
      bits = i;
  for (int i = bits; i >= 0; i--)
      bin = bin * 10 + ((x >> i) & 1);
  
  return bin;
}



#define pi 3.142857 
//XD define ça veux dire un definie une constante
// note from 2025 salim: no it defines a macro, not the same

int sum_binary(int bin) {
  int sum = 0, bit;

  while (bin != 0) {
    bit = bin % 10;
    sum = sum + bit;
    bin = bin / 10;
  }
  return sum;
}
// integrale ---------------------------------------------

// float f(float x){ 
//   return (sqrt(1 + (x * x)));
// }
//
// float riemann_sum() {
//   // façon arrogante de multiplier par 2,chepaquoi azy
//   float sum = 0.0;
//   float a = -1.0, b = 1.0;
//   float dx= (b - a) / 10000;
//   float x = a;
//
//   for (int i = 0; i < 10000; i++) {
//     sum += f(x) * dx;
//     x += dx;
//   }
//   return sum;
// }
//-------------------------------------------------------

/*
 * TODO: the generate and decrypt function
 * look alike a lot, that is redundant code
 * take care of it ig
 * (merge them into one function or create a macro)
 * */

int generate_key(long bin){
  int j =1, dec;
  for(char c=' '; c<='~'; c++){
    dec = c;
    if(sum_binary(BIN(dec)) == sum_binary(bin) ){
      if(BIN(dec) == bin) return j;
      j++;
    }
  }
  return 0;
}

/*
4 - Aphex Twin
   _________
   |  _ _  |
  C|  x|x  |D 
   |   o   | 
   |_______|
*/

char decrypte_key(int sum, int key){
  int j =1, dec;
  for(char c=' '; c<='~'; c++){
    dec = c;
    if(sum_binary(BIN(dec)) == sum ){
      if( j == key) return dec;
      j++;
    }
  }
  return 0;
}
