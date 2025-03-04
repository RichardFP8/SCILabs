// S T I L L  N E E D S  I M P R O V E M E N T S

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

double pi = 3.1415926536;

double sawtooth(double x, int nmax) {
  double sum = 0;
  for (int n = 1; n <= nmax; n++) {
    sum += pow(-1, n + 1) / (n * sin(n * x));
  }
  return sum * (2 / pi);
}

int main() {
  int nmax, steps = 100;
  float xmin = 0, xmax = 4 * pi;
  double dx = (xmax - xmin) / steps;
  string lab, csvFileName;
  cout << "Enter the maximum number of terms: ";
  cin >> nmax;

  lab = to_string(nmax);
  csvFileName = "sawtooth_" + lab + ".csv";
  ofstream outFile;
  outFile.open(csvFileName);
  for (float x = xmin; x <= xmax; x += dx) {
    outFile << x << "," << sawtooth(x, nmax) << endl;
  }
  outFile.close();
  cout << "Output written to " << csvFileName << endl;

  return 0;
}
