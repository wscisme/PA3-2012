/*******************************************************
 * COMP2012 - 2012/13 Spring
 * Programming Assignment 3
 * File: BigRational.cpp
 *******************************************************/

#include "BigRational.h"
#include "BigInteger.h"

BigRational::BigRational():BigNumber(2){}


BigRational::BigRational(int n):BigNumber(2)			//Convert constructor
{// n=0,1,11 bckd
	sign = PLUS;
	digitLists[1].push_front(1);
	if(n<0){
		sign=MINUS;
		n=-n;
	}
	else if(n==0)
		digitLists[0].push_back(0);

	while(n>0){
		digitLists[0].push_back(n%10);
		n=n/10;
	}
}

BigRational::BigRational(string c):BigNumber(2) 				//Convert constructor
{//c="", "0"  bckd
	digitLists[1].push_front(1);
	int i=0;
	if(c[i]=='-'){
		sign=false;
		i++;
	}
	for(;c[i] && c[i] != '/';++i)
		digitLists[0].push_front(c[i]-48);

	if(c[i++] == '/'){
		for(;c[i];++i)
			digitLists[1].push_front(c[i]-48);
		digitLists[1].pop_back();
	}
}

BigRational::BigRational(const BigRational& a):BigNumber(2)
{
	sign=a.sign;
	Nmr=a.Nmr;
	Dno=a.Dno;
}

BigRational::~BigRational()
{
	Nmr.clear();
	Dno.clear();
}

BigRational& BigRational::operator=(const BigRational& a)
{
	if(this == &a) return *this;				// to avoid self problem
	sign=a.sign;
	Nmr=a.Nmr;
	Dno=a.Dno;

	return *this;
}

BigRational& BigRational::operator+=(const BigRational& a)
{
	return *this=*this+a;
}

BigRational& BigRational::operator-=(const BigRational& a)
{
	return *this=*this-a;
}

BigRational& BigRational::operator*=(const BigRational& a)
{
	sign=(sign==a.sign);
	Nmr=listMultiply(Nmr, a.Nmr);
	Dno=listMultiply(Dno, a.Dno);
	simplify();

	return *this;
}

BigRational& BigRational::operator/=(const BigRational& a)
{
	return *this=*this/a;
}

bool BigRational::isZero() const
{
	if(digitLists[0].empty() || (Nmr.size()==1 && *Nmr.begin()==0))
		return true;

	return false;
}

void BigRational::str2bigNumber(const string s)
{
	Nmr.clear();						// delete the origin list if any
	Dno.clear();
	Dno.push_front(1);
	int n=s.size();
	int i=0;
	if(s[i]=='-'){ sign=MINUS; ++i;}	// check negative
	for(; i<n && s[i]!='/'; ++i)
		Nmr.push_front(s[i]-48);

	if(i==n)	return;					// if input integer, return now
	++i;
	for(; i<n ; ++i) Dno.push_front(s[i]-48);
	Dno.pop_back();

}

string BigRational::toString() const
{
	string s;
	if(!sign) s += '-';

	int n=Nmr.size();
	int d=Dno.size();
	BNL::const_reverse_iterator it =Nmr.rbegin();
	for(int i=0; i<n; ++i, ++it)
		s+=static_cast<char>(*it+48);

	s+='/';
	it = Dno.rbegin();
	for(int i=0; i<d; ++i, ++it)
		s+=static_cast<char>(*it+48);

	return s;
}

void BigRational::print(ostream &os) const
{
	if(!sign) os << '-';

	int n=Nmr.size();
	int d=Dno.size();
	BNL::const_reverse_iterator it =Nmr.rbegin();
	for(int i=0; i<n; ++i, ++it)	os << *it;

	os << '/';
	it = Dno.rbegin();
	for(int i=0; i<d; ++i, ++it)	os << *it;
}

void BigRational::read(istream &is)
{
	string s;
	is >> s;
	BigRational::str2bigNumber(s);
}

void BigRational::simplify()
{
	if(Nmr.size()==1 && *Nmr.begin()==0){Dno=BNL(1,1); return;} // 0 checking
	BNL gcd=listGCD(Nmr, Dno);
	Nmr=listDivide(Nmr, gcd);
	Dno=listDivide(Dno, gcd);
}

list<unsigned short int> BigRational::getNumerator() const
{
	return Nmr;
}

list<unsigned short int> BigRational::getDenominator() const
{
	return Dno;
}


//----------------- Non-member functions --------------------
bool operator==(const BigRational& a, const BigRational& b)
{
	return !compare(a, b);
}

int compare(const BigRational& a, const BigRational& b)
{
	if(a.getNumerator().empty()||b.getNumerator().empty())		// check empty
	{ cerr << "Invalid action with empty BigNumber!!\n"; return 0;}

	if (a.sign > b.sign)		 return 1;
	else if (b.sign > a.sign)	 return -1;

	// Suppose c=|a/b|
	BNL cn=listMultiply(a.getNumerator(), b.getDenominator());	// c.Nmr
	BNL cd=listMultiply(b.getNumerator(), a.getDenominator());	// c.Dno
	int cpr=listCompare(cn, cd);					// c>1?

	if(a.sign==1)	return cpr;
	else			return -cpr;
}

BigRational operator+(const BigRational& a, const BigRational& b)
{// a>=0, b<0 ; a<0
	if(a.sign!=b.sign){
		BigRational c(a);
		c.sign=b.sign;
		return b-c;
	}
	BigRational c(0);
	c.Dno=listMultiply(a.getDenominator(),b.getDenominator());
	listAddTo(c.Nmr, listMultiply(a.getNumerator(),b.getDenominator()));
	listAddTo(c.Nmr, listMultiply(a.getDenominator(), b.getNumerator()));

	c.sign=a.sign;
	c.simplify();

	return c;
}

