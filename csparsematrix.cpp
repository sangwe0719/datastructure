#include "csparsematrix.h"
#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <cmath> 
#include <algorithm>
#include <map>
#include <vector>

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
// 데이터크기 커지면 확률조정 필요. 
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
CSparseMatrix CSparseMatrix::transposeMatrix(const CSparseMatrix& A) {
    int rows = A.element[0].row;
    int cols = A.element[0].col;
    int count = A.element[0].val;

    CSparseMatrix transposed(count + 1);
    transposed.element[0] = {cols, rows, count};

    int* colCount = new int[cols]{};
    int* startPos = new int[cols]{};

    for (int i = 1; i <= count; ++i)
        ++colCount[A.element[i].col];

    startPos[0] = 1;
    for (int i = 1; i < cols; ++i)
        startPos[i] = startPos[i - 1] + colCount[i - 1];

    for (int i = 1; i <= count; ++i) {
        int col = A.element[i].col;
        int pos = startPos[col]++;
        transposed.element[pos] = {A.element[i].col, A.element[i].row, A.element[i].val};
    }

    delete[] colCount;
    delete[] startPos;
    return transposed;
}

bool compareSparseElement(const SparseElement& a, const SparseElement& b) {
    return (a.row < b.row) || (a.row == b.row && a.col < b.col);
}

// 희소행렬의 덧셈
CSparseMatrix CSparseMatrix::sumMatrix(const CSparseMatrix& A, const CSparseMatrix& B) {
    std::map<std::pair<int, int>, int> valueMap;

    for (int i = 1; i <= A.element[0].val; ++i) {
        auto key = std::make_pair(A.element[i].row, A.element[i].col);
        valueMap[key] += A.element[i].val;
    }
    for (int i = 1; i <= B.element[0].val; ++i) {
        auto key = std::make_pair(B.element[i].row, B.element[i].col);
        valueMap[key] += B.element[i].val;
    }

    std::vector<SparseElement> sortedElements;
    for (const auto& entry : valueMap) {
        if (entry.second != 0) {
            sortedElements.push_back({entry.first.first, entry.first.second, entry.second});
        }
    }

    std::sort(sortedElements.begin(), sortedElements.end(), compareSparseElement);

    CSparseMatrix result(static_cast<int>(sortedElements.size()) + 1);
    result.element[0] = {A.element[0].row, A.element[0].col, static_cast<int>(sortedElements.size())};

    for (int i = 0; i < sortedElements.size(); ++i) {
        result.element[i + 1] = sortedElements[i];
    }

    return result;
}

// 희소행렬의 뺄셈
CSparseMatrix CSparseMatrix::subtractMatrix(const CSparseMatrix& A, const CSparseMatrix& B) {
    std::map<std::pair<int, int>, int> valueMap;

    for (int i = 1; i <= A.element[0].val; ++i) {
        auto key = std::make_pair(A.element[i].row, A.element[i].col);
        valueMap[key] += A.element[i].val;
    }
    for (int i = 1; i <= B.element[0].val; ++i) {
        auto key = std::make_pair(B.element[i].row, B.element[i].col);
        valueMap[key] -= B.element[i].val;
    }

    std::vector<SparseElement> sortedElements;
    for (const auto& entry : valueMap) {
        if (entry.second != 0) {
            sortedElements.push_back({entry.first.first, entry.first.second, entry.second});
        }
    }

    std::sort(sortedElements.begin(), sortedElements.end(), compareSparseElement);

    CSparseMatrix result(static_cast<int>(sortedElements.size()) + 1);
    result.element[0] = {A.element[0].row, A.element[0].col, static_cast<int>(sortedElements.size())};

    for (size_t i = 0; i < sortedElements.size(); ++i) {
        result.element[i + 1] = sortedElements[i];
    }

    return result;
}

//희소행렬의 곱셈
CSparseMatrix CSparseMatrix::multMatrix(const CSparseMatrix& A, const CSparseMatrix& B) {
    CSparseMatrix BT = transposeMatrix(B);
    std::map<std::pair<int, int>, int> resultMap;

    for (int i = 1; i <= A.element[0].val;) {
        int rowA = A.element[i].row;
        int aStart = i;
        while (i <= A.element[0].val && A.element[i].row == rowA) ++i;
        int aEnd = i;

        for (int j = 1; j <= BT.element[0].val;) {
            int colB = BT.element[j].row;
            int bStart = j;
            while (j <= BT.element[0].val && BT.element[j].row == colB) ++j;
            int bEnd = j;

            int x = aStart, y = bStart, sum = 0;
            while (x < aEnd && y < bEnd) {
                if (A.element[x].col == BT.element[y].col) {
                    sum += A.element[x].val * BT.element[y].val;
                    ++x; ++y;
                } else if (A.element[x].col < BT.element[y].col) {
                    ++x;
                } else {
                    ++y;
                }
            }

            if (sum != 0)
                resultMap[{rowA, colB}] += sum;
        }
    }

    std::vector<SparseElement> sortedElements;
    for (const auto& kv : resultMap) {
        sortedElements.push_back({kv.first.first, kv.first.second, kv.second});
    }

    std::sort(sortedElements.begin(), sortedElements.end(), compareSparseElement);

    CSparseMatrix result(static_cast<int>(sortedElements.size()) + 1);
    result.element[0] = {A.element[0].row, B.element[0].col, static_cast<int>(sortedElements.size())};

    for (int i = 0; i < sortedElements.size(); ++i) {
        result.element[i + 1] = sortedElements[i];
    }

    return result;
}

// 희소행렬의 element-wise 나눗셈
CSparseMatrix CSparseMatrix::divideMatrix(const CSparseMatrix& A, const CSparseMatrix& B) {
    std::map<std::pair<int, int>, double> valueMap;

    for (int i = 1; i <= A.element[0].val; ++i) {
        auto key = std::make_pair(A.element[i].row, A.element[i].col);
        valueMap[key] = static_cast<double>(A.element[i].val);
    }

    for (int i = 1; i <= B.element[0].val; ++i) {
        auto key = std::make_pair(B.element[i].row, B.element[i].col);
        if (valueMap.find(key) != valueMap.end()) {
            if (B.element[i].val != 0) {
                valueMap[key] = std::floor((valueMap[key] / B.element[i].val) * 100) / 100; // 버림
            } else {
                valueMap[key] = NAN;
            }
        }
    }

    std::vector<SparseElement> sortedElements;
    for (const auto& entry : valueMap) {
        if (!std::isnan(entry.second)) {
            sortedElements.push_back({entry.first.first, entry.first.second, static_cast<int>(entry.second)});
        }
    }

    std::sort(sortedElements.begin(), sortedElements.end(), compareSparseElement);

    CSparseMatrix result(static_cast<int>(sortedElements.size()) + 1);
    result.element[0] = {A.element[0].row, A.element[0].col, static_cast<int>(sortedElements.size())};

    for (size_t i = 0; i < sortedElements.size(); ++i) {
        result.element[i + 1] = sortedElements[i];
    }

    return result;
}


