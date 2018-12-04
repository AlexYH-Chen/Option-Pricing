// test_european_option.cpp
//
// Test program for the exact solutions of Plain European options. 
//
// Since european option is a kind of option, I built a base class Option and 
// a derived class EuropeanOption. Since all options need parameters, I put
// the parameters T, K, sig, r, b, t, q in Option and create all the 
// getters and setters for each param in Option. I think it's more convenient
// to pass data to a function and to encapsulate the data to other objects by
// using OptionData. It's also more flexible and easier to add or change the
// member in the OptionData without having to rewrite the whole function.
// So I used Optiondata as my member data type. Moreover, I built plain european
// option pricing functions in EuropeanOption, overloading each function for
// different arguments. I also created similar global version pricing function.  
//

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include "option_data.hpp"
#include "european_option.hpp"
#include "option_function.hpp"

using namespace std;

/* Cost of carry factor b must be included in formulae depending on the
derivative type. These are used in the generalised Black-Scholes formula.
If r is the risk-free interest and q is the continuous dividend yield then
the cost-of-carry b per derivative type is:

a) Black-Scholes (1973) stock option model: b = r
b) b = r - q Merton (1973) stock option model with continuous dividend yield
c) b = 0 Black (1976) futures option model
d) b = r - rf Garman and Kohlhagen (1983) currency option model, where rf is the
'foreign' interest rate */

