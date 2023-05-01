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
  int ret = INCORRECT_MATRIX;  // изначально даем значение ошибки ввода данных
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
      ret = OK;
    }
  }
  return ret;
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
