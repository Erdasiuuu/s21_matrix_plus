#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_

#include <iostream> // X
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
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
          S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix InverseMatrix();

        S21Matrix operator+(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
        S21Matrix operator*(const S21Matrix& other);
        S21Matrix operator*(double num);
        bool operator==(const S21Matrix& other) const;
        S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
        S21Matrix operator+=(const S21Matrix& other);
        S21Matrix operator-=(const S21Matrix& other);
        S21Matrix operator*=(const S21Matrix& other);
        S21Matrix operator*=(const double num);
        double& operator()(int i, int j);

	friend void Out(const S21Matrix& m);

        void SetRows(int rows);
        void SetCols(int cols);
        int GetRows();
        int GetCols();
        double** GetMatrix();
        void SetMatrix(double** matrix);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  void UpBiggerValue(int index, double& result);
  void DiffRows(int index);

  static const std::string INCORRECT_SIZE;
  static const double EPS;

  inline bool GetDiff(const double value1, const double value2) const;
};

#endif //CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
