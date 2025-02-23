#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_matrix.h"

void fill_matrix_random(matrix_t *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = (rand() % 21) - 10;
    }
  }
}

void print_matrix(matrix_t *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      printf("%6.2f ", matrix->matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  matrix_t A, B, result;
  double determinant;

  srand(time(NULL));

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  fill_matrix_random(&A);
  fill_matrix_random(&B);

  printf("Матрица A:\n");
  print_matrix(&A);

  printf("\nМатрица B:\n");
  print_matrix(&B);

  s21_sum_matrix(&A, &B, &result);
  printf("\nРезультат сложения A + B:\n");
  print_matrix(&result);
  s21_remove_matrix(&result);

  s21_mult_matrix(&A, &B, &result);
  printf("\nРезультат умножения A * B:\n");
  print_matrix(&result);
  s21_remove_matrix(&result);

  s21_transpose(&A, &result);
  printf("\nТранспонированная матрица A:\n");
  print_matrix(&result);
  s21_remove_matrix(&result);

  s21_determinant(&A, &determinant);
  printf("\nОпределитель матрицы A: %.2f\n", determinant);

  if (s21_inverse_matrix(&A, &result) == OK) {
    printf("\nОбратная матрица для A:\n");
    print_matrix(&result);
  } else {
    printf("\nОбратная матрица для A не существует (определитель равен 0).\n");
  }
  s21_remove_matrix(&result);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  return 0;
}