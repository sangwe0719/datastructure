#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
protected:
    double** data;
    int rows, cols;

public:

    Matrix();
    Matrix(int r, int c);
    virtual ~Matrix();

    // 출력 함수
    virtual void printMatrix() const;

    // 행렬 연산
    virtual Matrix* sumMatrix(const Matrix& matrix1, const Matrix& matrix2);
    virtual Matrix* transposeMatrix(const Matrix& matrix1);
    virtual Matrix* multMatrix(const Matrix& matrix1, const Matrix& matrix2);
    Matrix* addMatrix(const Matrix& matrix1, const Matrix& matrix2);
    Matrix* subtractMatrix(const Matrix& matrix1, const Matrix& matrix2);
    Matrix* multiplyElement(const Matrix& matrix1, const Matrix& matrix2);
    Matrix* divideElement(const Matrix& A, const Matrix& B) const;

    // Getter 함수
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getElement(int row, int col) const { return data[row][col]; }

    // Setter 함수
    void setElement(int row, int col, int value);

    // 내부용 난수 생성 함수
    static int randZero(double probability);
};

#endif // MATRIX_H