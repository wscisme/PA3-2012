/*******************************************************
 * COMP2012 - 2012/13 Spring
 * Programming Assignment 3
 * File: BigRational.h
 *******************************************************/

#ifndef BIGRATIONAL_H_
#define BIGRATIONAL_H_

#include "BigNumber.h"

#define USI unsigned short int
#define BNL list<unsigned short int>	// Stands for Big Number List
#define Nmr digitLists[0]				// Stands for Numerator
#define Dno digitLists[1]				// Stands for Denominator

class BigRational : public BigNumber
{
public:
	BigRational();
	BigRational(int n);
	BigRational(string c);
	BigRational(const BigRational& a);
	~BigRational();
	BigRational& operator=(const BigRational& a);
	BigRational& operator+=(const BigRational& a);
	BigRational& operator-=(const BigRational& a);
	BigRational& operator*=(const BigRational& a);
	BigRational& operator/=(const BigRational& a);
	virtual bool isZero() const;
	virtual void str2bigNumber(const string str);
	virtual string toString() const;
	virtual void print(ostream &os) const;
	virtual void read(istream &is);
	void simplify();
	list<unsigned short int> getNumerator() const;
	list<unsigned short int> getDenominator() const;


	friend bool operator==(const BigRational& a, const BigRational& b);
	friend int compare(const BigRational& a, const BigRational& b);
	friend BigRational operator+(const BigRational& a, const BigRational& b);
	friend BigRational operator-(const BigRational& a, const BigRational& b);
	friend BigRational operator*(const BigRational& a, const BigRational& b);
	friend BigRational operator/(const BigRational& a, const BigRational& b);
	// Helper functions
	friend list<USI> listMultiply(const list<USI>& a, const list<USI>& b);
	friend void listAddTo(list<USI>& a, const list<USI>& b);
	friend int listCompare(const BNL& a, const BNL& b);
	friend void listMinus(BNL& a, const BNL& b);
	friend BNL listDivide(const BNL& a, const BNL& b);
	friend BNL listMod(const BNL& a, const BNL& b);
	friend BNL listGCD(const BNL& a, const BNL& b);

};

bool operator==(const BigRational& a, const BigRational& b);
int compare(const BigRational& a, const BigRational& b);
BigRational operator+(const BigRational& a, const BigRational& b);
BigRational operator-(const BigRational& a, const BigRational& b);
BigRational operator*(const BigRational& a, const BigRational& b);
BigRational operator/(const BigRational& a, const BigRational& b);
list<USI> listMultiply(const list<USI>& a, const list<USI>& b);		// Help in mutiply
void listAddTo(list<USI>& a, const list<USI>& b);
int listCompare(const BNL& a, const BNL& b);
void listMinus(BNL& a, const BNL& b);
BNL listDivide(const BNL& a, const BNL& b);
BNL listMod(const BNL& a, const BNL& b);
BNL listGCD(const BNL& a, const BNL& b);

#endif /* BIGRATIONAL_H_ */
