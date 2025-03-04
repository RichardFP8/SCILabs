// S T I L L  N E E D S  I M P R O V E M E N T S

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

double logistic (double x, double r) { return r * x * (1 - x); }

int main() {
  string fileName = "logistic.csv";
  int tranSteps = 1000, simsSteps = 200, r_points = 400;
  double rmin = 2.5, rmax = 4.0, dr = (rmax - rmin) / (r_points - 1);
  ofstream fout(fileName);
  for (double r = rmin; r <= rmax; r += dr) {
    double x = 0.5;
    for (double step = 0; step < tranSteps; step += 1) {
      x = logistic(x, r);
    }
    for (double step = 0; step < simsSteps; step += 1) {
      x = logistic(x, r);
      fout << r << "," << x << endl;
    }  
  }
  fout.close();
  cout << "Output written to " << fileName << endl;

}
