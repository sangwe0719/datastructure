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
    CSparseMatrix();
    CSparseMatrix(int size);
    CSparseMatrix(const CSparseMatrix& other);
    ~CSparseMatrix();

    SparseElement* getElements() const;
    int getCapacity() const;
    void printSparseMatrix() const;

    // 일반 행렬 -> 희소 행렬 변환
    static CSparseMatrix structArraySparseMatrixCOO(const Matrix& matrix);
    static CSparseMatrix generateRandomSparseMatrix(int rows, int cols);

    // 희소 행렬 연산
    static CSparseMatrix transposeMatrix(const CSparseMatrix& A);
    static CSparseMatrix sumMatrix(const CSparseMatrix& A, const CSparseMatrix& B);
    static CSparseMatrix subtractMatrix(const CSparseMatrix& A, const CSparseMatrix& B);
    static CSparseMatrix divideMatrix(const CSparseMatrix& A, const CSparseMatrix& B);
    static CSparseMatrix multMatrix(const CSparseMatrix& A, const CSparseMatrix& B);
};

// 정렬용 비교 함수 선언
bool compareSparseElement(const SparseElement& a, const SparseElement& b);

#endif // C_SPARSE_MATRIX_H
