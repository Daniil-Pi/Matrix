#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (result == NULL) {
    err = 1;
  } else {
    if (rows <= 0 || columns <= 0) {
      err = 1;
    } else {
      result->rows = rows;
      result->columns = columns;
      result->matrix = (double **)calloc(rows, sizeof(double *));
      if (result->matrix == NULL) {
        return 1;
      } else {
        for (int k = 0; k < result->rows; k++) {
          result->matrix[k] = (double *)calloc(columns, sizeof(double));
          if (result->matrix[k] == NULL) {
            return 1;
          }
        }
      }
    }
  }
  return err;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL || A->rows != 0 || A->columns != 0) {
      for (int k = 0; k < A->rows; k++) {
        if (A->matrix[k] != NULL) free(A->matrix[k]);
      }
      free(A->matrix);
      A->matrix = NULL;
    }
    if (A->columns) {
      A->columns = 0;
    }
    if (A->rows) {
      A->rows = 0;
    }
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = 1;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    err = 0;
  } else {
    {
      if (A->rows != B->rows || A->columns != B->columns || A->columns <= 0 ||
          A->rows <= 0 || B->columns <= 0 ||
          B->rows <= 0) {  // проверка на размер матрицы  0
        err = 0;
      } else

        for (int k = 0; k < A->rows && err == 1; k++) {
          for (int m = 0; m < A->columns; m++) {
            if (fabs(A->matrix[k][m] - B->matrix[k][m]) > 1e-6) {
              err = 0;
              break;
            }
          }
        }
    }
  }
  return err;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (result == NULL || A == NULL || B == NULL) {
    err = 1;
  } else {
    if (A->matrix == NULL || B->matrix == NULL) {
      err = 1;
    } else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
               B->columns <= 0 || A->rows != B->rows ||
               A->columns != B->columns) {
      err = 2;
    } else {
      int create_error = 0;
      create_error = s21_create_matrix(A->rows, A->columns, result);
      if (create_error == 0) {
        for (int k = 0; k < A->rows; k++) {
          for (int m = 0; m < A->columns; m++) {
            result->matrix[k][m] = A->matrix[k][m] + B->matrix[k][m];
          }
        }
      }
    }
  }
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (result == NULL || A == NULL || B == NULL) {
    err = 1;
  } else {
    if (A->matrix == NULL || B->matrix == NULL) {
      err = 1;
    } else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
               B->columns <= 0 || A->rows != B->rows ||
               A->columns != B->columns) {
      err = 2;
    } else {
      int create_error = 0;

      create_error = s21_create_matrix(A->rows, A->columns, result);
      if (create_error == 0) {
        for (int k = 0; k < A->rows; k++) {
          for (int m = 0; m < A->columns; m++) {
            result->matrix[k][m] = A->matrix[k][m] - B->matrix[k][m];
          }
        }
      }
    }
  }
  return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = 0;
  if (result == NULL || A == NULL) {
    err = 1;
  } else {
    if (A->matrix == NULL) {
      err = 1;
    } else if (A->rows <= 0 || A->columns <= 0) {
      err = 2;
    } else {
      int create_error = 0;

      create_error = s21_create_matrix(A->rows, A->columns, result);
      if (create_error == 0) {
        for (int k = 0; k < A->rows; k++) {
          for (int m = 0; m < A->columns; m++) {
            result->matrix[k][m] = A->matrix[k][m] * number;
          }
        }
      }
    }
  }
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (result == NULL || A == NULL || B == NULL) {
    err = 1;
  } else {
    if (A->matrix == NULL || B->matrix == NULL) {
      err = 1;
    } else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
               B->columns <= 0 || A->rows != B->columns) {
      err = 2;
    } else {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (result == NULL || A == NULL) {
    err = 1;
  } else {
    if (A->matrix == NULL) {
      err = 1;
    } else if (A->rows <= 0 || A->columns <= 0) {
      err = 2;
    } else {
      s21_create_matrix(A->columns, A->rows, result);
      for (int k = 0; k < A->rows; k++) {
        for (int m = 0; m < A->columns; m++) {
          result->matrix[m][k] = A->matrix[k][m];
        }
      }
    }
  }
  return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = 0;
  int sign = 0;
  if (result == NULL || A == NULL) {
    err = 1;
  } else {
    if (A->matrix == NULL) {
      err = 1;
    } else if (A->rows <= 0 || A->columns <= 0 || A->rows != A->columns) {
      err = 2;
    } else {
      s21_create_matrix(A->columns, A->rows, result);
      if (A->rows == 1 && A->columns == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else {
        matrix_t buf = {0};
        for (int k = 0; k < A->rows; k++) {
          for (int m = 0; m < A->columns; m++) {
            s21_create_minor(k, m, A, &buf);
            sign = ((k + m) % 2 == 0) ? 1 : -1;
            result->matrix[k][m] = s21_determ(&buf) * sign;
            s21_remove_matrix(&buf);
          }
        }
      }
    }
  }

  return err;
}

void s21_create_minor(int rows, int col, matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->columns - 1, A->rows - 1, result);
  for (int i = 0, i2 = 0; i < A->rows; i++) {
    if (i != rows) {
      for (int j = 0, j2 = 0; j < A->columns; j++) {
        if (j != col) {
          result->matrix[i2][j2] = A->matrix[i][j];
          j2++;
        }
      }
      i2++;
    }
  }
}

double s21_determ(matrix_t *A) {
  double result = 0.;
  if (A == NULL || A->matrix == NULL) {
    result = 0;
  } else {
    if (A->rows == 1) {
      result = A->matrix[0][0];
    }

    else if (A->rows == 2) {
      result = (A->matrix[0][0] * A->matrix[1][1]) -
               (A->matrix[1][0] * A->matrix[0][1]);

    } else {
      int sign = 1;
      for (int i = 0; i < A->rows; i++) {
        matrix_t buf;
        s21_create_minor(0, i, A, &buf);
        result += sign * A->matrix[0][i] * s21_determ(&buf);
        sign *= -1;
        s21_remove_matrix(&buf);
      }
    }
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int err = 0;
  if (A == NULL || result == NULL) {
    err = 1;
  } else {
    if (A->rows <= 0 || A->columns <= 0) {
      err = 2;
    } else {
      *result = s21_determ(A);
    }
  }
  return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = 0;
  if (A == NULL || result == NULL) {
    return 1;
  } else {
    if (A->matrix == NULL) {
      return 1;
    } else if (A->rows <= 0 || A->columns <= 0) {
      err = 2;
    } else {
      double determ = s21_determ(A);
      if (fabs(determ) < 1e-7) {
        err = 2;
      } else {
        matrix_t transp, compl ;
        s21_calc_complements(A, &compl );
        s21_transpose(&compl, &transp);
        s21_mult_number(&transp, 1 / determ, result);
      }
    }
  }
  return err;
}