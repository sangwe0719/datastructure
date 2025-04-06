#include "matrix.h"
#include <cstdlib>
#include <iomanip>
#include <cmath> 

using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            data[i][j] = rand() % 10; // 0이 나올 확률 없이 완전 랜덤 정수 (0~9)
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data; // 메모리누수방지
}

//출력 함수
void Matrix::printMatrix() const {
    for (int i = 0; i < rows; ++i) {
        cout << "[";
        for (int j = 0; j < cols; ++j) {
            double value = data[i][j];

            if (isnan(value)) {
                cout << "NaN";
            } else if (value == static_cast<int>(value)) {
                cout << static_cast<int>(value);
            } else {
                cout << fixed << setprecision(2) << value;
            }

            if (j != cols - 1)cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}


void Matrix::setElement(int row, int col, int value) {
    if (row < rows && col < cols) {
        data[row][col] = value;
    }
}

// 전치행렬 수행
Matrix* Matrix::transposeMatrix(const Matrix& matrix1) {
    int rowCount = matrix1.getRows();
    int colCount = matrix1.getCols();
    Matrix* result = new Matrix(colCount, rowCount);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            result->data[j][i] = matrix1.getElement(i, j);
        }
    }
    return result;
}

// 두 행렬의 같은 위치의 원소끼리 더한 값을 행렬로 반환
Matrix* Matrix::sumMatrix(const Matrix& matrix1, const Matrix& matrix2) {
    int rowCount = matrix1.getRows();
    int colCount = matrix1.getCols();
    Matrix* result = new Matrix(rowCount, colCount);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            result->data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
        }
    }
    return result;
}

// 두 행렬의 같은 위치의 원소끼리 곱한 값을 행렬로 반환
Matrix* Matrix::multiplyElement(const Matrix& matrix1, const Matrix& matrix2) {
    int rowCount = matrix1.getRows();
    int colCount = matrix1.getCols();
    Matrix* result = new Matrix(rowCount, colCount);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            result->data[i][j] = matrix1.data[i][j] * matrix2.data[i][j];
        }
    }
    return result;
}

// 행렬의 덧셈
Matrix* Matrix::addMatrix(const Matrix& matrix1, const Matrix& matrix2) {
    int rowCount = matrix1.getRows();
    int colCount = matrix1.getCols();
    Matrix* result = new Matrix(rowCount, colCount);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            result->data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
        }
    }
    return result;
}

// 행렬의 뺄셈
Matrix* Matrix::subtractMatrix(const Matrix& matrix1, const Matrix& matrix2) {
    int rowCount = matrix1.getRows();
    int colCount = matrix1.getCols();
    Matrix* result = new Matrix(rowCount, colCount);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            result->data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
        }
    }
    return result;
}

// 행렬의 곱셈
Matrix* Matrix::multMatrix(const Matrix& m1, const Matrix& m2) {
    if (m1.cols != m2.rows) {
        cout << "Matrix multiplication not possible" << endl;
        exit(1);
    }

    int rowCount = m1.getRows();
    int colCount = m2.getCols();
    Matrix* result = new Matrix(rowCount, colCount);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            result->data[i][j] = 0;
            for (int k = 0; k < m1.getCols(); ++k) {
                result->data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
    return result;
}
// 행렬의 나눗셈
Matrix* Matrix::divideElement(const Matrix& A, const Matrix& B) const {
    if (A.rows != B.rows || A.cols != B.cols) {
        std::cerr << "Matrix dimension not possible" << std::endl;
        return nullptr;
    }

    Matrix* result = new Matrix(A.rows, A.cols);

    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < A.cols; ++j) {
            int numerator = A.data[i][j];
            int denominator = B.data[i][j];

            if (denominator != 0) {
                double value = static_cast<double>(numerator) / denominator;
                value = floor(value * 100.0) / 100.0; 
                result->data[i][j] = value; 
            } else {
                result->data[i][j] = NAN; // 0으로 나눌 경우 NaN 처리
            }
        }
    }

    return result;
}

// 전치행렬 덧셈
Matrix* Matrix::addTransposed(const Matrix& A, const Matrix& B) {
    Matrix* At = transposeMatrix(A);
    Matrix* Bt = transposeMatrix(B);
    Matrix* result = addMatrix(*At, *Bt);
    delete At;
    delete Bt;
    return result;
}

// 전치행렬 뺄셈
Matrix* Matrix::subtractTransposed(const Matrix& A, const Matrix& B) {
    Matrix* At = transposeMatrix(A);
    Matrix* Bt = transposeMatrix(B);
    Matrix* result = subtractMatrix(*At, *Bt);
    delete At;
    delete Bt;
    return result;
}

// 전치행렬 곱셈
Matrix* Matrix::multiplyTransposed(const Matrix& A, const Matrix& B) {
    Matrix* Bt = transposeMatrix(B);
    Matrix* At = transposeMatrix(A);
    Matrix* product = multMatrix(*Bt, *At);
    delete At;
    delete Bt;
    return product;
}

// 전치행렬 나눗셈
Matrix* Matrix::divideTransposed(const Matrix& A, const Matrix& B) {
    Matrix* At = transposeMatrix(A);
    Matrix* Bt = transposeMatrix(B);
    Matrix* result = divideElement(*At, *Bt);
    delete At;
    delete Bt;
    return result;
}
