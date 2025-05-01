#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include "vector2D.hpp"
using namespace std;
vector<Vector2D> kaleidoscopeCurve(int, int);
random_device rd;
mt19937 gen(rd());

int main() {
  int symmetry, numOfPoints;
  string fileName = "kaleidoscope.csv";
  cout << "Symmetry: ";
  cin >> symmetry;
  cout << "Basis Points: ";
  cin >> numOfPoints;
  vector<Vector2D> curve = kaleidoscopeCurve(symmetry, numOfPoints);
  saveVectorToFile(curve, fileName);
  cout << "Output written to " << fileName << endl;
}

Vector2D getNextPoint(const Vector2D& pt, float phase, int n) {
  double angle = 0.;
  if (n > 0) angle = n * phase;
  else if (n < 0) angle = (n + 1) * phase - 2 * pt.angle();
  return pt.rotateAround(angle);
}

double rnum(double a = 1, double b = 0) {
  if (b > a) swap(a, b);
  uniform_real_distribution<double> distribute(a, b);
  return distribute(gen);
}

vector<Vector2D> kaleidoscopeCurve(int symmetry, int numOfPoints) {
  double phase = 360. / (2 * symmetry);
  vector<Vector2D> basis (numOfPoints);
  for (int i = 0; i < numOfPoints; i++) {
    double rad = rnum();
    double ang = rnum(0, phase);
    basis[i].setFromPolar(rad, ang);
  }
  vector<Vector2D> curve;
  for (int step = 0; step <= 2 * symmetry; step++) {
    if (step % 2 != 0) {
      for (int p = numOfPoints - 1; p >= 0; p--) {
        curve.push_back(getNextPoint(basis[p], phase, step));
      }
    }
    else {
      for (int p = 0; p < numOfPoints; p++) {
        curve.push_back(getNextPoint(basis[p], phase, step));
      }
    }
  }
  return curve;
}
