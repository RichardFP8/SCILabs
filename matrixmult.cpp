#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
using Matrix = vector<vector<double>>;

unsigned long int m_rows(Matrix M) { return M.size(); }
unsigned long int m_cols(Matrix M) { return M.size() != 0 ? M[0].size() : 0; }

Matrix buildMatrix(unsigned long rows, unsigned long cols, double val) {
  return Matrix(rows, vector<double>(cols, val));
}
Matrix readMatrix(string fileName) {
  Matrix M;
  ifstream finp(fileName);

  if (finp.is_open()) {
    int rows, cols;
    finp >> rows >> cols;
    M = buildMatrix(rows, cols, 0);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        double digit;
        if (!(finp >> digit))
          M[i][j] = {};
        else {
          M[i][j] = digit;
        }
      }
    }
  } else {
    cout << fileName << " was not found" << endl;
  }
  return M;
}

void displayMatrix(Matrix M, string label) {
  cout << label << endl;
  unsigned long int rows = m_rows(M);
  unsigned long int cols = m_cols(M);
  for (unsigned long int i = 0; i < rows; i++) {
    cout << setprecision(2) << fixed;
    for (unsigned long int j = 0; j < cols; j++) {
      cout <<  setw(8) << M[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

Matrix multiplyMatrices(Matrix A, Matrix B) {
  unsigned long int n = m_cols(A);
  if (n != m_rows(B)) return {};
  unsigned long int rows = m_rows(A);
  unsigned long int cols = m_cols(B);
  Matrix C = buildMatrix(rows,cols, 0);
  for (unsigned long int i = 0; i < rows; i++) {
    for (unsigned long int j = 0; j < cols; j++) {
      double sum = 0;
      for (unsigned long int k = 0; k < n; k++) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }
  return C;
}

int main() {
  Matrix A = readMatrix("A.txt");
  displayMatrix(A, "A = ");
  Matrix B = readMatrix("B.txt");
  displayMatrix(B, "B = ");
 Matrix C = multiplyMatrices(A, B);
  displayMatrix(C, "C = ");
}
