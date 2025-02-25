#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
double pi = 3.1415926536, pi2 = 2 * pi;

struct Coordinates {
  double x, y;
};

void stdmap(double *p, double *t, double K) {
  *p = fmod(*p + K * sin(*t), pi);
  *t = fmod(*t + *p + pi2, pi2);
}

vector<Coordinates>
trajectory(Coordinates pnt0, double K,
           function<void(double *, double *, double)> xymap) {

  int i = 0;
  while (i < 1000) {
    xymap(&(pnt0.x), &(pnt0.y), K);
    i++;
  }

  i = 0;
  int max = 100000;
  double eps = 1.E-4;
  vector<Coordinates> V;
  Coordinates pnt = pnt0;
  V.push_back(pnt);

  while (i < max) {
    xymap(&(pnt.x), &(pnt.y), K);
    V.push_back(pnt);

    if ((abs(pnt.x - pnt0.x) < eps) && (abs(pnt.y - pnt0.y) < eps)) {
      return V;
    }
    i++;
  }
  return V;
}

void writeDataToFile(vector<Coordinates> V, string file) {
  ofstream fout;
  fout.open(file);
  int i = 0;
  while (i < V.size()) {
    fout << V[i].x << ", " << V[i].y << endl;
    i++;
  }
  fout.close();
}

int main() {
  string fileName = "test";
  cout << "Enter output file name: ";
  cin >> fileName;
  int len = fileName.length();
  if (len < 4 || fileName.find(".csv") == string::npos) {
    fileName = fileName + ".csv";
  }
  Coordinates p0 = {0.01, 0.2};
  vector<Coordinates> data = trajectory(p0, 0.6, stdmap);
  cout << "Points: " << data.size() << endl;
  writeDataToFile(data, fileName);
  cout << "Output written to " << fileName << endl;

  return 0;
}
