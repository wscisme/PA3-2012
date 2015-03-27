/*******************************************************
 * COMP2012 - 2012/13 Spring
 * Programming Assignment 3
 * File: BigNumber.h
 *******************************************************/
#ifndef _BIGNUMBER_H
#define _BIGNUMBER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <list>
#include <vector>


using namespace std;

#define PLUS true
#define MINUS false

/* BigNumber class:
 */ 
class BigNumber
{
   public:
     // Default constructor 
     BigNumber();
    
     // Typical constructor: to allocate n list elements  
     BigNumber(int n);

     // Destructor
     virtual ~BigNumber();

     virtual void read(istream& is) =0;

     virtual string toString() const =0;

     virtual void str2bigNumber(string s) =0;

     virtual bool isZero() const = 0;

     virtual void print(ostream& os) const;
 
     void removeLeadingZeros();

     void removeTrailingZeros();

     void abs();

   protected:
     vector<list<unsigned short int> > digitLists;
     bool sign;

};

// Output operator
ostream & operator<<(ostream& os, const BigNumber& a);

// Input operator
istream & operator>>(istream& is, BigNumber& a);

#endif
