#include "s21_matrix_oop.h"

const double S21Matrix::EPS = 1e-6;
const std::string S21Matrix::INCORRECT_SIZE =
    "Matrix sizes not correct for this method";

S21Matrix::S21Matrix() : S21Matrix(0, 0) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::logic_error("The matrix size must be greater or equal than 0");
  }
  matrix_ = new double*[rows_]();
  *matrix_ = new double[rows_ * cols_]();
  for (int i = 1; i < rows_; i++) {
    matrix_[i] = *matrix_ + i * cols_;
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_]();
  *matrix_ = new double[rows_ * cols_]();
  for (int i = 1; i < rows_; i++) {
    matrix_[i] = *matrix_ + i * cols_;
  }
  std::copy(*(other.matrix_), *(other.matrix_) + rows_ * cols_, *matrix_);
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

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::out_of_range("Incorrect size of matrix");
  }
  double** new_matrix = new double*[rows];
  *new_matrix = new double[rows * this->cols_]();
//  for (int i = 1; i < rows; i++
  //size_t length = std::max(rows, this->rows_);
#if 0
  for (int i = 0; i < rows; ++i) {
    new_matrix[i] = new double[this->cols_];
    for (int j = 0; j < this->cols_; ++j) {
      if (rows >= this->rows_) {
        new_matrix[i][j] = 0;
      } else {
        new_matrix[i][j] = this->matrix_[i][j];
      }
    }
  }
#endif
  this->~S21Matrix();
  this->matrix_ = new_matrix;
  this->rows_ = rows;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::out_of_range("Incorrect size of matrix");
  }
  double** new_matrix = new double*[this->rows_];
  for (int i = 0; i < this->rows_; ++i) {
    new_matrix[i] = new double[cols];
    for (int j = 0; j < cols; ++j) {
      if (cols >= this->cols_) {
        new_matrix[i][j] = 0;
      } else {
        new_matrix[i][j] = this->matrix_[i][j];
        ;
      }
    }
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
  this->matrix_ = new_matrix;
  this->cols_ = cols;
}

int S21Matrix::GetCols() { return this->cols_; }

double** S21Matrix::GetMatrix() { return this->matrix_; }

void S21Matrix::SetMatrix(double** matrix) { this->matrix_ = matrix; }
