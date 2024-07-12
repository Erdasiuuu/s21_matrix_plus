#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  ~S21Matrix();
};

#endif
