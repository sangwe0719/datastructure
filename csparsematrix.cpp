#include "csparsematrix.h"
#include "matrix.h"
#include <iostream>
#include <cstdlib>

//기본생성자
CSparseMatrix::CSparseMatrix() : element(nullptr), capacity(0) {}

// size 만큼 구조체 배열을 동적으로 할당함
// capacity 는 희소행렬의 최대원소 개수
CSparseMatrix::CSparseMatrix(int size) : capacity(size) {
    element = new SparseElement[capacity];
}

// Deep copy
CSparseMatrix::CSparseMatrix(const CSparseMatrix& other) : capacity(other.capacity) {
    element = new SparseElement[capacity];
    for (int i = 0; i < capacity; ++i) {
        element[i] = other.element[i];
    }
}

// 메모리 누수 방지
CSparseMatrix::~CSparseMatrix() {
    delete[] element;
}

SparseElement* CSparseMatrix::getElements() const {
    return element;
}

int CSparseMatrix::getCapacity() const {
    return capacity;
}

// 희소행렬 구조체배열로 출력
void CSparseMatrix::printSparseMatrix() const {
    for (int i = 0; i <= element[0].val; ++i) {
        std::cout << "[" << element[i].row << ", " << element[i].col << ", " << element[i].val << "]\n";
    }
}


// 일반행렬 -> 희소행렬로 변환
CSparseMatrix CSparseMatrix::structArraySparseMatrixCOO(const Matrix& matrix) {
    int row = matrix.getRows();  
    int col = matrix.getCols(); 
    int count = 0;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (matrix.getElement(i, j) != 0)
                ++count;
        }
    }

    CSparseMatrix sparse(count + 1); // 첫 번째 요소는 메타데이터
    sparse.getElements()[0] = {row, col, count};

    int idx = 1;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int val = matrix.getElement(i, j);
            if (val != 0) {
                sparse.getElements()[idx++] = {i, j, val};
            }
        }
    }

    return sparse;
}

// 희소행렬 직접 생성: 70% 확률로 0을 포함한 행렬을 생성 후 변환
CSparseMatrix CSparseMatrix::generateRandomSparseMatrix(int rows, int cols) {
    Matrix m(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value = (rand() % 100 < 70) ? 0 : rand() % 10; // 70% 확률로 0
            m.setElement(i, j, value);
        }
    }
    return structArraySparseMatrixCOO(m);
}

//입력된 희소행렬(A)을 전치된 희소행렬 로 반환함
CSparseMatrix CSparseMatrix::transposeMatrix(const CSparseMatrix& A) {// A는 원본 희소행렬, CSparsMatrix는 전치된 희소행렬
    int rows = A.element[0].row; // 행 개수 추출
    int cols = A.element[0].col; // 열 개수 추출
    int count = A.element[0].val; // 비제로 원소 개수 추출

    CSparseMatrix transposed(count + 1); // element[0]에 행렬데이터를 저장
    transposed.element[0] = {cols, rows, count}; //{ 행 수, 열 수, 비제로 원소수 }

    int* colCount = new int[cols]{}; //각 열에 몇개의 비제로 원소가 있는지 저장   
    int* startPos = new int[cols]{}; // 전치 행렬에서 이 열이 어디서 시작 할 지를 계산함

    for (int i = 1; i <= count; ++i) // 전치 후에는 행과 열의 번호가 바뀌므로, A의 열 번호에 해당하는 colCount[]값을 증가
        ++colCount[A.element[i].col];

    startPos[0] = 1;
    for (int i = 1; i < cols; ++i)
        startPos[i] = startPos[i - 1] + colCount[i - 1]; // 나머지 열의 시작 위치를 계산

    //전치행렬에 값 삽입
    for (int i = 1; i <= count; ++i) {
        int col = A.element[i].col;
        int pos = startPos[col]++;
        transposed.element[pos] = {A.element[i].col, A.element[i].row, A.element[i].val};
    }

    delete[] colCount;
    delete[] startPos;
    return transposed;
}

// 두 희소 행렬을 더하는 함수
CSparseMatrix CSparseMatrix::sumMatrix(const CSparseMatrix& A, const CSparseMatrix& B) {
    CSparseMatrix result(A.capacity + B.capacity);
    result.element[0] = {A.element[0].row, A.element[0].col, 0};

    int i = 1, j = 1, idx = 1;
    while (i <= A.element[0].val && j <= B.element[0].val) { // A 와 B의 원소 비교후 더하기
        int rA = A.element[i].row, cA = A.element[i].col;
        int rB = B.element[j].row, cB = B.element[j].col;

        if (rA == rB && cA == cB) {
            int sum = A.element[i].val + B.element[j].val;
            if (sum != 0) result.element[idx++] = {rA, cA, sum};
            ++i; ++j;
        } else if (rA < rB || (rA == rB && cA < cB)) {
            result.element[idx++] = A.element[i++];
        } else {
            result.element[idx++] = B.element[j++];
        }
    }

    while (i <= A.element[0].val)
        result.element[idx++] = A.element[i++];
    while (j <= B.element[0].val)
        result.element[idx++] = B.element[j++];

    result.element[0].val = idx - 1;
    return result;
}

//A와 B의 행렬을 곱셈
CSparseMatrix CSparseMatrix::multMatrix(const CSparseMatrix& A, const CSparseMatrix& B) {
    CSparseMatrix BT = transposeMatrix(B); // A의 행 곱하기 B의 열을 해야하기 때문에 B를 전치시켜서 B의 열을 행처럼 만듦
    CSparseMatrix result(A.element[0].val * BT.element[0].val + 1);
    result.element[0] = {A.element[0].row, B.element[0].col, 0}; // element[0]에 항 * 열 * 항 수 저장

    int idx = 1; //A의 각행과 BT(B의 열)행을 곱셈
    for (int i = 1; i <= A.element[0].val;) {
        int row = A.element[i].row;
        int aStart = i;
        while (i <= A.element[0].val && A.element[i].row == row) ++i;
        int aEnd = i;

        for (int j = 1; j <= BT.element[0].val;) {
            int col = BT.element[j].row;
            int bStart = j;
            while (j <= BT.element[0].val && BT.element[j].row == col) ++j;
            int bEnd = j;

            // 두 행의 일치하는 열끼리 곱하고 누적합 계산
            int sum = 0;
            int x = aStart, y = bStart;
            while (x < aEnd && y < bEnd) {
                if (A.element[x].col == BT.element[y].col) {
                    sum += A.element[x].val * BT.element[y].val;
                    ++x; ++y;
                } else if (A.element[x].col < BT.element[y].col) ++x;
                else ++y;
            }

            // 0이 아닌 항만 희소행렬에 저장
            if (sum != 0)
                result.element[idx++] = {row, col, sum};
        }
    }

    result.element[0].val = idx - 1;
    return result;
}
