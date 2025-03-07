#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::logic_error(S21Matrix::INCORRECT_SIZE + "(SumMatrix)");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::logic_error(S21Matrix::INCORRECT_SIZE + "(SubMatrix)");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::logic_error(S21Matrix::INCORRECT_SIZE + "(MulMatrix)");
  }

  S21Matrix result(this->rows_, other.cols_);
  for (int row = 0; row < result.rows_; row++) {
    for (int col = 0; col < result.cols_; col++) {
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[row][col] +=
            this->matrix_[row][k] * other.matrix_[k][col];
      }
    }
  }
  *this = std::move(result);
}
