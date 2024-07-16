#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
	S21Matrix copy(other);
	*this = std::move(copy);
	return *this;
}
