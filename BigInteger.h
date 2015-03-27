/*******************************************************
 * COMP2012 - 2012/13 Spring
 * Programming Assignment 3
 * File: BigInteger.h
 *******************************************************/

#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include "BigRational.h"

class BigInteger : public BigRational
{
public:
	BigInteger();							//Default constructor
	BigInteger(int d);						//Convert constructor
	BigInteger(string c);					//Convert constructor
	BigInteger(const BigInteger& a);		//Copy constructor
	~BigInteger();							//Destructor

	BigInteger& operator/=(const BigInteger& a);		//Division assignment operator
	BigInteger& operator%=(const BigInteger& a);		//Modulus assignment operator
	BigInteger& operator++();							//Prefix increment operator
	BigInteger& operator--();							//	Prefix decrement operator
	BigInteger operator++(int dummy);					//	Postfix increment operator
	BigInteger operator--(int dummy);					//	Postfix decrement operator
	BigInteger& operator=(const BigInteger& a);
	BigInteger& operator+=(const BigInteger& a);
	BigInteger& operator-=(const BigInteger& a);
	BigInteger& operator*=(const BigInteger& a);

	virtual void str2bigNumber(const string str);		//	Convert a string to current BigInteger.
	virtual string toString() const;					//	Convert the BigInteger to a string
	virtual void print(ostream &os) const;
	virtual void read(istream &is);						//  Read from the istream,
	BigInteger gcd(const BigInteger& a);				//	greatest common divisor
	BigInteger lcm(const BigInteger& a);				//	least common multiplier

	friend bool operator==(const BigInteger& a, const BigInteger& b);
	friend int compare(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator+(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator-(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator*(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator/(const BigInteger& a, const BigInteger& b);
	friend BigInteger operator%(const BigInteger& a, const BigInteger& b);
	// Helper functions
	friend BNL listDivide(const BNL& a, const BNL& b);
	friend BNL listMod(const BNL& a, const BNL& b);

};

bool operator==(const BigInteger& a, const BigInteger& b);
//Equal to operator: return true if BigInteger a equals to BigInteger b, return false if otherwise.

int compare(const BigInteger& a, const BigInteger& b);
//Compare BigInteger a with BigInteger b. Return +1 if a > b; 0 if a = b; -1 if a < b.

BigInteger operator+(const BigInteger& a, const BigInteger& b);
//Addition operator: Add two BigIntegers to create a third BigInteger.

BigInteger operator-(const BigInteger& a, const BigInteger& b);
//Subtraction operator: Subtract BigInteger b from BigInteger a to create a third BigInteger.

BigInteger operator*(const BigInteger& a, const BigInteger& b);
//Multiplication operator: Multiply two BigIntegers to create a third BigInteger.

BigInteger operator/(const BigInteger& a, const BigInteger& b);
//Division operator: Find the quotient of dividing the BigInteger a by the divisor BigInteger b.

BigInteger operator%(const BigInteger& a, const BigInteger& b);
//Modulus operator: Find the remainder of dividing the BigInteger a by the divisor BigInteger b.

BNL listDivide(const BNL& a, const BNL& b);
BNL listMod(const BNL& a, const BNL& b);

#endif /* BIGINTEGER_H_ */
