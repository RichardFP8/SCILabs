#include <iostream>
#include <numeric>
#include <string>
using namespace std;

class Rational {
private:
	int num, den;
	Rational normal();
	Rational reduce();
public:
	Rational(int n = 0, int d = 1) : num(n), den(d) {
		normal();
	}
	const int get_num() { return num; }
	const int get_den() { return den; }
	void set(int n, int d = 1) {
		num = n; den = d;
		normal();
	}
	const Rational neg() { return Rational(-num, den).normal(); }
	const Rational reciprocal() { return Rational(den, num).normal(); }
	const Rational plus(const Rational& rhs) {
		int sum_num = (this->num * rhs.den) + (rhs.num * this->den);
		int denom = (this->den * rhs.den);
		return Rational (sum_num, denom).reduce();
	}
	const Rational minus(const Rational& rhs) {
		int diff_num = (this->num * rhs.den) - (this->den * rhs.num);
		int denom = (this->den * rhs.den);
		return Rational (diff_num, denom).reduce();
	}
	const Rational times(const Rational& rhs) {
		return Rational((this->num*rhs.num), (this->den * rhs.den)).reduce();
	}
	const Rational dividedBy(const Rational& rhs) {
		return Rational(this->num * rhs.den, this->den * rhs.num).reduce();
	}
	const Rational abs() {
		return this->num > 0 ? *this : neg();
	}
	const bool equal(const Rational&  rhs) {
		return this->num * rhs.den == this->den * rhs.num;
	}
	const bool lessThan(const Rational& rhs) {
		return this->num * rhs.den < this->den * rhs.num;
	}
	void readRational();
	const string to_str(bool = false);
	const double decimal() {
		return static_cast<double>(this->num) / static_cast<double>(this->den);
	}
};

Rational Rational::normal(){
	if (this->den < 0) {
		this->num *= -1;
		this->den *= -1;
	}
	return *this;
}
Rational Rational::reduce() {
	int div = gcd(this->num, this->den);
	if (div != 0 && div != 1) {
		this->num /= div;
		this->den /= div;
	}
	return *this;
}
void Rational::readRational() {
	cout << "Enter ratio: numerator followed by denominator\n";
	cin >> this->num >> this->den;
	normal();
}
const string Rational::to_str(bool both){
	string ans = "(" + to_string(this->num);
	if (both || den != 1) ans += "/" + to_string(this->den);
	ans += ")";
	return ans;
}
int main() {
	Rational n1;
	n1.readRational();
	Rational n2;
	n2.readRational();
	Rational n3;

	Rational diff = (n1.minus(n2));					    // n1 - n2
	Rational absolute = diff.abs();					// |n1 -n2|
	Rational sum = n1.plus(n2);						  // n1 + n2
	Rational dividedBy2 = sum.dividedBy(Rational(2)); // (n1+n2)/2
	Rational quotient = absolute.dividedBy(dividedBy2);   // |n1 -n2| / [(n1+n2)/2]
	n3 = quotient.times(Rational (100));			  // * 100

	cout << "x = " << n1.to_str() << endl;
	cout << "y = " << n2.to_str() << endl;
	cout << "|x-y| / [ (x+y)/2 ] *100% = " << n3.to_str();
	if (!(n1.equal(n2.neg()))) {
		if (n3.lessThan(Rational(1, 2))) cout << " = 0%" << endl;
		else cout << " = " << n3.decimal() << "%" << endl;
	}
	else {
		cout << " = undefined" << endl;
	}
}
