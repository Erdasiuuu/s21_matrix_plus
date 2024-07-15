#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_

class S21Matrix {
 public:
  S21Matrix();
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  ~S21Matrix();

  bool S21Matrix::EqMatrix(const S21Matrix& other);
  inline bool S21Matrix::GetDiff(double value1, double value2);

 private:
  int rows_;
  int cols_;
  double** matrix_;
  static const double EPS = 1e-6;
  enum class Status {
};

#endif //CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_S21_MATRIX_OOP_H_
