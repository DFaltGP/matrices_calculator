#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*
  Função responsável por alocar dinamicamente um vetor MxN.
  Retorna um ponteiro para outro ponteiro de inteiros (int**).
*/ 
int** alloc_matrix(int rows, int cols) {
  int** ptr = malloc(rows * sizeof(int*));
  if (!ptr) {
    printf("Falha na alocação do ponteiro da matrix 2D\n");
    return NULL;
  }

  for (int i = 0; i < rows; i++) {
    ptr[i] = malloc(cols * sizeof(int));
    if (!ptr[i]) {
      printf("A alocação de ptr[%d] falhou.\n", i);
      for (int j = 0; j < i; j++) {
        free(ptr[j]);
      }
      free(ptr);
      return NULL;
    }
  }

  printf("Alocação concluída nas dimensões %dx%d\n", rows, cols);
  return ptr;
}

/*
  Função responsável por liberar a matrix declarada com 'alloc_matrix' 
  da memória.
*/
void free_matrix(int** ptr, int rows) {
  if (ptr == NULL) return;
  
  for (int i = 0; i < rows; i++) {
    free(ptr[i]);
  }
  free(ptr);

  printf("Memória desalocada com sucesso\n");
}


/*
  Função responsável por ler os valores da matriz
  informados pelo usuário.
*/
void read_matrix(int** matrix, int rows, int cols, char name) {
  printf("\nDigite os elementos da matriz %c (%dx%d):\n", name, rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("Elemento [%d][%d]: ", i, j);
      scanf("%d", &matrix[i][j]);
    }
  }
}


/*
  Função responsável por printar uma matriz seguindo o padrão abaixo:
    ⌈ 1 0 0 ⌉
    | 0 1 0 |
    ⌊ 0 0 1 ⌋
*/
void print_matrix(int** matrix, int rows, int cols, char name) {
  printf("\nMatriz %c:\n", name);
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      bool is_tl = i == 0 && j == 0;
      bool is_tr = i == 0 && j == cols - 1;
      bool is_bl = i == rows - 1 && j == 0;
      bool is_br = i == rows - 1 && j == cols - 1;
      bool is_middle_line = 0 < i && i < rows - 1;

      if (is_tl) {
        printf("\xE2\x8C\x88");
      } else if (is_bl) {
        printf("\xE2\x8C\x8B");
      }

      if (is_middle_line && j == 0) {
        printf("|");
      }

      printf(" %3d ", matrix[i][j]);

      if (is_middle_line && j == cols - 1) {
        printf("|\n");
      } else if (is_tr) {
        printf("\xE2\x8C\x89\n");
      } else if (is_br) {
        printf("\xE2\x8C\x8A\n");
      }

      /* 
      Códigos Unicode para os pipes:
      U+2308 TL \xE2\x8C\x88
      U+2309 TR \xE2\x8C\x89
      U+230A BL \xE2\x8C\x8A
      U+230B BR \xE2\x8C\x8B
      */
    }
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  do {
    int m, n, p, r;

    printf("=== MULTIPLICAÇÃO DE MATRIZES ===\n\n");
    printf("Para multiplicar A x B, o número de colunas de A deve ser igual ao número de linhas de B\n\n");
    
    printf("Digite as dimensões MxN da matriz A: ");
    scanf("%d %d", &m, &n);

    printf("Digite as dimensões PxR da matriz B: ");
    scanf("%d %d", &p, &r);

    // Verificação da compatibilidade das dimensões
    if (n != p) {
        printf("\nERRO: As dimensões das matrizes não permitem multiplicação!\n");
        printf("Matriz A: %dx%d, Matriz B: %dx%d\n", m, n, p, r);
        printf("Para multiplicar A x B, o número de colunas de A (%d) deve ser igual ao número de linhas de B (%d)\n", n, p);
        return 1;
    }

    // Alocação das matrizes
    int **A = alloc_matrix(m, n);
    int **B = alloc_matrix(p, r);
    int **C = alloc_matrix(m, r);  // Matriz resultado é MxR

    if (!A || !B || !C) {
      printf("Erro na alocação de memória!\n");
      return 1;
    }

    // Leitura das matrizes
    read_matrix(A, m, n, 'A');
    read_matrix(B, p, r, 'B');

    // Multiplicação das matrizes: C = A x B
    printf("\nCalculando o produto A x B...\n");
    
    for(int i = 0; i < m; i++) {        // Para cada linha de A
      for(int j = 0; j < r; j++) {      // Para cada coluna de B
        int sum = 0;
        for(int k = 0; k < n; k++) {
          sum += A[i][k] * B[k][j];
        }
        C[i][j] = sum;
      }
    }

    // Exibição dos resultados 
    print_matrix(A, m, n, 'A');
    print_matrix(B, p, r, 'B');
    printf("\nResultado da multiplicação A x B:\n");
    print_matrix(C, m, r, 'C');

    // Liberação da memória
    free_matrix(A, m);
    free_matrix(B, p);
    free_matrix(C, m);
    printf("\n");

    printf("=== Deseja calcular outra matriz? ===\n");
    printf("=== Digite 1 para outra matriz ===\n");
    printf("=== Digite 0 para sair ===\n");

    int cmd;
    scanf("%d", &cmd);

    if (cmd == 0) break;

  } while (1); // Executa repetidamente até o usuário digitar 0
  
  printf("\nPrograma finalizado com sucesso!\n");
  return 0;
}