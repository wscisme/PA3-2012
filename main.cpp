/*******************************************************
 * COMP2012 - 2012/13 Spring
 * Programming Assignment 3
 * File: main.cpp
 *******************************************************/

#include <iostream>
#include <fstream>
#include "BigRational.h"
#include "BigInteger.h"

using namespace std;

template <typename T>
T readBigNumber(const char* filename)
{
  ifstream fin(filename,  ifstream::in);

  T temp;

  fin >> temp;
  fin.close();

  return (temp);
}

ostream& print(const list<unsigned short int>& a, ostream& os)
{
  for (list<unsigned short int>::const_reverse_iterator it=a.rbegin(); it!=a.rend(); it++)
  {
    os << (*it);  
  } 
  return (os); 
}

int main(int argc, char* argv[])
{
   streambuf* buf;
   ofstream of;
   if (argc > 1) {
      of.open(argv[1]);
      buf = of.rdbuf();
   } else {
      buf = std::cout.rdbuf();
   }
   ostream out(buf);

   string strArry[3] = {"1001", "1001/1002", "1003"};

   BigNumber *bigNums[3];
   bigNums[0] =new BigRational();
   bigNums[1] =new BigRational();
   bigNums[2] =new BigInteger();
   for (int i=0; i<3; i++)
   {
      bigNums[i]->str2bigNumber(strArry[i]);
      out << "bigNums[" << i << "]=" << *bigNums[i] << endl;
      out << "bigNums[" << i << "].toString=" << bigNums[i]->toString() << endl;
   }

   BigRational *bigRat[3];
   bigRat[0] = new BigRational(bigNums[0]->toString());
   bigRat[1] = new BigRational(bigNums[1]->toString());
   bigRat[2] = new BigInteger(bigNums[2]->toString());
   for (int i=0; i<3; i++)
   {
      out << "bigRat[" << i << "]=" << *bigRat[i] << endl;
      out << "bigRat[" << i << "].toString=" << bigRat[i]->toString() << endl;
   }
   out << "bigRat[2].BigRational::toString=" << bigRat[2]->BigRational::toString() << endl;


  out << "------- BigRationals --------\n";
   BigRational fa = readBigNumber<BigRational>("input1.txt");
   out << "fa=" << fa << endl;
   list<unsigned short int> numerator = fa.getNumerator();
   list<unsigned short int> denominator = fa.getDenominator();
   out << "numerator of fa=";
   print(numerator, out); 
   out << endl;
   out << "denominator of fa=";
   print(denominator, out); 
   out << endl;
   fa.str2bigNumber("1200000/24000000000");
   out << "fa=" << fa << endl;
   fa.simplify();
   out << "fa=" << fa << endl;

   BigRational fb("-123000000/5555555555");
   out << "fb=" << fb << endl;
   BigRational fc;
   fc = fa+fb;
   out << "fc=fa+fb=" << fc << endl;
   fc = fb-fa;
   out << "fc=fb-fa=" << fc << endl;
   fc = fa*fb;
   out << "fc=fa*fb=" << fc << endl;
   fc = fa/fb;
   out << "fc=fa/fb=" << fc << endl;
   fc+=fa;
   out << "fc+=fa=" << fc << endl;
   fc-=fa;
   out << "fc-=fa=" << fc << endl;
   fc*=fa;
   out << "fc*=fa=" << fc << endl;
   fc/=fa;
   out << "fc/=fa=" << fc << endl;
   out << "fc+fb/fc=" << fc+fb/fc << endl;
   out << "fc-fb+fc=" << fc-fb+fc << endl;
   out << "fc*fb-fc=" << fc*fb-fc << endl;
   out << "fc/fb+fc=" << fc/fb+fc << endl;

   BigRational fd("16/20");
   if (compare(fb, fd) == 0)
      out << "fb is equal to fd\n";
   if (compare(fa, fd) == 0)
      out << "fa is equal to fd\n";
   else {
      out << "fa is not equal to fd\n";
   }

   out << "------- BigIntegers--------\n";
   BigInteger a = readBigNumber<BigInteger>("input2.txt");
   out << "a=" << a << endl;
   BigInteger b = a+a;
   out << "b=" << b << endl;
   b.str2bigNumber("0000020123032100045671200000");
   out << "b=" << b << endl;
   b.removeTrailingZeros();
   b.removeLeadingZeros();
   out << "b=" << b << endl;
   BigInteger c("123456789012345");
   out << "c=" << c << endl;

   BigInteger d("123456789012345");
   if (compare(c, d) == 0)
      out << "c is equal to d\n";
   if (compare(a, d) == 0)
      out << "a is equal to d\n";
   else {
      out << "a is not equal to d\n";
   }

   out << "b+c=" << b+c << endl;
   out << "b-c=" << b-c << endl;
   out << "b*c=" << b*c << endl;
   out << "b/c=" << b/c << endl;
   out << "b%c=" << b%c << endl;
   out << "c/b=" << c/b << endl;
   out << "c%b=" << c%b << endl;
   out << "b+c-d=" << b+c-d << endl;
   out << "b-c/d=" << b-c/d << endl;
   out << "b*c/d=" << b*c/d << endl;
   out << "b/c%d=" << b/c%d << endl;

   BigInteger e(0);
   if (e.isZero())
     out << "e is zero.\n";

   if (e==0)
     out << "e is equal to 0.\n";

   b+=c;
   out << "b+=c=" << b << endl;
   b-=c;
   out << "b-=c=" << b << endl;
   b*=c;
   out << "b*=c=" << b << endl;
   b/=c;
   out << "b/=c=" << b << endl;
   b%=c;
   out << "b%=c=" << b << endl;
   a=b++;
   out << "a=b++, a=" << a << ",b=" << b << endl;
   a=b--;
   out << "a=b--, a=" << a << ",b=" << b << endl;
   a=++b;
   out << "a=++b, a=" << a << ",b=" << b << endl;
   a=--b;
   out << "a=--b, a=" << a << ",b=" << b << endl;
   BigInteger gcda(12), gcdb(8);
   out << "gcd(12,8)=" << gcda.gcd(gcdb) << endl;
   out << "lcm(12,8)=" << gcda.lcm(gcdb) << endl;

    
   out << "------- Mixed Operations --------\n";
   out << "fc+10=" << fc+10 << endl;
   out << "10+fc=" << 10+fc << endl;
   out << "fc+b=" << fc+b << endl;
   out << "b+fc=" << b+fc << endl;
   out << "fc/b=" << fc/b << endl;
   out << "b/fc=" << b/fc << endl;
   out << "b+10=" << b+10 << endl;
   out << "10+b=" << 10+b << endl;
   out << "b/10=" << b/10 << endl;
   out << "b%10=" << b%10 << endl;
   out << "fc+b-10=" << fc+b-10 << endl;
   out << "fc*b/10=" << fc*b/10 << endl;

   fd=10;
   out << "fd=" << fd << endl;
   of.close();

   return (0);

}
