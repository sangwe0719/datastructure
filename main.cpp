#include "csparsematrix.h"
#include "matrix.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));

    char answer = 'y';
    while (answer == 'y' || answer == 'Y') {
        int rows, cols;
        cout << "Enter row, col size: ";
        cin >> rows >> cols;

        cout << "Matrix A" << endl;
        Matrix* mat1 = new Matrix(rows, cols);
        mat1->printMatrix();

        cout << "Matrix B" << endl;
        Matrix* mat2 = new Matrix(rows, cols);
        mat2->printMatrix();

        cout << "\nElement-wise Addition" << endl;
        Matrix* added = mat1->addMatrix(*mat1, *mat2);
        added->printMatrix();
        delete added;

        cout << "\nElement-wise Subtraction" << endl;
        Matrix* subtracted = mat1->subtractMatrix(*mat1, *mat2);
        subtracted->printMatrix();
        delete subtracted;

        cout << "\nElement-wise Multiplication" << endl;
        Matrix* multiplied = mat1->multiplyElement(*mat1, *mat2);
        multiplied->printMatrix();
        delete multiplied;

        cout << "\nElement-wise Division" << endl;
        Matrix* divided = mat1->divideElement(*mat1, *mat2);
        divided->printMatrix();
        delete divided;

        cout << "\nTranspose Matrix A" << endl;
        Matrix* transposedA = mat1->transposeMatrix(*mat1);
        transposedA->printMatrix();
        delete transposedA;

        cout << "\nTranspose Matrix B" << endl;
        Matrix* transposedB = mat2->transposeMatrix(*mat2);
        transposedB->printMatrix();
        delete transposedB;

        cout << "\nRandomly Generated Sparse Matrix A" << endl;
        CSparseMatrix sMat1 = CSparseMatrix::generateRandomSparseMatrix(rows, cols);
        sMat1.printSparseMatrix();

        cout << "\nRandomly Generated Sparse Matrix B" << endl;
        CSparseMatrix sMat2 = CSparseMatrix::generateRandomSparseMatrix(rows, cols);
        sMat2.printSparseMatrix();

        CSparseMatrix sparse1 = CSparseMatrix::generateRandomSparseMatrix(rows, cols);
        CSparseMatrix sparse2 = CSparseMatrix::generateRandomSparseMatrix(rows, cols);

        cout << "\nAdd Sparse Matrices" << endl;
        CSparseMatrix addedSparse = CSparseMatrix::sumMatrix(sparse1, sparse2);
        addedSparse.printSparseMatrix();

        cout << "\nMultiply Sparse Matrices" << endl;
        CSparseMatrix multipliedSparse = CSparseMatrix::multMatrix(sparse1, sparse2);
        multipliedSparse.printSparseMatrix();

        cout << "\nTranspose Sparse Matrix A" << endl;
        CSparseMatrix transposedSparseA = CSparseMatrix::transposeMatrix(sparse1);
        transposedSparseA.printSparseMatrix();

        delete mat1;
        delete mat2;

        cout << "\nOther Matrix? (y/n): ";
        cin >> answer;
    }

    return 0;
}
