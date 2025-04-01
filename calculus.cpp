#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>
using namespace std;

double differentiation(function <double(double )> f, double x, double h) { 
  return (-1.0*f(x-h) + f(x+h)) / (2*h);
}

void derivative(function <double(double )> f, double a, double b, int n, string fname) {
  double dx = (b-a) / n;
  ofstream fout(fname);
  for (double x = (a + dx); x < b; x += dx) {
    fout << x << "," << differentiation(f, x, dx) << endl;
  }
  fout.close();
}

double integration(function <double(double )> f, double a, double b) {
  double h = (b-a) / 2;
  return (h/3) * (f(a) + (4 * f(a+h)) + f(b));
}

double integrate(function <double(double )> f, double a, double b, double n, string fname) {
  double dx = (b-a) / n, Itot = 0;
  ofstream fout(fname);
  for (double x = a; x < b; x += dx) {
    Itot += integration(f, x, x+ dx);
    fout << x << "," << Itot << endl;
  }
  fout.close();
  return Itot;
}

double SQRT2PI = sqrt(2 * 3.14159265358979323846);
double gauss(double x) { return exp((-1 * pow(x, 2)) / 2) / SQRT2PI; }

int main() {
  double a = -6, b = 6;
  int n = 500;
  derivative(gauss, a, b, n, "derivative.csv");
  double intabn = integrate(gauss, a, b, n, "integrate.csv");
  cout << intabn << endl;
}
