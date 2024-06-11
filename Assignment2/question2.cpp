#include <iostream>

class Matrix {
private:
    int rows, cols;
    double** data;

public:
    // Constructor to initialize matrix with given rows and columns
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
        }
    }

    // Destructor to free allocated memory
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Function to input matrix elements
    void input() {
        std::cout << "Enter elements for a " << rows << "x" << cols << " matrix:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }

    // Function to print matrix elements
    void print() const {
        std::cout << "Matrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    // Operator overloading for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            std::cerr << "Matrix dimensions do not match for multiplication.\n";
            exit(1);
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
};

int main() {
    int m, n;
    std::cout << "Enter the number of rows for the first matrix: ";
    std::cin >> m;
    std::cout << "Enter the number of columns for the first matrix (and rows for the second matrix): ";
    std::cin >> n;

    Matrix matA(m, n), matB(n, m), matC(m, m);

    std::cout << "Enter elements for Matrix A:\n";
    matA.input();
    std::cout << "Enter elements for Matrix B:\n";
    matB.input();

    matC = matA * matB;

    std::cout << "Matrix A:\n";
    matA.print();
    std::cout << "Matrix B:\n";
    matB.print();
    std::cout << "Matrix C (A * B):\n";
    matC.print();

    return 0;
}
