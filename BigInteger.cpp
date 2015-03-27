/*******************************************************
 * COMP2012 - 2012/13 Spring
 * Programming Assignment 3
 * File: BigInteger.cpp
 *******************************************************/

#include "BigInteger.h"


BigInteger::BigInteger():BigRational()				//Default constructor
{
	Dno.push_front(1);
}

BigInteger::BigInteger(int d):BigRational(d){}			//Convert constructor


BigInteger::BigInteger(string c):BigRational(c){}		//Convert constructor


BigInteger::BigInteger(const BigInteger& a):BigRational(0)		//Copy constructor
{
	Nmr=a.Nmr;
}

BigInteger::~BigInteger()								//Destructor
{
	Nmr.clear();
	Dno.clear();
}

BigInteger& BigInteger::operator/=(const BigInteger& a)		//Division assignment operator
{
	return *this=*this/a;
}

BigInteger& BigInteger::operator%=(const BigInteger& a)		//Modulus assignment operator
{
	return *this=*this%a;
}

BigInteger& BigInteger::operator++()				//Prefix increment operator
{
	BNL one;
	one.push_front(1);
	if(sign==PLUS)	listAddTo(Nmr, one);
	else			listMinus(Nmr, one);
	return *this;
}

BigInteger& BigInteger::operator--()				//Prefix decrement operator
{
	BNL one;
	one.push_front(1);
	if(sign==PLUS)
		if(Nmr.size()==1 && *Nmr.begin()==0 ){
			*Nmr.begin()=1;
			sign=MINUS;
		}
		else	listMinus(Nmr, one);
	else		listAddTo(Nmr, one);

	return *this;
}


BigInteger BigInteger::operator++(int dummy)		//Postfix increment operator
{
	BigInteger c(*this);
	++*this;
	return c;
}

BigInteger BigInteger::operator--(int dummy)		//Postfix decrement operator
{
	BigInteger c(*this);
	--*this;
	return c;
}

BigInteger& BigInteger::operator=(const BigInteger& a)
{
	sign=a.sign;
	Nmr=a.Nmr;
	return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& a)
{
	return *this=*this+a;
}

BigInteger& BigInteger::operator-=(const BigInteger& a)
{
	return *this=*this-a;
}

BigInteger& BigInteger::operator*=(const BigInteger& a)
{
	return *this=*this*a;
}


void BigInteger::str2bigNumber(const string str)	//Convert a string to the current BigInteger.
{
	BigRational::str2bigNumber(str);
}

string BigInteger::toString() const					//Convert the BigInteger to a string
{
	string s;
	if(!sign) s += '-';

	int n=Nmr.size();
	BNL::const_reverse_iterator it =Nmr.rbegin();
	for(int i=0; i<n; ++i, ++it)
		s+=static_cast<char>(*it+48);

	return s;
}

void BigInteger::print(ostream &os) const
{
	if(!sign) os << '-';

	int n=Nmr.size();
	BNL::const_reverse_iterator it =Nmr.rbegin();
	for(int i=0; i<n; ++i, ++it)	os << *it;

}

void BigInteger::read(istream &is)					//Read from the istream, is,
{
	string s;
	is >> s;
	BigRational::str2bigNumber(s);
}

BigInteger BigInteger::gcd(const BigInteger& a)		//	Greatest common division
{
	BigInteger gcd(1);
	gcd.Nmr=listGCD(Nmr, a.Nmr);

	return gcd;
}

BigInteger BigInteger::lcm(const BigInteger& a)		//	Least common multiple
{
	return (*this*a)/gcd(a);						// [m,n]=m*n/(m,n)
}

// Non-member functions

bool operator==(const BigInteger& a, const BigInteger& b)
{
	return !compare(a, b);
}

int compare(const BigInteger& a, const BigInteger& b)
{
	if (a.sign > b.sign)		 return 1;
	else if (b.sign > a.sign)	 return -1;

	int cpr=listCompare(a.getNumerator(), b.getNumerator());
	if(a.sign==1)	return cpr;
	else			return -cpr;
}

BigInteger operator+(const BigInteger& a, const BigInteger& b)
{
	if(a.sign!=b.sign){
		BigInteger c(a);
		c.sign=b.sign;
		return b-c;
	}
	BigInteger c(0);
	listAddTo(c.Nmr, a.Nmr);
	listAddTo(c.Nmr, b.Nmr);
	c.sign=a.sign;

	return c;
}

BigInteger operator-(const BigInteger& a, const BigInteger& b)
{
	BigInteger c;
	if(a.sign!=b.sign){
		c=b;
		c.sign=a.sign;
		return c+a;
	}

	int cpr=compare(a,b);
	if(cpr==0)  return BigInteger(0);
	else if((cpr==1 && a.sign==1) || (cpr==-1 && a.sign==0)){
		c=a;
		listMinus(c.Nmr, b.Nmr);

	}else{
		c=b;
		listMinus(c.Nmr, a.Nmr);
		c.sign=!a.sign;
	}

	return c;
}

BigInteger operator*(const BigInteger& a, const BigInteger& b)
{
	BigInteger c;
	c.Nmr=listMultiply(a.Nmr, b.Nmr);
	c.sign=(a.sign==b.sign);

	return c;
}

BigInteger operator/(const BigInteger& a, const BigInteger& b)
{
	if(b.isZero()){ cerr<<"Invalid Denominator!!\n"; return b;}
	BigInteger c;
	c.Nmr=listDivide(a.Nmr, b.Nmr);
	c.sign=(a.sign==b.sign);
	if(c.Nmr.empty()) c.Nmr.push_back(0);

	return c;
}

BigInteger operator%(const BigInteger& a, const BigInteger& b)
{
	if(b.isZero()){ cerr<<"Invalid Denominator!!\n"; return b;}
	BigInteger c;
	c.Nmr=listMod(a.Nmr, b.Nmr);

	c.sign=(c.isZero())? 1 : a.sign;
	if(c.Nmr.empty()) c.Nmr.push_front(0);

	return c;
}


//-------------------- Helper functions --------------------
BNL listDivide(const BNL& a, const BNL& b)
{//Should impliment a<b
	BNL n(a);							// numerator in changing
	BNL d(b);							// denominator in changing
	BNL q;	 							// the Quotient
	USI c;								// for each digit of the answer

	int k=n.size()-b.size();			// shifting of d
	for(int i=0; i<k; i++)
		d.push_front(0);				// shift the denominator

	for(; k>=0; k--){
		c=0;
		while(listCompare(n, d)>=0){
			listMinus(n, d);
			c++;
		}
		q.push_front(c);
		d.pop_front();						// shift right the denominator
	}

	while(q.size()>1 && *q.rbegin()==0 )					// Erase the 0s on head
		q.pop_back();

	if(q.empty())  q.push_front(0);

	return q;
}

BNL listMod(const BNL& a, const BNL& b)
{
	BNL n(a);					// numerator in changing
	BNL d(b);					// denominator in changing
	BNL q;						// the Quotient
	USI c;						// for each digit of the answer

	int k=a.size()-b.size();				// shifting of d
	for(int i=0; i<k; i++)
		d.push_front(0);					// shift the denominator

	for(; k>=0; k--){
		c=0;
		while(listCompare(n, d)>=0){
			listMinus(n, d);
			c++;
		}
		q.push_front(c);
		d.pop_front();						// shift right the denominator
	}

	if(n.size()==0) n.push_front(0);

	return n;
}

