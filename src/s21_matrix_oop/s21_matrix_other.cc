#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < this->cols_; i++) {
    for (int j = 0; j < this->rows_; j++) {
      result.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (this->rows_ != this->cols_) {
    throw std::logic_error(INCORRECT_SIZE + "(Determinant)");
  }
  S21Matrix tmp(*this);
  double result = 1.0;
  for (int index = 0; index < tmp.rows_ && std::abs(result) >= S21Matrix::EPS;
       index++) {
    tmp.UpBiggerValue(index, result);
    if (std::abs(tmp.matrix_[index][index]) >= S21Matrix::EPS) {
      tmp.DiffRows(index);
    }
    result *= tmp.matrix_[index][index];
  }
  return result;
}

void S21Matrix::UpBiggerValue(int index, double& result) {
  int max_index = index;
  double max = std::abs(this->matrix_[index][index]);
  for (int i = index + 1; i < this->rows_; i++) {
    if (std::abs(this->matrix_[i][index]) > max) {
      max_index = i;
      max = std::abs(this->matrix_[i][index]);
    }
  }
  if (max_index != index) {
    for (int i = 0; i < this->cols_; i++) {
      double tmp = this->matrix_[index][i];
      this->matrix_[index][i] = this->matrix_[max_index][i];
      this->matrix_[max_index][i] = tmp;
    }
    result = -result;
  }
}

void S21Matrix::DiffRows(int index) {
  for (int i = index + 1; i < this->rows_; i++) {
    double div = this->matrix_[i][index] / this->matrix_[index][index];
    for (int j = index; j < this->rows_; j++) {
      this->matrix_[i][j] -= div * this->matrix_[index][j];
    }
  }
}

S21Matrix S21Matrix::CalcComplements() const {
  if (this->rows_ != this->cols_) {
    throw std::logic_error(INCORRECT_SIZE + "(CalcComplements)");
  }
  S21Matrix result(this->rows_, this->cols_);

  if (this->rows_ == 1) {
    **result.matrix_ = 1;
  } else {
    for (int row = 0; row < result.rows_; row++) {
      for (int col = 0; col < result.cols_; col++) {
        S21Matrix minor = this->GetMinorMatrix(row, col);
        result.matrix_[row][col] = minor.Determinant();

        if ((row + col) % 2 != 0) {
          result.matrix_[row][col] = -result.matrix_[row][col];
        }
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::GetMinorMatrix(int row, int col) const {
  S21Matrix result(this->rows_ - 1, this->cols_ - 1);
  int row_correct = 0;
  for (int i = 0; i < result.rows_; i++) {
    int col_correct = 0;
    for (int j = 0; j < result.cols_; j++) {
      if (row == i) {
        row_correct = 1;
      }
      if (col == j) {
        col_correct = 1;
      }
      result.matrix_[i][j] = this->matrix_[i + row_correct][j + col_correct];
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (this->rows_ != this->cols_) {
    throw std::logic_error(INCORRECT_SIZE + "(InverseMatrix)");
  }
  double det = this->Determinant();
  if (std::abs(det) < S21Matrix::EPS) {
    throw std::logic_error("Determinant must not equal zero");
  }
  return 1.0 / det * this->Transpose().CalcComplements();
}