BigRational operator-(const BigRational& a, const BigRational& b)
{
	BigRational c;
	BNL tmp;				// temp elements for calculation
	if(a.sign!=b.sign){
		c=b;
		c.sign=a.sign;
		return c+a;
	}

	int cpr=compare(a,b);
	if(cpr==0)
		return BigRational(0);
	else if((cpr==1 && a.sign==PLUS) || (cpr==-1 && a.sign==MINUS)){
		c.Nmr=listMultiply(a.Nmr, b.Dno);
		tmp=listMultiply(b.Nmr, a.Dno);
		listMinus(c.Nmr, tmp);
		c.Dno=listMultiply(a.Dno, b.Dno);
		c.sign=a.sign;
	}
	else{
		c.Nmr=listMultiply(b.Nmr, a.Dno);
		tmp=listMultiply(a.Nmr, b.Dno);
		listMinus(c.Nmr, tmp);
		c.Dno=listMultiply(a.Dno, b.Dno);
		c.sign=!a.sign;
	}
	c.simplify();

	return c;
}

BigRational operator*(const BigRational& a, const BigRational& b)
{
	BigRational c;
	c.Nmr=listMultiply(a.Nmr, b.Nmr);
	c.Dno=listMultiply(a.Dno, b.Dno);
	c.sign=(a.sign==b.sign);
	c.simplify();				// may consider optimization here

	return c;
}

BigRational operator/(const BigRational& a, const BigRational& b)
{
	BigRational c;
	if(b.isZero()){ cerr << "Not valid denominator!!\n"; return c;}		// Error checking

	c.Nmr=listMultiply(a.Nmr, b.Dno);			// can consider optimization here by list divide
	c.Dno=listMultiply(a.Dno, b.Nmr);
	c.sign=(a.sign==b.sign);
	c.simplify();

	return c;
}

//----------------- Helper functions -----------------------

int listCompare(const BNL& a, const BNL& b)
{
	int na=a.size();
	int nb=b.size();
	if(na>nb)				return 1;
	else if(na<nb)		return -1;

	BNL::const_reverse_iterator pa= a.rbegin();			// remaining are for lists of same length
	BNL::const_reverse_iterator pb= b.rbegin();

	for(int i=0; i<na ; ++i, ++pa, ++pb)
		if(*pa>*pb)		 return 1;
		else if(*pa<*pb) return -1;

	return 0;
}

void listAddTo(BNL& b,  const BNL& a)
{//b empty? a empty?
	// Haven't implement check empty
	int n=b.size();
	int na=a.size();
	int k=(n<na)? n:na;				// k is the number of first cycle
	USI c=0;						// carryIn
	BNL::iterator p = b.begin();
	BNL::const_iterator pa = a.begin();

	for(int i=0; i<k; i++, ++p, ++pa){
		*p= *p+ *pa+c;
		c=0;
		if(*p>9){					// determine carry out
			*p-=10;
			c=1;
		}
	}

	for(int j=n; j<na; ++j, ++pa){			// to deal with higher terms in a
		b.push_back(*pa+c);					// haven't check out of bound
		c=0;
		if( *b.rbegin()>9){
			*b.rbegin() -=10;
			c=1;
		}
	}

	while (c){								// deal with the remaining carry out
		if(p!= b.end())  *p = *p+c;
		else{
			b.push_back(1);
			break;
		}
		c=0;
		if(*p>9){
			*p -=10;
			c=1;
		}
		++p;
	}
}

void listMinus(BNL& a, const BNL& b)
{// To test a=b, b=0, result = 000XXX
	USI carryIn=0;					// CarryIn & CarryOut
	short int d=0;					// digit temp enable negative
	BNL::iterator p=a.begin();				// get the head of digitList
	BNL::const_iterator pb=b.begin();		// have check b=0?

	for(; pb!=b.end() ; ++pb, ++p){
		d=*p-*pb-carryIn;
		carryIn =0;
		if(d<0){
			d+=10;
			carryIn=1;
		}
		*p=d;
	}

	while(carryIn && p!=a.end()){				// pass carryIn	to the end
		d=*p-carryIn;
		carryIn =0;
		if(d<0){
			d+=10;
			carryIn=1;
		}
		*p=d;
		++p;
	}								// this step's return contains 0s in tail

	while(*a.rbegin()==0)			// Erase the 0s on head
		a.pop_back();

	//if(a.empty())	a.push_back(0);		// result empty means a=b
}

list<USI> listMultiply(const list<USI>& a, const list<USI>& b)
{
	list<USI> c(1,0);
	if(a.empty() || b.empty()){ cerr << "Not valid multiplier!!\n"; return c;}	// Error checking

	if((a.size()==1 && *a.begin()==0) || (b.size()==1 && *b.begin()==0))  return c;

	BNL::const_reverse_iterator p = b.rbegin();
	for(int i=b.size(); i>0; --i, ++p){
		for(USI j=0; j< *p; j++)  listAddTo(c, a);					// crucial part

		c.push_front(0);
	}
	c.pop_front();

	return c;
}

BNL listGCD(const BNL& a, const BNL& b)
{
	BNL n;
	BNL m;
	BNL tmp;

	int cpr=listCompare(a, b);
	if(cpr==1) {
		n=b;
		m=listMod(a, b);
	}
	else if(cpr==-1){
		n=a;
		m=listMod(b, a);
	}

	while(m.size()>1 || *m.begin()!=0){
		tmp=listMod(n, m);
		n=m;
		m=tmp;
	}

	return n;
}

