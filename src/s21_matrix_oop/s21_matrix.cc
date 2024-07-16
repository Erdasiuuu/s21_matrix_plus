#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(0, 0) { }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
	if (rows_ < 0 || cols_ < 0) {
		std::length_error("The matrix size must be greater or equal than 0");
	}
	matrix_ = new double*[rows_]();
	double *new_matrix = new double[rows_ * cols_];
	for (int i = 0; i < rows_; i++) {
		matrix_[i] = new_matrix + i * cols_;
	}
}

S21Matrix::~S21Matrix() {
	delete[] *matrix_;
	delete[] matrix_;
	matrix_ = nullptr;
	rows_ = 0;
	cols_ = 0;
}
