#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_

#include <cstring>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <utility>

class S21Matrix {
 public:
  S21Matrix();
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);





 private:
  int rows_;
  int cols_;
  double** matrix_;
  static const double EPS;
  static const std::string INCORRECT_SIZE;

  inline bool GetDiff(double value1, double value2);
};

const std::string INCORRECT_SIZE = "Matrix sizes not correct for this method";
const double S21Matrix::EPS = 1e-6;

#endif //CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
