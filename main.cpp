#include "csparsematrix.h"
#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0));
    vector<int> sizes = {10, 50, 100, 200, 300, 400, 500};

    char answer = 'y';
    while (answer == 'y' || answer == 'Y') {
        int rows, cols;
        cout << "Enter row, col size: ";
        cin >> rows >> cols;

        // 일반행렬 A,B 생성
        cout << "Matrix A" << endl;
        Matrix* mat1 = new Matrix(rows, cols);
        mat1->printMatrix();

        cout << "Matrix B" << endl;
        Matrix* mat2 = new Matrix(rows, cols);
        mat2->printMatrix();

         // Addition
         auto start = high_resolution_clock::now();
         Matrix* added = mat1->addMatrix(*mat1, *mat2);
         auto end = high_resolution_clock::now();
         cout << "\nResult of A + B:\n";
         added->printMatrix();
         auto durationAdd = duration_cast<milliseconds>(end - start).count();
         cout << "Addition Time: " << durationAdd << " ms\n";
         delete added;

         // Subtraction
        start = high_resolution_clock::now();
        Matrix* sub = mat1->subtractMatrix(*mat1, *mat2);
        end = high_resolution_clock::now();
        cout << "\nResult of A - B:\n";
        sub->printMatrix();
        auto durationSub = duration_cast<milliseconds>(end - start).count();
        cout << "Subtraction Time: " << durationSub << " ms\n";
        delete sub;

        // Multiplication 
        start = high_resolution_clock::now();
        Matrix* mul = mat1->multMatrix(*mat1, *mat2);
        end = high_resolution_clock::now();
        cout << "\nResult of A * B:\n";
        mul->printMatrix();
        auto durationMul = duration_cast<milliseconds>(end - start).count();
        cout << "Multiplication Time: " << durationMul << " ms\n";
        delete mul;

        // Division (element-wise)
        start = high_resolution_clock::now();
        Matrix* div = mat1->divideElement(*mat1, *mat2);
        end = high_resolution_clock::now();
        cout << "\nResult of A / B:\n";
        div->printMatrix();
        auto durationDiv = duration_cast<milliseconds>(end - start).count();
        cout << "Element-wise Division Time: " << durationDiv << " ms\n";
        delete div;

        cout << "=========================================" << endl;
        
        // 희소행렬 A,B 생성
        cout << "\nSparse Matrix A" << endl;
        CSparseMatrix sMat1 = CSparseMatrix::generateRandomSparseMatrix(rows, cols);
        sMat1.printSparseMatrix();

        cout << "\nSparse Matrix B" << endl;
        CSparseMatrix sMat2 = CSparseMatrix::generateRandomSparseMatrix(rows, cols);
        sMat2.printSparseMatrix();

        
        // Addition Time
        start = high_resolution_clock::now();
        CSparseMatrix addedSparse = CSparseMatrix::sumMatrix(sMat1, sMat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Sparse A + B" << endl;
        addedSparse.printSparseMatrix();
        cout << "Sp-Addition Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // Subtraction Time
        start = high_resolution_clock::now();
        CSparseMatrix subSparse = CSparseMatrix::subtractMatrix(sMat1, sMat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Sparse A - B:\n";
        subSparse.printSparseMatrix();
        cout << "Sp-Subtraction Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // Multiplecation Time
        start = high_resolution_clock::now();
        CSparseMatrix multipliedSparse = CSparseMatrix::multMatrix(sMat1, sMat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Sparse A * B" << endl;
        multipliedSparse.printSparseMatrix();
        cout << "Sp-Multiplecation Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
        
        // Element-wise Division Time
        start = high_resolution_clock::now();
        CSparseMatrix divSparse = CSparseMatrix::divideMatrix(sMat1, sMat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Sparse A / B:\n";
        divSparse.printSparseMatrix();
        cout << "Sp-Element-wise Division Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        cout << "=========================================" << endl;

        // matrix A,B를 전치한 전치함수 생성
        cout << "\nTranspose Matrix A" << endl;
        Matrix* transposedA = mat1->transposeMatrix(*mat1);
        transposedA->printMatrix();
        delete transposedA;
 
        cout << "\nTranspose Matrix B" << endl;
        Matrix* transposedB = mat2->transposeMatrix(*mat2);
        transposedB->printMatrix();
        delete transposedB;

        //전치행렬 연산 - 덧셈
        start = high_resolution_clock::now();
        Matrix* transAdd = mat1->addTransposed(*mat1, *mat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Transposed A + B:\n";
        transAdd->printMatrix();
        cout << "Transposed Addition Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // 전치행렬 연산 - 뺄셈
        start = high_resolution_clock::now();
        Matrix* transSub = mat1->subtractTransposed(*mat1, *mat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Transposed A - B:\n";
        transSub->printMatrix();
        cout << "Transposed Subtraction Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // 전치행렬 연산 - 곱셈
        start = high_resolution_clock::now();
        Matrix* transMul = mat1->multiplyTransposed(*mat1, *mat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Transposed A * B:\n";
        transMul->printMatrix();
        cout << "Transposed Multiplication Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // 전치행렬 연산 - 나눗셈
        start = high_resolution_clock::now();
        Matrix* transDiv = mat1->divideTransposed(*mat1, *mat2);
        end = high_resolution_clock::now();
        cout << "\nResult of Transposed A / B:\n";
        transDiv->printMatrix();
        cout << "Transposed Element-wise Division Time: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

        // 메모리 정리
        delete transAdd;
        delete transSub;
        delete transMul;
        delete transDiv;
        delete mat1;
        delete mat2;
               
    }

    return 0;
}