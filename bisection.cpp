// FAILED ATTEMPT AT USING TEH BISECTION METHOD

// #include <cstdio>
#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

void printpars(int i, double a, double b, double p, double fp) {
  if (i == 1) printf("%-6s %-10s %-10s %-10s %-10s\n", "i", "a", "b", "p", "fp");
  printf("%-3d %-10.5f %-10.5f %-10.5f %-10.5f\n", i, a, b , p, fp);
}

double bisection(function <double(double para)> f, double a, double b, double eps, int N) {
  int x, y;
  x = f(a); y = f(b);
  if ((x * y) > 0) {
    cout << "Bisection Error: invalid endpoints.\n";
    return 1;
  }
  for (int i = 0; i < N; i++) {
    double p = (a + b) / 2, fp = f(p), check = (b - a) / 2;
    printpars(i, a, b, p, fp);
    if (check < eps || abs(fp) < eps) return p;
    ((x * fp) > 0) ? a = p: b = p;
  }
  cout << "Method failed to converge after " << N << " iterations\n";
  return 1;
}

double fun(double x) { return (5 * pow(x, 2)) - (1.75 * x) - 10; }

int main() {
  double a, b, eps = 1E-5, p;
  int N = 100;
  
  cout << "Enter endpoints a and b surrounding the solution: ";
  cin >> a >> b;
  if (a > b) cout << "Error: invalid endpoints\n"; return 1;
  p = bisection(fun, a, b, eps, N);
  cout << "A zero was found at p = " << p << endl;
  return 0;
}
