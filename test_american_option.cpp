// test_american_option.cpp
//
// Perpetual American option
//

#include <cmath>
#include <iostream>
#include "american_option.hpp"
#include "american_option_function.hpp"
#include "option_data.hpp"
#include "option_function.hpp"

using namespace std;
using namespace OptionFunction;

int main(void) {
	// Test AmericanOption Class.
	AmericanOption myOption1(100.0, 0.1, 0.1, 0.02, 0.0, 0.0, "C");
	cout << "Option" << endl;
	cout << "C = " << myOption1.Price(110.0) << endl;
	myOption1.toggle();
	cout << "P = " << myOption1.Price(110.0) << endl;
	myOption1.toggle();
	cout << string(75, '-') << endl;

	// Test vector pricing function.
	// Compute option prices for a monotonically increasing range of underlying values of S.
	cout << "Call option" << endl;
	cout << "Range of S: [90, 130], interval: 1.0\n" << endl;
	PrintVector(myOption1.Price(90.0, 130.0, 1.0));	 // Using mesh range and size.
	cout << string(75, '-') << endl;

	myOption1.toggle();
	cout << "Put option" << endl;
	cout << "Range of S: [90, 130], interval: 1.0\n" << endl;
	PrintVector(myOption1.Price(90.0, 130.0, 1.0));	 // Using mesh range and size.
	cout << string(75, '-') << endl;

	// Test global function.
	double K, S, sig, r, b;
	cout << "K: "; cin >> K;
	cout << "S: "; cin >> S;
	cout << "sig: "; cin >> sig;
	cout << "r: "; cin >> r;
	cout << "b: "; cin >> b;
	cout << "Price, call: " << AmericanOptionFunction::CallPrice(K, sig, r, b, S) << endl;
	cout << "Price, put: " << AmericanOptionFunction::PutPrice(K, sig, r, b, S) << endl;
	cout << string(75, '-') << endl;

	return 0;
}
