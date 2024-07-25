#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>  // X
#include <stdexcept>
#include <utility>

class S21Matrix {
 public:
  S21Matrix();
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double& operator()(int i, int j);

  void SetRows(int rows);
  void SetCols(int cols);
  int GetRows() const;
  int GetCols() const;
  double** GetMatrix();
  void SetMatrix(double** matrix);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  void UpBiggerValue(int index, double& result);
  void DiffRows(int index);
  S21Matrix GetMinorMatrix(int row, int col) const;
  void AllocateMatrix();

  static const std::string INCORRECT_SIZE;
  static const double EPS;

  inline bool GetDiff(const double value1, const double value2) const;
};

S21Matrix operator*(double number, const S21Matrix& matrix) noexcept;

#endif  // CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
