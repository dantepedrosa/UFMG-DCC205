#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int i;
  int a[10];

  for (i=0; i < 10; i++){
    a[i] = malloc(sizeof(int) * 100);
  }
  for (i=0; i < 10; i++){
    free(a[i]);
  }
  return 0;
}

