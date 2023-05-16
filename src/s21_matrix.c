#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (rows > 0 && columns > 0) {
    double **matrix = calloc(rows * columns + rows, sizeof(double));
    if (matrix) {
      matrix[0] = (double *)(matrix + rows);
      for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + columns * i;
      }
      result->columns = columns;
      result->matrix = matrix;
      result->rows = rows;
      res = OK;
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    free(A->matrix);
  }
  A->matrix = NULL;
  A->columns = 0;
  A->rows = 0;
}

int examination_matrix(matrix_t *A) {
  int exam = OK;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0)
    exam = INCORRECT_MATRIX;
  return exam;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (EXAM_A) {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (EXAM_A && EXAM_B) {
    if (A->rows == B->rows && A->columns == B->columns) {
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        res = INCORRECT_MATRIX;
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (EXAM_A && EXAM_B) {
    if (A->rows == B->rows && A->columns == B->columns) {
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        res = INCORRECT_MATRIX;
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (EXAM_A && EXAM_B) {
    if ((A->columns == B->rows)) {
      res = s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (EXAM_A && EXAM_B && A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          res = FAILURE;
          break;
        }
      }
      if (res == FAILURE) {
        break;
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (EXAM_A) {
    res = s21_create_matrix(A->columns, A->rows, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (EXAM_A) {
    res = s21_create_matrix(A->columns, A->rows, result);
    if (A->rows == A->columns) {
      if (res == OK) {
        s21_c_c(A, result);
      } else {
        res = INCORRECT_MATRIX;
      }
    } else {
      res = CALC_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}

void s21_c_c(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double det_m = 0;
      matrix_t nov_mat = {0};
      s21_create_matrix(A->rows - 1, A->columns - 1, &nov_mat);
      minor_matrix(i, j, A, &nov_mat, A->rows);
      s21_determinant(&nov_mat, &det_m);
      result->matrix[i][j] = pow(-1, (i + j)) * det_m;
      s21_remove_matrix(&nov_mat);
    }
  }
}

void minor_matrix(int rows, int columns, matrix_t *A, matrix_t *result, int n) {
  int n_columns = 0, n_rows = 0;
  result->rows = n - 1;
  result->columns = n - 1;
  for (int i = 0; i < n; i++) {
    if (i == rows) n_rows = 1;
    n_columns = 0;
    for (int j = 0; j < n; j++) {
      if (j == columns) n_columns = 1;
      if (i != rows && j != columns) {
        result->matrix[i - n_rows][j - n_columns] = A->matrix[i][j];
      }
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  *result = 0;
  if (EXAM_A) {
    if (A->rows == A->columns) {
      if (res == OK) {
        if (A->rows == 1) {
          *result = A->matrix[0][0];
        } else if (A->rows == 2) {
          *result = s21_do_det(A->matrix);
        } else {
          *result = s21_less_det(A);
        }
      }
    } else {
      res = CALC_ERROR;
    }
  }
  return res;
}

int s21_less_det(matrix_t *A) {
  int res = OK;
  double det_m = 0;
  matrix_t nov_mat = {0};
  int err = s21_create_matrix(A->rows, A->rows, &nov_mat);
  if (!err) {
    for (int j = 0; j < A->columns; j++) {
      minor_matrix(0, j, A, &nov_mat, A->rows);
      s21_determinant(&nov_mat, &det_m);
      res += A->matrix[0][j] * pow(-1, j + 2) * det_m;
    }
  }
  s21_remove_matrix(&nov_mat);
  return res;
}

double s21_do_det(double **matrix) {
  return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (EXAM_A) {
    if (A->rows == A->columns) {
      if (res == OK) {
        double det;
        res = s21_determinant(A, &det);
        if (res == OK) {
          s21_in_mat(A, det, result);
        } else {
          res = INCORRECT_MATRIX;
        }
      } else {
        res = INCORRECT_MATRIX;
      }
    } else {
      res = CALC_ERROR;
    }
  }
  return res;
}

int s21_in_mat(matrix_t *A, double det, matrix_t *result) {
  int res = OK;
  if (fabs(det) > 1e-6) {
    matrix_t n_mat = {0};
    if (res == OK) {
      s21_calc_complements(A, &n_mat);
      s21_transpose(&n_mat, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->rows; j++) {
          result->matrix[i][j] /= det;
        }
      }  // s21_mult_number(&n_mat, n_det, result);
      s21_remove_matrix(&n_mat);
    }
  } else {
    res = CALC_ERROR;
  }
  return res;
}