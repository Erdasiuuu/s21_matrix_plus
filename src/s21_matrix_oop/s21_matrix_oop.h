#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_

#define EPS 1e-6
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

  bool EqMatrix(const S21Matrix& other);
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
        S21Matrix operator*(const double num);
        bool operator==(const S21Matrix& other);
        S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
        S21Matrix operator+=(const S21Matrix& other);
        S21Matrix operator-=(const S21Matrix& other);
        S21Matrix operator*=(const S21Matrix& other);
        S21Matrix operator*=(const double num);
        double& operator()(int i, int j);


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
  static const std::string INCORRECT_SIZE;

  inline bool GetDiff(double value1, double value2);
};

#endif //CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
