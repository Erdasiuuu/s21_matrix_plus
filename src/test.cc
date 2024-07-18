#include "s21_matrix_oop/s21_matrix_oop.h"
#include <gtest/gtest.h>

#define DEFAULT_VALUE_ROWS 3
#define DEFAULT_VALUE_COLUMNS 3
#define GET_DIFF(x, y) (fabs(x - y) <= EPS)

void FillMatrix(double* arr, S21Matrix* struct_matrix) {
  int count = 0;
  double** matrix = struct_matrix->GetMatrix();
  for (int i = 0; i < struct_matrix->GetRows(); ++i) {
    for (int j = 0; j < struct_matrix->GetCols(); ++j) {
      matrix[i][j] = arr[count++];
    }
  }
  struct_matrix->SetMatrix(matrix);
}

void OutMatrix(S21Matrix* struct_matrix) {
  int count = 0;
  double** matrix = struct_matrix->GetMatrix();
  for (int i = 0; i < struct_matrix->GetRows(); ++i) {
    for (int j = 0; j < struct_matrix->GetCols(); ++j) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  struct_matrix->SetMatrix(matrix);
}

bool CheckMatrix(S21Matrix matrix, double arr[]) {
  bool result = true;
  int count = 0;
  double** matrix_arr = matrix.GetMatrix();
  for (int i = 0; i < matrix.GetRows() && result; ++i) {
    for (int j = 0; j < matrix.GetCols() && result; ++j) {
      if (!GET_DIFF(matrix_arr[i][j], arr[count++])) {
        result = false;
      }
    }
  }
  return result;
}

TEST(Matrix, DefaultConstructor) {
  S21Matrix* matrix = new S21Matrix();
  EXPECT_EQ(matrix->GetRows(), 0);
  EXPECT_EQ(matrix->GetCols(), 0);
  delete matrix;
}

TEST(Matrix, ConstructorWithRowsCols) {
  int rows = 2;
  int cols = 3;
  double arr[6] = {0, 0, 0, 0, 0, 0};
  S21Matrix matrix(rows, cols);
  EXPECT_EQ(matrix.GetRows(), rows);
  EXPECT_EQ(matrix.GetCols(), cols);
  EXPECT_TRUE(CheckMatrix(matrix, arr));
}

TEST(Matrix, ConstructorWithOther) {
  int rows_1 = 2, cols_1 = 5;
  double arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  S21Matrix matrix(rows_1, cols_1);
  S21Matrix result_matrix(matrix);
  EXPECT_EQ(result_matrix.GetRows(), rows_1);
  EXPECT_EQ(result_matrix.GetCols(), cols_1);
  EXPECT_TRUE(CheckMatrix(result_matrix, arr));
}

#if 0
TEST(Matrix, ConstructorWithOtherMove) {
  int rows = 2, cols = 10;
  double arr[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  S21Matrix matrix_1(rows, cols);
  S21Matrix result_matrix(std::move(matrix_1));
  EXPECT_EQ(result_matrix.GetRows(), rows);
  EXPECT_EQ(result_matrix.GetCols(), cols);
  EXPECT_TRUE(CheckMatrix(result_matrix, arr));
  EXPECT_EQ(matrix_1.GetRows(), 0);
  EXPECT_EQ(matrix_1.GetCols(), 0);
}

#endif

TEST(Matrix, EqMatrix) {
  int rows = 2;
  int cols = 2;
  double arr_1[4] = {1.1, 2.2, 3.3, 4.4};
  double arr_2[4] = {1.1, 2.2, 3.3, 4.4};
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_2));
}
TEST(Matrix, SumMatrix) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double expect_result[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  matrix_1.SumMatrix(matrix_2);
  S21Matrix matrix_expect(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(expect_result, &matrix_expect);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_expect));
}

TEST(Matrix, SubMatrix) {
  int rows = 4, cols = 3;
  double arr_1[12] = {0, 6, 5, 4, 8.4, 1, 9.0, 5.1, 1, -10, 9, 8.3};
  double arr_2[12] = {0, 6, 5, 4, 8.4, 1, 9.0, 5.1, 1, -10, 9, 8.3};
  double expect_result[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  matrix_1.SubMatrix(matrix_2);
  S21Matrix matrix_expect(rows, cols);
  FillMatrix(expect_result, &matrix_expect);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_expect));
}

TEST(Matrix, MulNumber) {
  int rows = 2, cols = 1;
  double num = 4;
  double arr_1[2] = {4, -9};
  double expect_result[2] = {16, -36};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  S21Matrix matrix_expect(rows, cols);
  FillMatrix(expect_result, &matrix_expect);
  matrix_1.MulNumber(num);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_expect));
}

