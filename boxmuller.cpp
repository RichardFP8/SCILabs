#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
using namespace std;

struct Partition {
  double x0, dx;
  int size;
  int bin(double x) { return static_cast<int>((x - x0) / dx); }
  double val(int xi) { return x0 + (xi + 0.5) * dx; }
};
vector<double> rnGenerator(int, double, double, Partition&);
vector<double> getProbability(int, vector<double>, Partition);

int main() {
  int totalSteps = 20000;
  double mu = 0, sigma = 1;
  Partition xpar;
  xpar.size = 100;
  vector<double> x = rnGenerator(totalSteps, mu, sigma, xpar);
  vector<double> probability = getProbability(totalSteps, x, xpar);
  string outFileName = "probability.csv";
  ofstream fileOut(outFileName);
  for (int bin = 0; bin < xpar.size; bin++) {
    fileOut << fixed << setprecision(6) << xpar.val(bin) << "," << probability[bin] << endl;
  }
  fileOut.close();
  cout << "Output written to " << outFileName;
  
}

double gaussianNoise(double mu, double sigma) {
  static bool iset = true;
  static double z1 = 0;
  iset = !iset;
  if (iset == false) {
    double v1, v2, r;
    do {
      v1 = 2.0 * (static_cast<double> (rand()) / RAND_MAX) - 1.0;
      v2 = 2.0 * (static_cast<double> (rand()) / RAND_MAX) - 1.0;

      r = pow(v1, 2) + pow(v2, 2);
    } while (r >= 1 || r == 0);
    double fac = sqrt((-2 * log(r)) / r);
    z1 = v1 * fac;
    return v2 * fac * sigma + mu;
  }
  return z1 * sigma + mu;
}

vector<double> rnGenerator(int totalSteps, double mu, double sigma, Partition& xpar) {
  double xmin = 1E32, xmax = -xmin;
  vector<double> x (totalSteps);
  for (int step = 0; step < totalSteps; step++) {
    x[step] = gaussianNoise(mu, sigma);
    if (xmin > x[step]) xmin = x[step];
    if (xmax < x[step]) xmax = x[step];
  }
  xpar.x0 = xmin;
  xpar.dx = (xmax - xmin) / (xpar.size - 0.01);
  return x;
}

vector<double> getProbability(int totalSteps, vector<double> x, Partition xpar) {
  vector<double> probability (xpar.size, 0);
  for (int step = 0; step < totalSteps; step++) {
    int i = xpar.bin(x[step]);
    probability[i] += 1;
  }
  for (int i = 0; i < xpar.size; i++) {
    probability[i] /= totalSteps;
  }
  return probability;
}
