#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using Matrix = vector<vector<double>>;

Matrix readXY2Pro(const string& fileName);
vector<double> linearRegression(Matrix P);

struct Partition {
	double x0 = 0, x1 = 1., dx = 1.;
	int size = 1;

	void set_dx(double xmin, double xmax, int s) {
		x0 = xmin;
		x1 = xmax;
		size = s;
		dx = (xmax - xmin) / (size - 0.01);
	}
	int bin(double x) { return static_cast<int> ((x - x0) / dx); }
	double val(int i) { return x0 + (i + 0.5) * dx; }
};

Partition xpar, ypar;

void setPartition(string fileName, int size) {
	ifstream dataIn(fileName);
	if (!dataIn) {
		cout << "Error: no data file found\n";
		exit(EXIT_FAILURE);
	}
	double xmin = 1E30, ymin = 1E30;
	double xmax = -1E30, ymax = -1E30;
	for (double x, y; dataIn >> x >> y;) {
		if (xmin > x) xmin = x;
		if (ymin > y) ymin = y;
		if (xmax < x) xmax = x;
		if (ymax < y) ymax = y;
	}
	xpar.set_dx(xmin, xmax, size);
	ypar.set_dx(ymin, ymax, size);

}

int main() {
	string fileName = "xydata.txt";
	Matrix P = readXY2Pro(fileName);
	vector<double> A = linearRegression(P);
	cout << "y = " << A[1] << " * x " << A[0] << "\nr2 = " << A[2] << endl;
}

Matrix readXY2Pro(const string& fileName) {
	setPartition(fileName, 100);
	Matrix P(xpar.size, vector<double>(ypar.size, 0));
	ifstream dataIn(fileName);
	if (!dataIn) {
		cout << "Error: no data file found";
		exit(EXIT_FAILURE);
	}
	double tot = 0,  x, y;
	while (dataIn >> x >> y) {
		int i = xpar.bin(x);
		int j = ypar.bin(y);
		if (i < xpar.size && j < ypar.size) {
			P[i][j]++;
			tot++;
		}
	}
	// each row
	for (vector<double> row : P) {
	// each element of row (column)
		for (double col : row) {
			col /= tot;
		}
	}
	return P;
}

double expectation(Matrix P, int n, int m) {
	double e = 0;
	int size = P.size();
	int inner_size = P[0].size();
	for (int i = 0; i < size; i++) {
		double xn = pow(xpar.val(i), n);
		for (int j = 0; j < inner_size; j++) {
			if (P[i][j] == 0) continue;
			double ym = pow(ypar.val(j), m);
			e += xn * ym * P[i][j];
		}
	}
	return e;
}

Matrix getExpectations(Matrix P, int max = 3) {
	Matrix E(max, vector<double>(max, 0));
	for (int n = 0; n < max; n++) {
		int difference = max - n;
		for (int m = 0; m < difference; m++) {
			E[n][m] = expectation(P, n, m);
		}
	}
	return E;
}

vector<double> linearRegression(Matrix P) {
	Matrix E = getExpectations(P);
	double Cxx, Cxy, Cyy, a, b, R2;
	Cxx = E[2][0] - pow(E[1][0], 2);
	Cxy = E[1][1] - E[1][0] * E[0][1];
	Cyy = E[0][2] - pow(E[0][1], 2);
	a = Cxy / Cxx;
	b = E[0][1] - (E[1][0] * a);
	R2 = pow(Cxy, 2) / (Cxx * Cyy);
	return { b, a, R2 };
}