TEST(Matrix, MulMatrix) {
  double arr_1[9] = {1.3, -0.1, 8, -4, 87, -1, -46, -2.342, -234};
  double arr_2[9] = {7, -9, 3.3, 7.1, -0.9, -4.5, -3.45, -1, 4.8};
  double expect_result[9] = {-19.21, -19.61,   43.14,    593.15,   -41.3,
                             -409.5, 468.6718, 650.1078, -1264.461};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  matrix_1.MulMatrix(matrix_2);
  S21Matrix matrix_expect(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(expect_result, &matrix_expect);
  OutMatrix(&matrix_expect);
  OutMatrix(&matrix_1);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_expect));
}

#if 0
TEST(Matrix, Transpose) {
  int rows = 2, cols = 2;
  double arr_1[4] = {1.1, 2.8, -1.0, -0.9};
  double expect_result[4] = {1.1, -1.0, 2.8, -0.9};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  S21Matrix matrix_expect(rows, cols);
  FillMatrix(expect_result, &matrix_expect);
  S21Matrix transpose_matrix = matrix_1.Transpose();
  EXPECT_TRUE(transpose_matrix.EqMatrix(matrix_expect));
}

TEST(Matrix, CalcComplements) {
  int rows = 4, cols = 4;
  double arr_1[16] = {1, -9, -9, 1, 54, 1, -1, 6, 8, 1, -1, -9, 1, 4, -123, 1};
  double expect_result[16] = {-1785, 65713, 2167,  5474, -10186, -1938,
                              -221,  -9245, -6959, 5472, 624,    61823,
                              270,   -4837, 4775,  -828};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  S21Matrix matrix_expect(rows, cols);
  FillMatrix(expect_result, &matrix_expect);
  EXPECT_TRUE(matrix_1.CalcComplements().EqMatrix(matrix_expect));
}

TEST(Matrix, CalcComplementsWithSize1) {
  int rows = 1, cols = 1;
  double arr_1[1] = {2};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  S21Matrix result_matrix = matrix_1.CalcComplements();
  double** matrix_arr = result_matrix.GetMatrix();
  EXPECT_TRUE(result_matrix.GetRows() == 1);
  EXPECT_TRUE(result_matrix.GetCols() == 1);
  EXPECT_TRUE(matrix_arr[0][0] == 1);
}

TEST(Matrix, Determinant) {
  int rows = 4, cols = 4;
  double arr_1[16] = {1, -9, -9, 1, 54, 1, -1, 6, 8, 1, -1, -9, 1, 4, -123, 1};
  double det = -607231;
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_DOUBLE_EQ(matrix_1.Determinant(), det);
}

TEST(Matrix, DeterminantSize1) {
  int rows = 1, cols = 1;
  double arr_1[1] = {3};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  double det = matrix_1.Determinant();
  EXPECT_DOUBLE_EQ(det, matrix_1.GetMatrix()[0][0]);
}

TEST(Matrix, InverseMatrix) {
  int rows = 3, cols = 3;
  double arr_1[9] = {9, -1, -2, -3, 1, 5, 6, 2, -1};
  double expect_result[9] = {0.107843, 0.049019, 0.029411, -0.264705, -0.029411,
                             0.382352, 0.117647, 0.235294, -0.058823};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  S21Matrix matrix_expect(rows, cols);
  FillMatrix(expect_result, &matrix_expect);
  EXPECT_TRUE(matrix_1.InverseMatrix().EqMatrix(matrix_expect));
}

TEST(Matrix, IndexesOperator) {
  int rows = 2, cols = 2;
  double arr[4] = {1, 2, 3, 4};
  S21Matrix matrix(rows, cols);
  matrix(0, 0) = arr[0];
  matrix(0, 1) = arr[1];
  matrix(1, 0) = arr[2];
  matrix(1, 1) = arr[3];
  double** m = matrix.GetMatrix();
  EXPECT_DOUBLE_EQ(m[0][0], arr[0]);
  EXPECT_DOUBLE_EQ(m[0][1], arr[1]);
  EXPECT_DOUBLE_EQ(m[1][0], arr[2]);
  EXPECT_DOUBLE_EQ(m[1][1], arr[3]);
}

TEST(Matrix, IndexesOperatorFail) {
  int rows = 2, cols = 2;
  S21Matrix matrix(rows, cols);
  EXPECT_THROW(matrix(3, 3), std::out_of_range);
}

