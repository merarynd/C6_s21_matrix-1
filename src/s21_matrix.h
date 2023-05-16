#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
// #include <limits.h>
// #include <math.h>
// #include <stdbool.h>
// #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

#define EXAM_A (examination_matrix(A) == OK)
#define EXAM_B (examination_matrix(B) == OK)

enum {
  OK = 0,                // 0
  INCORRECT_MATRIX = 1,  // 1  Ошибка, некорректная матрица
  CALC_ERROR = 2,  // 2  Ошибка вычисления (несовпадающие размеры матриц;
                   // матрица, для
  // которой нельзя провести вычисления и т.д.)
  MALLOC_FAILED = 3  // 3 Ошибка работы с динамической памятью
};

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// работа с матрицами (создание /чистка)
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

// арифметика
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// доп свойства матриц
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// доп функции
int examination_matrix(matrix_t *A);
void minor_matrix(int rows, int columns, matrix_t *A, matrix_t *result, int n);
double s21_do_det(double **matrix);
int s21_less_det(matrix_t *A);
void minor_matrix(int rows, int columns, matrix_t *A, matrix_t *result, int n);
int s21_in_mat(matrix_t *A, double det, matrix_t *result);
void s21_c_c(matrix_t *A, matrix_t *result);

// тесты
void s21_fill(matrix_t *matrixStruct, double value);
void s21_gen_matrix(matrix_t *A);
void s21_anti_gen_matrix(matrix_t *A);

#endif  // S21_MATRIX_H_