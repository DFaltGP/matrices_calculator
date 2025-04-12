#include <stdio.h>

int main() {
  int A[2][2] = {
    {1,2},
    {3,5}
  };

  int B[2][2] = {
    {1,3},
    {3,9}
  };

  int C[2][2];

  int a_len = sizeof(A[0]) / sizeof(A[0][0]);
  int b_len = sizeof(B) / sizeof(B[0]);

  printf("The A length is %d\nThe B length is %d\n", a_len, b_len);

  if (a_len != b_len) {
      printf("The matrices n size doesn't matches.");
      return 0;
  }

  for(int k = 0; k < a_len; k++) {
    int i = 0;
    
    while (i < a_len) {
      int j = 0;
      int sum = 0;

      while (j < a_len) {
        sum = sum + (A[k][j] * B[j][i]);
        j++;
      }
      
      C[k][i] = sum;
      i++;
    }
  }  

  printf("[ %d %d ]\n[ %d %d ]", C[0][0], C[0][1], C[1][0], C[1][1]);

  return 0;
}