int main(void) {
	/*
	All options are European non-stock dividend paying option.
	Batch 1 : T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628).
	Batch 2 : T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557).
	Batch 3 : T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326).
	Batch 4 : T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).
	*/

	// Test Pricing function.
	// Batch1.
	OptionData OptData = { 0.25, 65.0, 0.30, 0.08, 0.08 };
	EuropeanOption Batch1(OptData, "C");
	cout << "Batch1" << endl;
	cout << "C = " << Batch1.Price(60.0) << endl;
	Batch1.toggle();
	cout << "P = " << Batch1.Price(60.0) << endl;
	cout << string(75, '-') << endl;

	// Batch2.
	OptData = { 1.0, 100.0, 0.2, 0.0, 0.0 };
	EuropeanOption Batch2(OptData, "C");
	cout << "Batch2" << endl;
	cout << "C = " << Batch2.Price(100.0) << endl;
	Batch2.toggle();
	cout << "P = " << Batch2.Price(100.0) << endl;
	cout << string(75, '-') << endl;

	// Batch3.
	OptData = { 1.0, 10.0, 0.50, 0.12, 0.12 };
	EuropeanOption Batch3(OptData, "C");
	cout << "Batch3" << endl;
	cout << "C = " << Batch3.Price(5.0) << endl;
	Batch3.toggle();
	cout << "P = " << Batch3.Price(5.0) << endl;
	cout << string(75, '-') << endl;

	// Batch4.
	OptData = { 30.0, 100.0, 0.30, 0.08, 0.08 };
	EuropeanOption Batch4(OptData, "C");
	cout << "Batch4" << endl;
	cout << "C = " << Batch4.Price(100.0) << endl;
	Batch4.toggle();
	cout << "P = " << Batch4.Price(100.0) << endl;
	cout << string(75, '-') << endl;

	// Put-call parity.
	cout << "*** Put-call parity ***\n\n";
	cout << "Batch1" << endl;
	cout << "P = " << Batch1.Price(60.0) << " to C = " << Batch1.PutCallParity(60.0) << endl;		// Batch1.
	Batch1.toggle();
	cout << "C = " << Batch1.Price(60.0) << " to P = " << Batch1.PutCallParity(60.0) << endl;
	if (Batch1.IsParity(60.0, 5.84628)) 
		cout << "Batch1 Put-call parity holds" << endl;
	else 
		cout << "Batch1 Put-call parity does not hold" << endl;
	cout << string(75, '-') << endl;

	cout << "Batch2" << endl;
	cout << "P = " << Batch2.Price(100.0) << " to C = " << Batch2.PutCallParity(100.0) << endl;	// Batch2.
	Batch2.toggle();
	cout << "C = " << Batch2.Price(100.0) << " to P = " << Batch2.PutCallParity(100.0) << endl;
	if (Batch2.IsParity(100.0, 7.96557))
		cout << "Batch2 Put-call parity holds" << endl;
	else
		cout << "Batch2 Put-call parity does not hold" << endl;
	cout << string(75, '-') << endl;

	cout << "Batch3" << endl;
	cout << "P = " << Batch3.Price(5.0) << " to C = " << Batch3.PutCallParity(5.0) << endl;			// Batch3.
	Batch3.toggle();
	cout << "C = " << Batch3.Price(5.0) << " to P = " << Batch3.PutCallParity(5.0) << endl;
	if (Batch3.IsParity(5.0, 4.07326))
		cout << "Batch3 Put-call parity holds" << endl;
	else
		cout << "Batch3 Put-call parity does not hold" << endl;
	cout << string(75, '-') << endl;

	cout << "Batch4" << endl;
	cout << "P = " << Batch4.Price(100.0) << " to C = " << Batch4.PutCallParity(100.0) << endl;	// Batch4.
	Batch4.toggle();
	cout << "C = " << Batch4.Price(100.0) << " to P = " << Batch4.PutCallParity(100.0) << endl;
	if (Batch4.IsParity(100.0, 1.24750))
		cout << "Batch4 Put-call parity holds" << endl;
	else
		cout << "Batch4 Put-call parity does not hold" << endl;
	cout << string(75, '-') << endl;

	// Test vector pricing function.
	// Compute option prices for a monotonically increasing range of underlying values of S.
	cout << "Batch1 Call" << endl;
	cout << "T = 0.25, K = 65, sig = 0.30, r = 0.08, b = 0.08" << endl;
	cout << "Range of S: [60, 100], interval: 5.0\n" << endl;
	OptionFunction::PrintVector(Batch1.Price(OptionFunction::MeshArray(60.0, 100.0, 5.0)));	 // Using spot price MeshArray.
	OptionFunction::PrintVector(Batch1.Price(60.0, 100.0, 5.0));	// Using mesh range and size.
	cout << string(75, '-') << endl;

	// Compute option prices for a monotonically increasing range of underlying values of T.
	cout << "Batch1 Call" << endl;
	cout << "K = 65, sig = 0.30, r = 0.08, b = 0.08, S = 60.0" << endl;
	cout << "Range of T: [0.25, 0.5], interval: 0.05\n" << endl;
	OptionFunction::PrintVector(Batch1.Price(0.25, 0.7, 0.05, "T", 60.0));
	cout << string(75, '-') << endl;

	// Compute option prices for a monotonically increasing range of underlying values of sig.
	cout << "Batch1 Call" << endl;
	cout << "T = 0.25, K = 65, r = 0.08, b = 0.08, S = 60.0" << endl;
	cout << "Range of sig: [0.30, 1], interval: 0.1\n" << endl;
	OptionFunction::PrintVector(Batch1.Price(0.30, 1, 0.1, "sig", 60.0));
	cout << string(75, '-') << endl;

	// Test sensitivities function.
	EuropeanOption myOption1(0.5, 100, 0.36, 0.1, 0.0, 0.0, 0.0, "C");
	cout << "Call Option" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0, S = 105\n" << endl;
	cout << "Delta: " << myOption1.Delta(105.0) << endl;
	cout << "Gamma: " << myOption1.Gamma(105.0) << endl;
	cout << "Delta approximation: " << myOption1.Delta(105.0, 0.10) << endl;
	cout << "Gamma approximation: " << myOption1.Gamma(105.0, 0.10) << endl;
	cout << string(75, '-') << endl;

	EuropeanOption myOption2(0.5, 100, 0.36, 0.1, 0.0, 0.0, 0.0, "P");
	cout << "Put Option" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0, S = 105\n" << endl;
	cout << "Delta: " << myOption2.Delta(105.0) << endl;
	cout << "Gamma: " << myOption2.Gamma(105.0) << endl;
	cout << "Delta approximation: " << myOption2.Delta(105.0, 0.10) << endl;
	cout << "Gamma approximation: " << myOption2.Gamma(105.0, 0.10) << endl;
	cout << string(75, '-') << endl;

	// Test sensitivities with changing spot price
	cout << "Call Option Delta" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of S: [50, 150], interval: 1.0\n" << endl;
	OptionFunction::PrintVector(myOption1.Delta(50.0, 150.0, 5.0));
	cout << string(75, '-') << endl;

	cout << "Call Option Gamma" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of S: [50, 150], interval: 1.0\n" << endl;
	OptionFunction::PrintVector(myOption1.Gamma(50.0, 150.0, 5.0));
	cout << string(75, '-') << endl;

	cout << "Put Option Delta" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of S: [50, 150], interval: 1.0\n" << endl;
	OptionFunction::PrintVector(myOption2.Delta(50.0, 150.0, 5.0));
	cout << string(75, '-') << endl;

	cout << "Put Option Gamma" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of S: [50, 150], interval: 1.0\n" << endl;
	OptionFunction::PrintVector(myOption2.Gamma(50.0, 150.0, 5.0));
	cout << string(75, '-') << endl;

	// Test sensitivities approximation
	cout << "Call Option Delta approximation" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of h: [0.05, 0.5], interval: 0.05\n" << endl;
	for (double h = 0.05; h <= 0.5; h+= 0.05) {
		cout << myOption1.Delta(105.0, h) << "  ";
	}
	cout << "\n" << string(75, '-') << endl;

	cout << "Call Option Gamma approximation" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of h: [0.05, 0.5], interval: 0.05\n" << endl;
	for (double h = 0.05; h <= 0.5; h += 0.05) {
		cout << myOption1.Gamma(105.0, h) << "  ";
	}
	cout << "\n" << string(75, '-') << endl;

	cout << "Put Option Delta approximation" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of h: [0.05, 0.5], interval: 0.05\n" << endl;
	for (double h = 0.05; h <= 0.5; h += 0.05) {
		cout << myOption2.Delta(105.0, h) << "  ";
	}
	cout << "\n" << string(75, '-') << endl;
	
	cout << "Put Option Gamma approximation" << endl;
	cout << "T = 0.5, K = 100, sig = 0.36, r = 0.1, b = 0" << endl;
	cout << "Range of h: [0.05, 0.5], interval: 0.05\n" << endl;
	for (double h = 0.05; h <= 0.5; h += 0.05) {
		cout << myOption2.Gamma(105.0, h) << "  ";
	}
	cout << "\n" << string(75, '-') << endl;

	return 0;
}
