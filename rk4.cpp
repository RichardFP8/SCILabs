#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

vector<double> get_yt(vector<double> y, vector<double> dydx, double hh) {
  int N = y.size();
  for (int i = 0; i < N; i += 1) y[i] += hh * dydx[i];
  return y;
}

vector<double> rk4(function<vector<double>(vector<double>, double)> derivs,
                   vector<double> y, double x, double h) {
  double h6 = h / 6, hh = h / 2, xh = x + hh;
  vector<double> yt = y;

  vector<double> D1 = derivs(yt, x);
  yt = get_yt(y, D1, hh);

  vector<double> D2 = derivs(yt, xh);
  yt = get_yt(y, D2, hh);

  vector<double> D3 = derivs(yt, xh);
  yt = get_yt(y, D3, h);

  vector<double> D4 = derivs(yt, x + h);

  int size = y.size();
  for (int i = 0; i < size; i++) {
    y[i] += (h6 * (D1[i] + 2 * (D2[i] + D3[i]) + D4[i]));
  }
  return y;
}

const double sigma = 10, beta = 8 / 3, rho = 28;
vector<double> lorentzD(vector<double> y, double x) {
  double dy0 = sigma * (y[1] - y[0]);
  double dy1 = y[0] * (rho - y[2]) - y[1];
  double dy2 = (y[0] * y[1]) - (beta * y[2]);
  return {dy0, dy1, dy2};
}

int main() {
  double t = 0;
  int outStep = 10;
  double time = 100.;
  double dt = 1.E-3;
  int totalSteps = time / dt;
  cout << "Steps = " << totalSteps << endl;
  vector<double> y(3, 1.0);
  ofstream fout("trajectory.csv");
  fout << t << ","
       << "1.0"
       << ","
       << "1.0"
       << ","
       << "1.0" << endl;
  for (int step = 1; step <= totalSteps; step++) {
    y = rk4(lorentzD, y, t, dt);
    t += dt;
    if (step % outStep == 0)
      fout << t << "," << y[0] << "," << y[1] << "," << y[2] << endl;
  }
  fout.close();
}
