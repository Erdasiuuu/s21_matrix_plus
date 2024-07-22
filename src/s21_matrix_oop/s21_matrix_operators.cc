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

double& S21Matrix::operator()(int i, int j) {
	if (i < 0 || j < 0 || i > this->rows_ || j >= this->cols_) {
		std::out_of_range("Incorrect indexes");
	}
	return this->matrix_[i][j];
}

bool S21Matrix::operator==(const S21Matrix& other) const {
	return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
	S21Matrix tmp(*this);
	tmp.SumMatrix(other);
	return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
	S21Matrix tmp(*this);
	tmp.SubMatrix(other);
	return tmp;
}

#if 0
S21Matrix operator*(const double num, const S21Matrix& other) {
	S21Matrix tmp = other * num;
	return tmp;
}
#endif

S21Matrix S21Matrix::operator*(double num) {
	S21Matrix tmp(*this);
	tmp.MulNumber(num);
	return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
	S21Matrix tmp(*this);
	tmp.MulMatrix(other);
	return tmp;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
	this->SumMatrix(other);
	return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
	this->SubMatrix(other);
	return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
	this->MulNumber(num);
	return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
	this->MulMatrix(other);
	return *this;
}

