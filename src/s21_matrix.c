#include "s21_matrix.h"

// int s21_create_matrix(int rows, int columns, matrix_t *result) {
//   int error = 0;
//   if (rows > 0 && columns > 0) {  // проверка поданных данных
//     result->rows = rows;
//     result->columns = columns;
//     result->matrix = (double **)calloc(rows, sizeof(double *));
//     error = 0;
//   } else {
//     error = 1;
//   }
//   if (result->matrix != NULL) {  // проверка поданных данных
//     for (int i = 0; i != rows; i++) {
//       result->matrix[i] = (double *)calloc(columns, sizeof(double));
//       if (!result->matrix) {
//         for (int j = 0; j != columns; i++) {
//           free(result->matrix[j]);  // очистка памяти каждого элемента
//         }
//         free(result->matrix);  // очистка матрици
//       }
//     }
//     error = 0;
//   }
//   return error;
// }

int s21_create_matrix(int rows, int columns,
                      matrix_t *result) {  // создание матриц
  int error =
      INCORRECT_MATRIX;  // изначально даем значение ошибки ввода данных
                         // для декомпозиции кода и корректности ввода
                         // данных дабы не делать дополнительных проверок
  if (rows > 0 && columns > 0) {  // проверка поданных данных
    double **matrix =
        calloc(rows * columns * sizeof(double) + rows * sizeof(double *), 1);
    if (matrix) {  // защита малока (динамической памяти)
      double *ptr = (double *)(matrix + rows);
      for (int i = 0; i < rows; i++) {
        matrix[i] = ptr + columns * i;
      }
      result->columns = columns;
      result->matrix = matrix;
      result->rows = rows;
      error = OK;
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {  // очистка матрици
  if (A->matrix) {
    free(A->matrix);  // очистка динамической памяти
  }
  A->matrix = NULL;  // зануление
  A->columns = 0;    // отдельных
  A->rows = 0;       // сегментов
}

// int s21_create_matrix(int rows, int columns, matrix_t *result) {
//   errors outcome = OK;
//   if (rows > 0 && columns > 0 && result != NULL) {
//     result->rows = rows;
//     result->columns = columns;
//     result->matrix = (double **)malloc(sizeof(double *) * rows);
//     for (int i = 0; i < rows; i++) {
//       (result->matrix)[i] = (double *)malloc(sizeof(double) * columns);
//     }
//   } else {
//     outcome = INCORRECT;
//   }
//   return outcome;
// }

int examination_matrix(matrix_t *A) {  // проверка матрици
  int exam = OK;
  if (A->matrix == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0)
    exam = INCORRECT_MATRIX;  // соответсвенно всех ее компанентов
  return exam;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (examination_matrix(A) == OK) {  // проверка матрици
    res = s21_create_matrix(A->rows, A->columns, result);  // создание матрици
    if (res == OK) {  // проверяем выход при создании матрици
      for (int i = 0; i < A->rows; i++) {       // проходимся по
        for (int j = 0; j < A->columns; j++) {  // всей матрице
          result->matrix[i][j] =
              A->matrix[i][j] * number;  // умножение на число
        }
      }
    } else {
      res = INCORRECT_MATRIX;  // если результат при создании  матрици
    }                          // некорректный
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (examination_matrix(A) == OK &&
      examination_matrix(B) == OK) {  // проверка матрици
    if (A->rows == B->rows &&
        A->columns == B->columns) {  // проверяем параметры матриц
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {       // проходимся по
          for (int j = 0; j < A->columns; j++) {  // всей матрице
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
  if (examination_matrix(A) == OK &&
      examination_matrix(B) == OK) {  // проверка матрици
    if (A->rows == B->rows &&
        A->columns == B->columns) {  // проверяем параметры матриц
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {       // проходимся по
          for (int j = 0; j < A->columns; j++) {  // всей матрице
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
  int res = OK;
  if (examination_matrix(A) == OK &&
      examination_matrix(B) == OK) {  // проверка матрици
    if (A->columns == B->rows) {  // проверяем параметры матриц
      res = s21_create_matrix(A->rows, A->columns, result);
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {       // проходимся по
          for (int j = 0; j < A->columns; j++) {  // всей матрице
            result->matrix[i][j] = A->matrix[i][j] * B->matrix[i][j];
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

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (examination_matrix(A) == OK &&
      examination_matrix(B) == OK) {  // проверка матриц
    if (A->rows == B->rows &&
        A->columns == B->columns) {  // проверяем параметры матриц
      for (int i = 0; i < A->rows; i++) {       // проходимся по
        for (int j = 0; j < A->columns; j++) {  // всей матрице
          if (round(A->matrix[i][j] * pow(10, 7)) !=
              round(B->matrix[i][j] * pow(10, 7))) {
            res = FAILURE;
          }
        }
      }
    } else {
      res = FAILURE;
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (examination_matrix(A) == OK) {  // проверка матрици
    res = s21_create_matrix(A->columns, A->rows, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {       // проходимся по
        for (int j = 0; j < A->columns; j++) {  // всей матрице
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (examination_matrix(A) == OK) {  // проверка матрици
    res = s21_create_matrix(A->columns, A->rows, result);
    if (A->rows == A->columns) {
      if (res == OK) {
        for (int i = 0; i < A->rows; i++) {       // проходимся по
          for (int j = 0; j < A->columns; j++) {  // всей матрице
            double det_m = 0;
            matrix_t nov_mat = {0};
            s21_create_matrix(A->rows - 1, A->columns - 1, &nov_mat);
            minor_matrix(i, j, A, &nov_mat, A->rows);
            s21_determinant(&nov_mat, &det_m);
            result->matrix[i][j] =  // поиск алгебрагического
                pow(-1, (i + j)) * det_m;  //  доп. элемента матрицы
            s21_remove_matrix(&nov_mat);  // чистка
          }
        }
      } else {
        res = INCORRECT_MATRIX;
      }
    } else {
      res = CALC_ERROR;
    }
  }
  // s21_remove_matrix(&A);
  return res;
}

void minor_matrix(int rows, int columns, matrix_t *A, matrix_t *result, int n) {
  // double res = 0;
  int n_rows = 0, n_colums = 0;
  result->rows = n - 1;  // убираем у каждого параметра
  result->columns = n - 1;  // по одному ряду/столбцу
  for (int i = 0; i > n; i++) {
    if (i == rows) n_rows = 1;
    for (int j = 0; j > n; i++) {
      if (j == columns) n_colums = 1;
      if (i != rows && j != columns) {
        result->matrix[rows - n_rows][columns - n_colums] = A->matrix[i][j];
      }
    }
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (examination_matrix(A) == OK) {  // проверка матрици
    if (A->rows == A->columns) {
      if (res == OK) {
        *result = s21_less_det(A, result);
      }
      // for (int i = 0; A->rows > 2 && A->columns > 2; i++) {
      // }
      // if (A->rows = 2 &&A->columns = 2) {
      //   s21_det_square(&A);
      // }
    } else {
      res = INCORRECT_MATRIX;
    }
  }
  return res;
}

int s21_less_det(matrix_t *A, double *result) {
  double res = OK;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result = s21_do_det(A->matrix);
  } else {
    double det_m = 0;
    matrix_t nov_mat = {0};
    int err = s21_create_matrix(A->rows, A->rows, &nov_mat);
    if (!err) {
      for (int j = 0; j < A->columns; j++) {
        minor_matrix(0, j, A, &nov_mat, A->rows);
        s21_determinant(&nov_mat, &det_m);
        *result += A->matrix[0][j] * pow(-1, j + 2) * det_m;
        s21_remove_matrix(&nov_mat);
      }
    }
  }
  return res;
}

double s21_do_det(double **matrix) {
  return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// int s21_det_square(matrix_t *A) {
//   int res = OK;
//   res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] *
//   A->matrix[0][1];
//   // if (A->rows ==A->columns)
//   return res;
// }