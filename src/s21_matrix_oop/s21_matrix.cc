#include "s21_matrix_oop.h"

const double S21Matrix::EPS = 1e-6;
const std::string S21Matrix::INCORRECT_SIZE =
    "Matrix sizes not correct for this method";

void S21Matrix::AllocateMatrix() {
  this->matrix_ = new double*[rows_]();
  *this->matrix_ = new double[rows_ * cols_]();
  for (int i = 1; i < rows_; i++) {
    this->matrix_[i] = *this->matrix_ + i * cols_;
  }
}

S21Matrix::S21Matrix() : S21Matrix(0, 0) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (this->rows_ < 0 || this->cols_ < 0) {
    throw std::logic_error("The matrix size must be greater or equal than 0");
  }
  this->AllocateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->AllocateMatrix();
  std::copy(*other.matrix_, *other.matrix_ + other.rows_ * other.cols_,
            *this->matrix_);
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    delete[] * matrix_;
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::out_of_range("Incorrect size of matrix");
  }
  double** new_matrix = new double*[rows];
  *new_matrix = new double[rows * this->cols_]();
  for (int i = 1; i < rows; i++) {
    new_matrix[i] = *new_matrix + i * cols_;
  }
  int exist_length = std::min(rows, this->rows_);
  for (int index = 0; index < exist_length; index++) {
    std::copy(new_matrix[index], &new_matrix[index + 1][-1],
              this->matrix_[index]);
  }
  this->~S21Matrix();
  this->matrix_ = new_matrix;
  new_matrix = nullptr;
  this->rows_ = rows;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::out_of_range("Incorrect size of matrix");
  }
  double* new_matrix = new double[this->rows_ * cols]();
  double* current_position = new_matrix;
  int exist_length = std::min(cols, this->cols_);
  for (int i = 0; i < exist_length; i++) {
    std::copy(current_position, current_position + exist_length - 1,
              this->matrix_[i]);
    current_position += exist_length;
  }
  current_position = nullptr;
  delete[] * this->matrix_;
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new_matrix + i * cols;
  }
  this->cols_ = cols;
}

int S21Matrix::GetRows() const { return this->rows_; }

int S21Matrix::GetCols() const { return this->cols_; }

double** S21Matrix::GetMatrix() { return this->matrix_; }

void S21Matrix::SetMatrix(double** matrix) { this->matrix_ = matrix; }
