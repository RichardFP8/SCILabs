#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using Matrix = vector<vector<double>>;
using uli = unsigned long int;

uli m_rows(Matrix M) { return M.size(); }
uli m_cols(Matrix M) { return M.size() != 0 ? M[0].size() : 0; }

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
  uli rows = m_rows(M);
  uli cols = m_cols(M);
  for (uli i = 0; i < rows; i++) {
    // cout << setprecision(2) << fixed;
    for (uli j = 0; j < cols; j++) {
      cout << setw(8) << M[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

vector<double> GEBS(Matrix A) {
  uli N = m_rows(A);
  if (N == 0 || (N + 1) != m_cols(A))
    return {};
  for (int i = 0; i < N - 1; i++) {
    if (A[i][i] == 0) {
      int p; // initialize outside to test in line 70
      for (p = i + 1; p < N; p++) {
        if (A[p][i] != 0) {
          swap(A[p], A[i]);
          break;
        }
      }
      if (p == N) {
        cout << "No unique solution exists" << endl;
        return {};
      }
    } // end of inner if statement
    for (int j = i + 1; j < N; j++) {
      if (A[j][i] != 0) {
        double r = A[j][i] / A[i][i];
        for (int k = i; k <= N; k++) {
          A[j][k] -= (r * A[i][k]);
        }
      }
    }
  } // end of outer for loop
  
  int n = N - 1;
  if (fabs(A[n][n]) < 1E-16) {
    cout << "No unique solution exists" << endl;
    return {};
  }
  vector<double> X(N);
  X[n] = A[n][N] / A[n][n];
  for (int i = N - 2; i >= 0; i--) {
    double sum = 0.0;
    for (uli j = i + 1; j < N; j++) {
      sum += A[i][j] * X[j];
    }
    X[i] = (A[i][N] - sum) / A[i][i];
  }
  return X;
}

int main() {
  Matrix Ab = readMatrix("equations.txt");
  displayMatrix(Ab, "Ab = ");
  vector<double> X = GEBS(Ab);
  // cout << "C  u  t  t  i  n  g" << endl;
  int size = X.size();

  for (int i = 0; i < size; i++) {
    cout << "x_" << to_string(i) << " =" << setw(10) << setprecision(5) << fixed << to_string(X[i]) << endl;
  }
}
