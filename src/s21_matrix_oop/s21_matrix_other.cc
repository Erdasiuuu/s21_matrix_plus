#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < this->cols_; i++) {
    for (int j = 0; j < this->rows_; j++) {
      result.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
	if (this->rows_ != this->cols_) {
		throw std::logic_error(INCORRECT_SIZE + "(Determinant)");
	}
	S21Matrix tmp(*this);
	double result = 1.0;
	for (int index = 0; index < tmp.rows_ && std::abs(result) > S21Matrix::EPS; index++) {
		tmp.UpBiggerValue(index, result);
		if (tmp.matrix_[index][index] > S21Matrix::EPS) {
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
    double *tmp = this->matrix_[index];
    this->matrix_[index] = this->matrix_[max_index];
    this->matrix_[max_index] = tmp;
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

