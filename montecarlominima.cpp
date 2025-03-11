// INCOMPLETE

#include <iostream>
#include <random>
#include <functional>
#include <fstream>
using namespace std;

double mc_minima(function<double(double temp)> f, double x, double T0, long long int simSteps) {
  random_device rg;
  uniform_real_distribution<double> randDx(-1, 1);
  uniform_real_distribution<double> randOne(0, 1);
  double fx = f(x), xmin = x, fmin = fx, T = T0;
  ofstream outf("covergence.csv");
  
  for(long long int steps = 0; steps < simSteps; steps++) {
    double dx = randDx(rg), fxdx = f(x + dx), df = fxdx - fx, expConstant = exp((-df) / T);
    if (df <= 0 || randOne(rg) < expConstant) {
      x += dx; fx = fxdx;
      if (fx < fmin) { xmin = x; fmin = fx;}
      outf << steps << ", " << x << endl;
    }
    T = T0 * (1 - ( pow(int(steps/ simSteps), 2) ));
  }
  outf.close();
  return xmin;
}

double func(double x) { return 480 - (232 * x) - (28 * pow(x, 2)) + (10 * pow(x, 3)) + pow(x,4); }


int main(){
  double xi, T = 500, xmin;
  long long int maxStep = 5E4;
  cout << "Starting x value: ";
  cin >> xi;
  
  xmin = mc_minima(func, xi, T, maxStep);
  cout << "Minima at x = " << xmin << endl;
  cout << "Minima value f(x) = " << func(xmin) << endl;
  
}
