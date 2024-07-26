#include "s21_matrix_oop/s21_matrix_oop.h"
#include <gtest/gtest.h>

#define PREDEFINE_ROWS 3
#define PREDEFINE_COLS 3

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
  double** matrix = struct_matrix->GetMatrix();
  for (int i = 0; i < struct_matrix->GetRows(); ++i) {
    for (int j = 0; j < struct_matrix->GetCols(); ++j) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

bool CheckMatrix(S21Matrix matrix, double arr[]) {
  bool result = true;
  int count = 0;
  double** matrix_arr = matrix.GetMatrix();
  for (int i = 0; i < matrix.GetRows() && result; ++i) {
    for (int j = 0; j < matrix.GetCols() && result; ++j) {
      if (std::abs(matrix_arr[i][j] - arr[count++]) > 1e-6) {
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
TEST(Constructor, ConstructorWithRowsCols1) {
  int rows = 2;
  int cols = 3;
  double arr[6] = {0, 0, 0, 0, 0, 0};
  S21Matrix matrix(rows, cols);
  EXPECT_EQ(matrix.GetRows(), rows);
  EXPECT_EQ(matrix.GetCols(), cols);
  EXPECT_TRUE(CheckMatrix(matrix, arr));
}

TEST(Constructor, ConstructorWithRowsCols2) {
  for (int i = 1; i < 20; ++i) {
    S21Matrix mat(i, i + 1);
    EXPECT_EQ(mat.GetRows(), i);
    EXPECT_EQ(mat.GetCols(), i + 1);
    EXPECT_EQ(mat(i - 1, i), 0);
  }
}

TEST(Method, ConstructorWithRowsColsFailer) {
  int rows_1 = -1, cols_1 = 2;
  EXPECT_THROW(S21Matrix matrix_1(rows_1, cols_1), std::logic_error);
}

TEST(Constructor, ConstructorWithOther1) {
  int rows_1 = 2, cols_1 = 5;
  double arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  S21Matrix matrix(rows_1, cols_1);
  S21Matrix result_matrix(matrix);
  EXPECT_EQ(result_matrix.GetRows(), rows_1);
  EXPECT_EQ(result_matrix.GetCols(), cols_1);
  EXPECT_TRUE(CheckMatrix(result_matrix, arr));
}

TEST(Constructor, ConstructorWithOther2) {
  S21Matrix mat_first(1, 1);
  mat_first(0, 0) = -2;
  S21Matrix mat_second(mat_first);
  EXPECT_EQ(mat_first(0, 0), mat_second(0, 0));
}

TEST(Constructor, ConstructorWithOtherMove1) {
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

TEST(Constructor, ConstructorWithOtherMove2) {
  S21Matrix mat_one(2, 2);
  mat_one(0, 0) = 43;
  mat_one(0, 1) = -3;
  mat_one(1, 0) = 2;
  mat_one(0, 1) = -1;

  S21Matrix mat_two(mat_one + mat_one);
  EXPECT_EQ(mat_two(0, 0), 86);
}

TEST(Method, EqMatrixTrue1) {
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

TEST(Method, EqMatrixTrue2) {
  S21Matrix mat_first(2, 2);
  S21Matrix mat_second(2, 2);
  EXPECT_EQ(mat_second.EqMatrix(mat_first), true);
}

TEST(Method, EqMatrixFalse1) {
  S21Matrix mat_first(2, 2);
  S21Matrix mat_second(2, 2);
  mat_second(0, 0) = 2;
  EXPECT_EQ(mat_second.EqMatrix(mat_first), false);
  mat_first.SetCols(3);
  mat_second(0, 0) = 0;
  EXPECT_EQ(mat_second.EqMatrix(mat_first), false);
}

TEST(Method, EqMatrixFalse2) {
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

TEST(Method, SumMatrix1) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double expect_result[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  matrix_1.SumMatrix(matrix_2);
  S21Matrix matrix_expect(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(expect_result, &matrix_expect);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_expect));
}

TEST(Method, SumMatrix2) {
  S21Matrix mat_first(2, 2);
  S21Matrix mat_second(2, 2);
  S21Matrix check(2, 2);
  mat_first(0, 0) = 32;
  mat_first(0, 1) = 2;
  mat_first(1, 0) = 1;
  mat_first(1, 1) = -3;

  mat_second(0, 0) = 4;
  mat_second(0, 1) = -23;
  mat_second(1, 0) = 0.32;
  mat_second(1, 1) = 3;

  check(0, 0) = 36;
  check(0, 1) = -21;
  check(1, 0) = 1.32;
  check(1, 1) = 0;

  mat_first.SumMatrix(mat_second);
  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(Method, SumMatrixFailer1) {
  EXPECT_THROW(
      {
        S21Matrix mat_first(2, 2);
        S21Matrix mat_second(3, 2);
        mat_first.SumMatrix(mat_second);
      },
      std::logic_error);
}

TEST(Method, SumMatrixFailer2) {
  int rows_1 = 2, cols_1 = 3;
  int rows_2 = 2, cols_2 = 2;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  double arr_2[4] = {1, 2, 3, 4};
  S21Matrix matrix_1(rows_1, cols_1);
  S21Matrix matrix_2(rows_2, cols_2);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  EXPECT_THROW(matrix_1.SumMatrix(matrix_2), std::logic_error);
}

TEST(Method, SubMatrix1) {
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

TEST(Method, SubMatrix2) {
  for (int i = 0; i < 10; ++i) {
    S21Matrix mat_first(i + 1, i + 2);
    S21Matrix mat_second(i + 1, i + 2);
    S21Matrix check(i + 1, i + 2);

    for (int r = 0; r < i + 1; ++r) {
      for (int c = 0; c < i + 2; ++c) {
        mat_first(r, c) = (2.3 + i) * pow(-1, i);
        mat_second(r, c) = (-1111.3 - i) * pow(-1, i);
        check(r, c) = mat_first(r, c) - mat_second(r, c);
      }
    }
    mat_first.SubMatrix(mat_second);
    EXPECT_EQ(check.EqMatrix(mat_first), true);
  }
}

TEST(Method, SubMatrixFailer) {
  EXPECT_THROW(
      {
        S21Matrix mat_first;
        S21Matrix mat_second(2, 2);
        mat_first.SubMatrix(mat_second);
      },
      std::logic_error);
}

TEST(Method, MulNumber1) {
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

TEST(Method, MulNumber2) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 10;
  mat(0, 1) = -23;
  mat(1, 0) = 6;
  mat(1, 1) = 5;
  mat.MulNumber(5);
  S21Matrix check(3, 3);
  check(0, 0) = 50;
  check(0, 1) = -115;
  check(1, 0) = 30;
  check(1, 1) = 25;
  EXPECT_EQ(check.EqMatrix(mat), true);
}

TEST(Method, MulMatrix1) {
  double arr_1[9] = {1.3, -0.1, 8, -4, 87, -1, -46, -2.342, -234};
  double arr_2[9] = {7, -9, 3.3, 7.1, -0.9, -4.5, -3.45, -1, 4.8};
  double expect_result[9] = {-19.21, -19.61,   43.14,    593.15,   -41.3,
                             -409.5, 468.6718, 650.1078, -1264.461};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  matrix_1.MulMatrix(matrix_2);
  S21Matrix matrix_expect(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(expect_result, &matrix_expect);
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_expect));
}

TEST(Method, MulMatrix2) {
  S21Matrix mat_first(2, 3);
  S21Matrix mat_second(3, 2);

  mat_first(0, 0) = 1;
  mat_first(0, 1) = 2;
  mat_first(0, 2) = 3;

  mat_first(1, 0) = 6;
  mat_first(1, 1) = 4;
  mat_first(1, 2) = 5;

  mat_second(0, 0) = 1;
  mat_second(0, 1) = 8;

  mat_second(1, 0) = 7;
  mat_second(1, 1) = 6;

  mat_second(2, 0) = 4;
  mat_second(2, 1) = 2;

  S21Matrix check(2, 2);

  check(0, 0) = 27;
  check(0, 1) = 26;

  check(1, 0) = 54;
  check(1, 1) = 82;

  mat_first.MulMatrix(mat_second);

  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(Method, MulMatrixFailer1) {
  S21Matrix mat_1;
  S21Matrix mat_2(1, 1);
  EXPECT_THROW(mat_1.MulMatrix(mat_2), std::logic_error);
}

TEST(Method, MulMatrixFailer2) {
  int rows_1 = 2, cols_1 = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows_1, cols_1);
  S21Matrix matrix_2(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.MulMatrix(matrix_2), std::logic_error);
}

TEST(Method, Transpose1) {
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

TEST(Method, Transpose2) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  S21Matrix check(2, 2);
  check(0, 0) = 1;
  check(0, 1) = 3;
  check(1, 0) = 2;
  check(1, 1) = 4;
  EXPECT_EQ(check.EqMatrix(mat.Transpose()), true);
}

TEST(Method, CalcComplements1) {
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

TEST(Method, CalcComplements2) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 0;
  mat(1, 1) = 4;
  mat(1, 2) = 2;
  mat(2, 0) = 5;
  mat(2, 1) = 2;
  mat(2, 2) = 1;

  S21Matrix check(3, 3);

  check(0, 0) = 0;
  check(0, 1) = 10;
  check(0, 2) = -20;
  check(1, 0) = 4;
  check(1, 1) = -14;
  check(1, 2) = 8;
  check(2, 0) = -8;
  check(2, 1) = -2;
  check(2, 2) = 4;

  EXPECT_EQ(check == mat.CalcComplements(), true);
}

TEST(Method, CalcComplementsFailer1) {
  S21Matrix mat(3, 2);
  EXPECT_THROW({ mat = mat.CalcComplements(); }, std::logic_error);
}

TEST(Method, CalcComplementsFailer2) {
  int rows_1 = 2, cols_1 = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.CalcComplements(), std::logic_error);
}

TEST(Method, CalcComplementsWithSize1) {
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

TEST(Method, Determinant1) {
  int rows = 4, cols = 4;
  double arr_1[16] = {1, -9, -9, 1, 54, 1, -1, 6, 8, 1, -1, -9, 1, 4, -123, 1};
  double det = -607231;
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_DOUBLE_EQ(matrix_1.Determinant(), det);
}

TEST(Method, DeterminantSize1) {
  int rows = 1, cols = 1;
  double arr_1[1] = {3};
  S21Matrix matrix_1(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  double det = matrix_1.Determinant();
  EXPECT_DOUBLE_EQ(det, matrix_1.GetMatrix()[0][0]);
}

TEST(Method, DeterminantFailer1) {
  S21Matrix mat(3, 2);

  EXPECT_THROW({ mat.Determinant(); }, std::logic_error);
}

TEST(Method, DeterminantFailer2) {
  int rows_1 = 2, cols_1 = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.Determinant(), std::logic_error);
}

TEST(Method, InverseMatrix1) {
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

TEST(Method, InverseMatrix2) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 2;
  mat(0, 1) = 5;
  mat(0, 2) = 7;
  mat(1, 0) = 6;
  mat(1, 1) = 3;
  mat(1, 2) = 4;
  mat(2, 0) = 5;
  mat(2, 1) = -2;
  mat(2, 2) = -3;

  S21Matrix check(3, 3);

  check(0, 0) = 1;
  check(0, 1) = -1;
  check(0, 2) = 1;
  check(1, 0) = -38;
  check(1, 1) = 41;
  check(1, 2) = -34;
  check(2, 0) = 27;
  check(2, 1) = -29;
  check(2, 2) = 24;

  EXPECT_NO_THROW({ EXPECT_EQ(check == mat.InverseMatrix(), true); });
}

TEST(Method, InverseMatrixFailerZeroDeterm) {
  S21Matrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;
  mat(2, 0) = 7;
  mat(2, 1) = 8;
  mat(2, 2) = 9;
  EXPECT_THROW({ mat = mat.InverseMatrix(); }, std::logic_error);
}

TEST(Method, InverseMatrixFailerNotSquare) {
  S21Matrix mat(2, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;
  EXPECT_THROW({ mat = mat.InverseMatrix(); }, std::logic_error);
}

TEST(Method, InverseMatrixFailer) {
  int rows_1 = 2, cols_1 = 2;
  double arr_1[4] = {2, 2, 2, 2};
  S21Matrix matrix_1(rows_1, cols_1);
  FillMatrix(arr_1, &matrix_1);
  EXPECT_THROW(matrix_1.InverseMatrix(), std::logic_error);
}

TEST(Operator, IndexesOperator) {
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

TEST(Operator, IndexesOperatorFail) {
  int rows = 2, cols = 2;
  S21Matrix matrix(rows, cols);
  EXPECT_THROW(matrix(3, 3), std::logic_error);
}

TEST(Operator, IndexesOperator2) {
  S21Matrix mat(2, 2);
  EXPECT_EQ(mat.GetMatrix()[0][0], mat(0, 0));
}

TEST(Operator, PlusOperator) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_result(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 = matrix_1 + matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Operator, MinusOperator) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {-8, -6, -4, -2, 0, 2, 4, 6, 8};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_result(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 = matrix_1 - matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Operator, MulMatrixOperator1) {
  double arr_1[9] = {1.3, -0.1, 8, -4, 87, -1, -46, -2.342, -234};
  double arr_2[9] = {7, -9, 3.3, 7.1, -0.9, -4.5, -3.45, -1, 4.8};
  double expect_result[9] = {-19.21, -19.61,   43.14,    593.15,   -41.3,
                             -409.5, 468.6718, 650.1078, -1264.461};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_result(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(expect_result, &matrix_result);
  matrix_1 = matrix_1 * matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Operator, MulMatrixOperator2) {
  S21Matrix mat_first(3, 3);
  S21Matrix mat_second(3, 3);
  S21Matrix res(3, 3);

  S21Matrix check(3, 3);

  for (int r = 0; r < 3; ++r) {
    for (int c = 0; c < 3; ++c) {
      mat_first(r, c) = r + c + 7;
      mat_second(r, c) = c + 5 * r + 23;
    }
  }
  check(0, 0) = 682;
  check(0, 1) = 706;
  check(0, 2) = 730;

  check(1, 0) = 766;
  check(1, 1) = 793;
  check(1, 2) = 820;

  check(2, 0) = 850;
  check(2, 1) = 880;
  check(2, 2) = 910;

  res = mat_first * mat_second;

  EXPECT_EQ(check.EqMatrix(res), true);
  mat_first *= mat_second;
  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(Operator, MulMatrixOperatorFailer) {
  S21Matrix mat_1;
  S21Matrix mat_2(1, 1);
  EXPECT_THROW(
      {
        mat_1* mat_2;
        mat_1 *= mat_2;
      },
      std::logic_error);
}

TEST(Operator, MulNumberOperator1) {
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

TEST(Operator, MulNumberOperator2) {
  S21Matrix mat(3, 3);
  S21Matrix res;
  mat(0, 0) = 10;
  mat(0, 1) = -23;
  mat(1, 0) = 6;
  mat(1, 1) = 5;
  res = mat * 5;
  S21Matrix check(3, 3);
  check(0, 0) = 50;
  check(0, 1) = -115;
  check(1, 0) = 30;
  check(1, 1) = 25;
  EXPECT_EQ(check.EqMatrix(res), true);
  mat *= 5;
  EXPECT_EQ(check.EqMatrix(mat), true);
}

TEST(Operator, AssignmentOperator) {
  int rows = 2, cols = 1;
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_result = matrix_1;
  EXPECT_TRUE(matrix_result.EqMatrix(matrix_1));
}

TEST(Operator, AssignmentOperatorEqualMatrix) {
  int rows = 2, cols = 1;
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_result(rows, cols);
  matrix_result = matrix_1;
  EXPECT_TRUE(matrix_result.EqMatrix(matrix_1));
}

TEST(Operator, EqualOperator1) {
  S21Matrix mat_first(2, 2);
  S21Matrix mat_second(2, 2);
  EXPECT_EQ(mat_second == mat_first, true);
}

TEST(Operator, EqualOperator2) {
  S21Matrix mat_first(2, 2);
  S21Matrix mat_second(2, 2);
  mat_first(0, 0) = 4;
  mat_first(0, 1) = 3;
  mat_first(1, 0) = 7;
  mat_first(1, 1) = 6;

  mat_second = mat_first;
  EXPECT_EQ(mat_second(0, 0), 4);
}

TEST(Operator, EqualOperatorFalse) {
  S21Matrix mat_first(2, 2);
  S21Matrix mat_second(2, 2);
  mat_second(0, 0) = 2;
  EXPECT_EQ(mat_second == mat_first, false);
  mat_first.SetCols(3);
  mat_second(0, 0) = 0;
  EXPECT_EQ(mat_second == mat_first, false);
}

TEST(Operator, EqualOperator3) {
  int rows = 2, cols = 3;
  double arr_1[6] = {1, 2, 3, 4, 5, 6};
  double arr_2[6] = {1, 2, 3, 4, 5, 6};
  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(rows, cols);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(Operator, PlusAssignmentOperator1) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_result(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 += matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Operator, PlusAssignmentOperator2) {
  S21Matrix mat_first(2, 2);
  S21Matrix mat_second(2, 2);
  S21Matrix res(2, 2);
  S21Matrix check(2, 2);
  mat_first(0, 0) = 32;
  mat_first(0, 1) = 2;
  mat_first(1, 0) = 1;
  mat_first(1, 1) = -3;

  mat_second(0, 0) = 4;
  mat_second(0, 1) = -23;
  mat_second(1, 0) = 0.32;
  mat_second(1, 1) = 3;

  check(0, 0) = 36;
  check(0, 1) = -21;
  check(1, 0) = 1.32;
  check(1, 1) = 0;

  res = mat_first + mat_second;
  EXPECT_EQ(check.EqMatrix(res), true);
  mat_first += mat_second;
  EXPECT_EQ(check.EqMatrix(mat_first), true);
}

TEST(Operator, PlusAssignmentOperatorFailer) {
  EXPECT_THROW(
      {
        S21Matrix mat_first(2, 2);
        S21Matrix mat_second(3, 2);
        mat_first += mat_second;
      },
      std::logic_error);
}

TEST(Operator, MinusAssignmentOperator1) {
  double arr_1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double arr_2[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  double arr_result[9] = {-8, -6, -4, -2, 0, 2, 4, 6, 8};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_result(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(arr_result, &matrix_result);
  matrix_1 -= matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Operator, MinusAssignmentOperator2) {
  for (int i = 0; i < 10; ++i) {
    S21Matrix mat_first(i + 1, i + 2);
    S21Matrix mat_second(i + 1, i + 2);
    S21Matrix check(i + 1, i + 2);
    S21Matrix res(i + 1, i + 2);

    for (int r = 0; r < i + 1; ++r) {
      for (int c = 0; c < i + 2; ++c) {
        mat_first(r, c) = (2.3 + i) * pow(-1, i);
        mat_second(r, c) = (-1111.3 - i) * pow(-1, i);
        check(r, c) = mat_first(r, c) - mat_second(r, c);
      }
    }
    res = mat_first - mat_second;
    EXPECT_EQ(check.EqMatrix(res), true);
    mat_first -= mat_second;
    EXPECT_EQ(check.EqMatrix(mat_first), true);
  }
}

TEST(Operator, MinusAssignmentOperatorFailer) {
  EXPECT_THROW(
      {
        S21Matrix mat_first;
        S21Matrix mat_second(2, 2);
        mat_first - mat_second;
        mat_first -= mat_second;
      },
      std::logic_error);
}

TEST(Operator, MulMatrixAssignmentOperator) {
  double arr_1[9] = {1.3, -0.1, 8, -4, 87, -1, -46, -2.342, -234};
  double arr_2[9] = {7, -9, 3.3, 7.1, -0.9, -4.5, -3.45, -1, 4.8};
  double expect_result[9] = {-19.21, -19.61,   43.14,    593.15,   -41.3,
                             -409.5, 468.6718, 650.1078, -1264.461};
  S21Matrix matrix_1(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_2(PREDEFINE_ROWS, PREDEFINE_COLS);
  S21Matrix matrix_result(PREDEFINE_ROWS, PREDEFINE_COLS);
  FillMatrix(arr_1, &matrix_1);
  FillMatrix(arr_2, &matrix_2);
  FillMatrix(expect_result, &matrix_result);
  matrix_1 *= matrix_2;
  EXPECT_TRUE(matrix_1.EqMatrix(matrix_result));
}

TEST(Operator, MulNumberAssignmentOperator) {
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

TEST(SetGet, SetGetRows1) {
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

TEST(SetGet, SetGetCols1) {
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

TEST(SetGet, SetRowsException) {
  int new_cols = -1;
  S21Matrix matrix_1(1, 1);
  EXPECT_THROW(matrix_1.SetCols(new_cols), std::logic_error);
}

TEST(SetGet, SetColsException) {
  int new_rows = -1;
  S21Matrix matrix_1(1, 1);
  EXPECT_THROW(matrix_1.SetRows(new_rows), std::logic_error);
}

TEST(SetGet, GetRows) {
  S21Matrix mat(1, 1);
  EXPECT_EQ(mat.GetRows(), 1);
  EXPECT_EQ(S21Matrix(3, 3).GetRows(), 3);
  EXPECT_EQ(S21Matrix(5, 3).GetRows(), 5);
}

TEST(SetGet, SetGetRows2) {
  S21Matrix mat(3, 3);
  EXPECT_EQ(mat.GetRows(), 3);
  mat.SetRows(5);
  EXPECT_EQ(mat.GetRows(), 5);
  EXPECT_EQ(mat(4, 0), 0);
}

TEST(SetGet, GetCols) {
  S21Matrix mat(1, 1);
  EXPECT_EQ(mat.GetCols(), 1);
  EXPECT_EQ(S21Matrix(3, 3).GetCols(), 3);
  EXPECT_EQ(S21Matrix(1, 4).GetCols(), 4);
}

TEST(SetGet, SetRowsThrow) {
  S21Matrix mat;
  EXPECT_THROW({ mat.SetRows(-3); }, std::logic_error);
}

TEST(SetGet, SetGetCols2) {
  S21Matrix mat(10, 3);
  EXPECT_EQ(mat.GetCols(), PREDEFINE_COLS);
  mat.SetCols(5);
  EXPECT_EQ(mat.GetCols(), 5);
  EXPECT_EQ(mat(0, 4), 0);
}

TEST(SetGet, SetColsThrow) {
  S21Matrix mat;
  EXPECT_THROW({ mat.SetCols(-200); }, std::logic_error);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
