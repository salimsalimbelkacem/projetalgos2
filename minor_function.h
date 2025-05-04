#ifndef MINOR_FUNCTUON
#define MINOR_FUNCTUON
#include <stdbool.h>

long BIN(int N);
int sum_binary(int bin);

double riemann_sum(int);

int generate_key(long bin);
int decrypte_key(int sum, int key);
#endif
