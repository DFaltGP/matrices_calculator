#include <stdio.h>
#include <stdbool.h>

int main() {
  int A[4][5] = {
    {1,2,1,0,1},
    {0,1,1,1,1},
    {0,2,1,0,1},
    {2,1,0,2,1}
  };

  int B[5][5] = {
    {1,1,0,1,0},
    {0,2,1,2,1},
    {1,1,0,2,1},
    {0,1,1,1,1},
    {0,1,2,3,2}
  };

  int C[5][5];

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
  
  int c_len = sizeof(A) / sizeof(A[0]);
  int d_len = sizeof(B[0]) / sizeof(B[0][0]);
   
  for (int p = 0; p < c_len; p++) {
    for (int q = 0; q < d_len; q++) {
      bool is_tl = p == 0 && q == 0;
      bool is_tr = p == 0 && q == d_len - 1;
      bool is_bl = p == c_len - 1 && q == 0;
      bool is_br = p == c_len - 1 && q == d_len - 1;
      bool is_middle_line = 0 < p && p < c_len - 1;

      if (is_tl) {
        printf("\xE2\x8C\x88");
      } else if (is_bl) {
        printf("\xE2\x8C\x8A");
      }

      if (is_middle_line && q == 0) {
        printf("|"); // lpipe
      }

      printf(" %d ", C[p][q]);

      if (is_middle_line && q == d_len - 1) {
        printf("|\n"); // rpipe
      }

      if (is_tr) {
        printf("\xE2\x8C\x89\n");
      } else if (is_br) {
        printf("\xE2\x8C\x8B");
      }
    }
  }

  /* 
    Unicode for closing pipes:
    U+2308 TL \xE2\x8C\x88
    U+2309 TR \xE2\x8C\x89
    U+230A BL \xE2\x8C\x8A
    U+230B BR \xE2\x8C\x8B
  */

  return 0;
}
