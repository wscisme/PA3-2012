/*******************************************************
 * COMP2012 - 2012/13 Spring
 * Programming Assignment 3
 * File: BigNumber.cpp
 *******************************************************/

#include "BigNumber.h"

// Default constructor
BigNumber::BigNumber():sign(PLUS){}

// Typical constructor: to allocate n list elements
BigNumber::BigNumber(int n):digitLists(n),sign(PLUS){}

// Destructor
BigNumber::~BigNumber(){}

void BigNumber::print(ostream& os) const
{
	list<unsigned short int>::const_reverse_iterator p;
	if(!sign) os << '-';
	for(unsigned int i=0; i<digitLists.size(); ++i){
		p=digitLists[i].rbegin();
		for(; p!=digitLists[i].rend(); ++p)
			os << *p;
	}
}

void BigNumber::removeLeadingZeros()
{// no checking now, can be empty now
	list<unsigned short int>::reverse_iterator p;
	for(unsigned int i=0; i<digitLists.size(); ++i)
		while(*digitLists[i].rbegin()==0)
			digitLists[i].pop_back();
}

void BigNumber::removeTrailingZeros()
{// no checking now
	list<unsigned short int>::reverse_iterator p;
	for(unsigned int i=0; i<digitLists.size(); ++i)
		while(*digitLists[i].begin()==0)
			digitLists[i].pop_front();
}

void BigNumber::abs()
{
	sign=PLUS;
}


// Output operator
ostream & operator<<(ostream& os, const BigNumber& a)
{
	a.print(os);
	return os;
}

// Input operator
istream & operator>>(istream& is, BigNumber& a)
{
	a.read(is);
	return is;
}
