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