TEST(Matrix, PlusOperator) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_result(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 = matrix_1 + matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, MinusOperator) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {-8, -6, -4, -2, 0, 2, 4, 6, 8};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_result(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 = matrix_1 - matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, MulMatrixOperator) {
  double arr_1[9] = {1.3, -0.1, 8, -4, 87, -1, -46, -2.342, -234};
  double arr_2[9] = {7, -9, 3.3, 7.1, -0.9, -4.5, -3.45, -1, 4.8};
  double expect_result[9] = {-19.21, -19.61,   43.14,    593.15,   -41.3,
                             -409.5, 468.6718, 650.1078, -1264.461};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_result(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(expect_result, &matrix_result);
  matrix_1 = matrix_1 * matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, MulNumberOperator) {
  int rows = 2, cols = 1;
  double arr_1[2] = {3, -3};
  double arr_result[2] = {-3, 3};
  double num = -1;
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_result(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 = matrix_1 * num;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, AssignmentOperator) {
  int rows = 2, cols = 1;
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_result = matrix_1;
  EXPECT_TRUE(matrix_result.EqMatrix(matrix_1));
}

TEST(Matrix, EqualsOperator) {
  int rows = 2, cols = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  double arr_2[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(Matrix, PlusAssignmentOperator) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_result(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 += matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, MinusAssignmentOperator) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {-8, -6, -4, -2, 0, 2, 4, 6, 8};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_result(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 -= matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, MulMatrixAssignmentOperator) {
  double arr_1[9] = {1.3, -0.1, 8, -4, 87, -1, -46, -2.342, -234};
  double arr_2[9] = {7, -9, 3.3, 7.1, -0.9, -4.5, -3.45, -1, 4.8};
  double expect_result[9] = {-19.21, -19.61,   43.14,    593.15,   -41.3,
                             -409.5, 468.6718, 650.1078, -1264.461};
  S21Matrix matrix_1(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_2(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  S21Matrix matrix_result(DEFAULT_VALUE_ROWS, DEFAULT_VALUE_COLUMNS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(expect_result, &matrix_result);
  matrix_1 *= matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, MulNumberAssignmentOperator) {
  int rows = 2, cols = 1;
  double arr_1[2] = {3, -3};
  double arr_result[2] = {-3, 3};
  double num = -1;
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_result(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 *= num;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Matrix, SetRows) {
  int rows = 2, cols = 2;
  int new_rows = 3;
  double arr_1[4] = {1, 2, 3, 4};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  matrix_1.SetRows(new_rows);
  new_rows = 1;
  matrix_1.SetRows(new_rows);
  EXPECT_TRUE(matrix_1.GetRows() == new_rows);
}

TEST(Matrix, SetCols) {
  int rows = 2, cols = 2;
  int new_cols = 3;
  double arr_1[4] = {1, 2, 3, 4};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  matrix_1.SetCols(new_cols);
  double** matrix = matrix_1.GetMatrix();
  EXPECT_DOUBLE_EQ(matrix[0][2], 0);
  EXPECT_DOUBLE_EQ(matrix[1][2], 0);
  new_cols = 1;
  matrix_1.SetCols(new_cols);
  EXPECT_TRUE(matrix_1.GetCols() == new_cols);
}

TEST(Matrix, SetRowsException) {
  int new_cols = -1;
  S21Matrix matrix_1(1, 1);
  EXPECT_THROW(matrix_1.SetCols(new_cols), std::out_of_range);
}

TEST(Matrix, SetColsException) {
  int new_rows = -1;
  S21Matrix matrix_1(1, 1);
  EXPECT_THROW(matrix_1.SetRows(new_rows), std::out_of_range);
}

TEST(Matrix, EqMatrixException) {
  int rows_1 = 2, cols_1 = 3;
  int rows_2 = 2, cols_2 = 2;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  double arr_2[4] = {1, 2, 3, 4};
  S21Matrix matrix_1(rows_1, cols_1);
  S21Matrix matrix_2(rows_2, cols_2);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_2));
  double arr_3[6] = {1, 2, 3, 4, 5, 6.1};
  S21Matrix matrix_3(rows_1, cols_1);
  FillMatrix(arr_3, &matrix_3);
  EXPECT_FALSE(matrix_1.EqMatrix(matrix_3));
}

TEST(Matrix, MulMatrixException) {
  int rows_1 = 2, cols_1 = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows_1, cols_1);
  S21Matrix matrix_2(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.MulMatrix(matrix_2), std::out_of_range);
}

TEST(Matrix, CalcComplementsException) {
  int rows_1 = 2, cols_1 = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.CalcComplements(), std::out_of_range);
}

TEST(Matrix, DeterminantException) {
  int rows_1 = 2, cols_1 = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.Determinant(), std::out_of_range);
}

TEST(Matrix, InverseMatrixException) {
  int rows_1 = 2, cols_1 = 2;
  double arr_1[4] = {2, 2, 2, 2};
  S21Matrix matrix_1(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.InverseMatrix(), std::out_of_range);
}

TEST(Matrix, ConstructorException) {
  int rows_1 = -1, cols_1 = 2;
  EXPECT_THROW(S21Matrix matrix_1(rows_1, cols_1), std::out_of_range);
}

TEST(Matrix, ArithmeticException) {
  int rows_1 = 2, cols_1 = 3;
  int rows_2 = 2, cols_2 = 2;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  double arr_2[4] = {1, 2, 3, 4};
  S21Matrix matrix_1(rows_1, cols_1);
  S21Matrix matrix_2(rows_2, cols_2);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::out_of_range);
}
#endif
int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
