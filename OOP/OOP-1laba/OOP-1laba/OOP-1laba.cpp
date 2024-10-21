#include <iostream>

#include "Fraction.h"

int main()
{
	Fraction a, b, sum, difference, product, quotient, deg, bFactorial;
	int degree;
	a.input();
	a.output();
	b.input();
	b.output();

	sum = a + b;
	sum.slash();
	std::cout << "A + B = ";
	sum.output();

	difference = a - b;
	difference.slash();
	std::cout << "A - B = ";
	difference.output();

	product = a * b;
	product.slash();
	std::cout << "A * B = ";
	product.output();

	quotient = a / b;
	quotient.slash();
	std::cout << "A / B = ";
	quotient.output();

	if (a > b)
		std::cout << "A > B" << std::endl;

	if (a < b)
		std::cout << "A < B" << std::endl;

	if (a == b)
		std::cout << "A == B" << std::endl;

	if (a != b)
		std::cout << "A != B" << std::endl;

	std::cout << "Enter degree a: ";
	std::cin >> degree;
	deg = a ^ degree;
	std::cout << "a ^ " << degree << " = ";
	deg.output();

	bFactorial = b.factorial();
	bFactorial.output();

	return 0;
}