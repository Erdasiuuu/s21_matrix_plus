#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
	S21Matrix copy(other);
	*this = std::move(copy);
	return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
	if (this != &other) {
		std::swap(rows_, other.rows_);
		std::swap(cols_, other.cols_);
		std::swap(matrix_, other.matrix_);
	}
	return *this;
}
