#ifndef C_SPARSE_MATRIX_H
#define C_SPARSE_MATRIX_H

#include "matrix.h"

struct SparseElement {
    int row;
    int col;
    int val;
};

class CSparseMatrix {
private:
    SparseElement* element;
    int capacity;

public:
    CSparseMatrix();                              // 기본 생성자
    CSparseMatrix(int size);                      // 크기 기반 생성자
    CSparseMatrix(const CSparseMatrix& other);    // 복사 생성자
    ~CSparseMatrix();                             // 소멸자

    SparseElement* getElements() const;
    int getCapacity() const;
    void printSparseMatrix() const;

    // 일반 행렬 → 희소 행렬 변환
    static CSparseMatrix structArraySparseMatrixCOO(const Matrix& matrix);
    // 희소 행렬 직접 생성 (70% 확률로 0 포함)
    static CSparseMatrix generateRandomSparseMatrix(int rows, int cols);


    // 희소 행렬 연산
    static CSparseMatrix transposeMatrix(const CSparseMatrix& matrix);
    static CSparseMatrix sumMatrix(const CSparseMatrix& A, const CSparseMatrix& B);
    static CSparseMatrix multMatrix(const CSparseMatrix& A, const CSparseMatrix& B);
};

#endif // C_SPARSE_MATRIX_H