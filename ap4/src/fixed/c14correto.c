#include <stdio.h>

int main(void) {
  int n, i, fact;

  printf("Positive integer:");
  scanf("%d", &n);
  
  fact = 1;

  for(i = 1; i<=n; i++) 
    fact = fact*i;

  printf("Factorial %d = %d\n", n, fact);
}
