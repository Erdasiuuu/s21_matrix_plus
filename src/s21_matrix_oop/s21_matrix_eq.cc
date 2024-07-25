#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    result = false;
  }
  for (int i = 0; i < this->rows_ && result == true; i++) {
    for (int j = 0; j < this->cols_ && result == true; j++) {
      result = GetDiff(this->matrix_[i][j], other.matrix_[i][j]);
    }
  }
  return result;
}

inline bool S21Matrix::GetDiff(const double value1, const double value2) const {
  return std::abs(value1 - value2) < S21Matrix::EPS;  // Try without namespace
}
