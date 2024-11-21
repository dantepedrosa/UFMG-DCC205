#include <stdio.h>
#include <stdlib.h>

int actual_calc(int a, int b){
  int c;
  if (b==0){
    printf("Erro: divisão por zero\n");
    return 0;
  }
  c=a/b;
  return c;
}

int calc(){
  int a;
  int b;
  scanf("%d %d", &a, &b);
  return actual_calc(a, b);;
}

int main(){
  return calc();;
}
