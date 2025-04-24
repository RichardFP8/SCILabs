#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Partition {
  double x0, dx;
  int size;
  int bin(double x) { return static_cast<int>((x - x0) / dx); }
  double val(int xi) { return x0 + (xi + 0.5) * dx; }
};
vector<double> rnGenerator(int, double, double, Partition) s;
vector<double> getProbability(int, vector<double>, Partition);

int main() {
  int totalSteps = 2E4;
  double mu = 0, sigma = 1;
  Partition xpar;
  xpar.size = 100;
  vector<double> x = rnGenerator(totalSteps, mu, sigma, xpar);
  vector<double> probability = getProbability(totalSteps, x, xpar);
  string outFileName = "probability.csv";
  ofstream fileOut(outFileName);
  for (double bin : probability) {
    fileOut << xpar.val(bin) << "," << bin << endl;
  }
  cout << "Output written to " << outFileName;
}

double gaussianNoise(double mu, double sigma) {
  static bool iset = true;
  double z1;
}
