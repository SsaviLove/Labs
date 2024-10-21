#include <iostream>

#include "Fraction.h"

void Swap(int* first, int* second)
{
	int ptr = *first;
	*first = *second;
	*second = ptr;
}

int Fraction::numerator() const
{
	return m_numerator;
}

int Fraction::denominator() const
{
	return m_denominator;
}

void Fraction::setNumerator(int numerator)
{
	m_numerator = numerator;
}

void Fraction::setDenominator(int denominator)
{
	if (denominator != 0)
		m_denominator = denominator;
	else
	{
		m_numerator = 0;
		m_denominator = 1;
	}
}

void Fraction::input()
{
	std::cout << "Enter numerator: ";
	std::cin >> m_numerator;
	std::cout << "Enter denominator: ";
	std::cin >> m_denominator;
	if (m_denominator == 0)
	{
		std::cout << "Denominator cannot be == 0 -> " << m_numerator << "/" << m_denominator << " = 0/1" << std::endl;
		m_numerator = 0;
		m_denominator = 1;
	}
}

void Fraction::output()
{
	std::cout << m_numerator << "/" << m_denominator << std::endl;
}

Fraction Fraction::operator+(Fraction const b) const
{
	Fraction c;
	c.setNumerator(m_numerator * b.m_denominator + m_denominator * b.m_numerator);
	c.setDenominator(m_denominator * b.m_denominator);
	return c;
}

Fraction Fraction::operator-(Fraction const b) const
{
	Fraction c;
	c.setNumerator(m_numerator * b.m_denominator - m_denominator * b.m_numerator);
	c.setDenominator(m_denominator * b.m_denominator);
	return c;
}

Fraction Fraction::operator*(Fraction const b) const
{
	Fraction c;
	c.setNumerator(m_numerator * b.m_numerator);
	c.setDenominator(m_denominator * b.m_denominator);
	return c;
}

Fraction Fraction::operator/(Fraction const b) const
{
	Fraction c;
	c.setNumerator(m_numerator * b.m_denominator);
	c.setDenominator(m_denominator * b.m_numerator);
	return c;
}

bool Fraction::operator>(Fraction const b) const
{
	return (m_numerator * b.m_denominator > b.m_numerator * m_denominator);
}

bool Fraction::operator<(Fraction const b) const
{
	return (m_numerator * b.m_denominator < b.m_numerator * m_denominator);
}

bool Fraction::operator==(Fraction const b) const
{
	return (m_numerator * b.m_denominator == b.m_numerator * m_denominator);
}

bool Fraction::operator!=(Fraction const b) const
{
	return (m_numerator * b.m_denominator != b.m_numerator * m_denominator);
}

Fraction Fraction::operator^(int n)
{
	Fraction b;
	if (n < 0)
	{
		Swap(&m_numerator, &m_denominator);
		n = -n;
	}
	for (int i = 0; i < n; i++)
	{
		b.setNumerator(b.m_numerator * m_numerator);
		b.setDenominator(b.m_denominator * m_denominator);
	}
	return b;
}

int Fraction::factorial(int n) const
{
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}

Fraction Fraction::factorial() const
{
	int n_factorial = factorial(m_numerator);
	int d_factorial = factorial(m_denominator);
	return Fraction(n_factorial, d_factorial);
}

void Fraction::slash()
{
	int LCD = 0;
	while (LCD != 1)
	{
		LCD = 1;
		for (int i = 2; i <= std::min(abs(m_numerator), abs(m_denominator)); ++i)
			if (m_numerator % i == 0 && m_denominator % i == 0)
				LCD = i;
		m_numerator /= LCD;
		m_denominator /= LCD;
	}
	if (m_denominator < 0)
	{
		m_numerator *= -1;
		m_denominator *= -1;
	}
}

Fraction::Fraction(int numerator, int denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	else
	{
		m_numerator = numerator;
		m_denominator = denominator;

	}
}

Fraction::Fraction()
{
}