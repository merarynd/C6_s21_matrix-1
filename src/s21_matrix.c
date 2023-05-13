#include "s21_matrix.h"

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

int examination_matrix(matrix_t *A) {  // проверка матрици
  int exam = OK;
  if (A->matrix == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0)
    exam = INCORRECT_MATRIX;  // соответсвенно всех ее компанентов
  return exam;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (EXAM_A) {  // проверка матрици
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
  if (EXAM_A && EXAM_B) {  // проверка матрици
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
        res = INCORRECT_MATRIX;  // некорректная матрица
      }
    } else {
      res = INCORRECT_MATRIX;  // некорректная матрица
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (EXAM_A && EXAM_B) {  // проверка матрици
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
        res = INCORRECT_MATRIX;  // некорректная матрица
      }
    } else {
      res = INCORRECT_MATRIX;  // некорректная матрица
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (EXAM_A && EXAM_B) {  // проверка матрици
    if ((A->columns == B->rows)) {
      res = s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] +=
                A->matrix[i][k] * B->matrix[k][j];  // перемножение матриц
          }
        }
      }
    } else {
      res = CALC_ERROR;  // Ошибка вычисления(нельзя провести вычесления)
    }
  } else {
    res = INCORRECT_MATRIX;  // некорректная матрица
  }
  return res;
}

// int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
//   int res = OK;
//   if ((examination_matrix(A) == OK && examination_matrix(B) == OK) &&
//       (A->columns == B->columns && A->rows == B->rows)) {  // проверка
//       sматрици
//     if (A->columns == B->rows) {  // проверяем параметры матриц
//       res = s21_create_matrix(A->rows, A->columns, result);
//       if (res == OK) {
//         for (int i = 0; i < A->rows; i++) {       // проходимся по
//           for (int j = 0; j < A->columns; j++) {  // всей матрице
//             result->matrix[i][j] += A->matrix[i][j] * B->matrix[i][j];
//           }
//         }
//       } else {
//         res = INCORRECT_MATRIX;
//       }
//     } else {
//       res = CALC_ERROR;
//     }
//   }
//   return res;
// }

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (EXAM_A && EXAM_B) {  // проверка матриц
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

// int s21_eq_matrix(matrix_t *A, matrix_t *B) {
//   int res = SUCCESS;
//   if (examination_matrix(A) == FAILURE ||
//       examination_matrix(B) == FAILURE) {  // проверка матриц
//     res = FAILURE;
//   } else {
//     if (A->rows == B->rows && A->columns == B->columns) {
//       for (int i = 0; i < A->rows; i++) {       // проходимся по
//         for (int j = 0; j < A->columns; j++) {  // всей матрице
//           if (fabs(A->matrix[i][j] - B->matrix[i][j]) < 1e-7) {
//             res = SUCCESS;
//             break;
//           }
//         }
//       }
//     }
//   }
//   return res;
// }

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
  if (EXAM_A) {  // проверка матрици
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
        res = INCORRECT_MATRIX;  // некорректная матрица
      }
    } else {
      res = CALC_ERROR;  // Ошибка вычисления(нельзя провести вычесления)
    }
  } else {
    res = INCORRECT_MATRIX;  // некорректная матрица
  }
  // s21_remove_matrix(&A);// чистка
  return res;
}

void minor_matrix(int rows, int columns, matrix_t *A, matrix_t *result, int n) {
  int n_columns = 0, n_rows = 0;
  result->rows = n - 1;  // убираем у каждого параметра
  result->columns = n - 1;  // по одному ряду/столбцу
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
  if (EXAM_A) {  // проверка матрици
    if (A->rows == A->columns) {
      if (res == OK) {
        *result = s21_less_det(A, A->rows);
      }
    } else {
      res = CALC_ERROR;  // Ошибка вычисления(нельзя провести вычесления)
    }
  } else {
    res = INCORRECT_MATRIX;  // некорректная матрица
  }
  return res;
}

int s21_less_det(matrix_t *A, int n) {
  double res = OK;
  if (n == 1) {  // если матрица из одного числа
    res = A->matrix[0][0];
  } else if (n == 2) {  // если матрица из 4 чисел
    res = s21_do_det(A->matrix);
  } else {  // слобци/строки размером > 2 && !=0
    double det_m = 0;
    matrix_t nov_mat = {0};
    int err =
        s21_create_matrix(A->rows, A->rows, &nov_mat);  // создание матрици
    if (!err) {
      for (int j = 0; j < A->columns; j++) {
        minor_matrix(0, j, A, &nov_mat,
                     A->rows);  // поиск минора для уменешения матрици на 1
                                // столб и строку
        s21_determinant(&nov_mat,
                        &det_m);  // поиск детерминанта полученой матрици
        res += A->matrix[0][j] * pow(-1, j + 2) * det_m;
        // s21_remove_matrix(&nov_mat);// чистка
      }
    }
    s21_remove_matrix(&nov_mat);  // чистка
  }
  return res;
}

double s21_do_det(double **matrix) {
  return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

// int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
//   int res = OK;
//   double n_det = 0;
//   if (EXAM_A) {  // проверка матрици
//                  // res = s21_create_matrix(A->columns, A->rows, result);
//     // res = s21_determinant(A, &n_det);
//     if (A->rows == A->columns) {
//       if (res == OK) {
//         res = s21_in_mat(A, n_det, result);
//         // res = s21_determinant(A, result);
//       }
//     } else {
//       res = CALC_ERROR;  // Ошибка вычисления(нельзя провести вычесления)
//     }
//   } else {
//     res = INCORRECT_MATRIX;  // некорректная матрица
//   }
//   return res;
// }

// int s21_in_mat(matrix_t *A, double n_det, matrix_t *result) {
//   int res = OK;
//   // double n_det = 0;
//   if (fabs(n_det) > 1e-6) {
//     matrix_t n_mat = {0};
//     res = s21_determinant(A, &n_det);
//     if (res == OK) {
//       s21_calc_complements(A, &n_mat);
//       s21_transpose(A, &n_mat);
//       for (int i = 0; i < A->rows; i++) {       // проходимся по
//         for (int j = 0; j < A->columns; j++) {  // всей матрице
//           result->matrix[i][j] /= n_det;
//         }
//       }
//       s21_remove_matrix(&n_mat);  // чистка
//       // s21_remove_matrix(A);  // чистка
//     }
//   }
//   return res;
// }