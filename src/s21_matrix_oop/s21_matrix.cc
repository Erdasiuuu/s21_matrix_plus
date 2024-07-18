#include "s21_matrix_oop.h"

const std::string S21Matrix::INCORRECT_SIZE = "Matrix sizes not correct for this method";

S21Matrix::S21Matrix() : S21Matrix(0, 0) { }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
	if (rows_ < 0 || cols_ < 0) {
		throw std::logic_error("The matrix size must be greater or equal than 0");
	}
	matrix_ = new double*[rows_]();
	*matrix_ = new double[rows_ * cols_]();
	for (int i = 0; i < rows_; i++) {
		matrix_[i] = *matrix_ + i * cols_;
	}
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
	matrix_ = new double*[rows_]();
	*matrix_ = new double[rows_ * cols_]();
	for (int i = 0; i < rows_; i++) {
		matrix_[i] = *matrix_ + i * cols_;
	}
	std::copy(*matrix_, *matrix_ + rows_ * cols_, *(other.matrix_));
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
	delete[] *matrix_;
	delete[] matrix_;
	matrix_ = nullptr;
	rows_ = 0;
	cols_ = 0;
}


int S21Matrix::GetRows() { return this->rows_; }

int S21Matrix::GetCols() { return this->cols_; }

double** S21Matrix::GetMatrix() { return this->matrix_; }

void S21Matrix::SetMatrix(double** matrix) { this->matrix_ = matrix; }
