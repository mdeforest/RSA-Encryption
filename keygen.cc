////////////////////////////////
// keygen.cc
// Part of homework 1, part 9
////////////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;

int main(int argc, char** argv) {
  /* Function takes two prime numbers, computes n and t, and creates
     a public and private key; writes them to two files*/

  ReallyLongInt prime1 = ReallyLongInt(argv[1]);
  ReallyLongInt prime2 = ReallyLongInt(argv[2]);
  ofstream publicOut(argv[3]);
  ofstream privateOut(argv[4]);

  if (prime1 > 100000 || prime2 > 100000) {
    cout << "One (or both) of your numbers is too large. Primality has not been checked" << endl;
  }
  else {

    if (!isPrime(prime1) || !isPrime(prime2)) {
      // return error message if one of the numbers is not prime

      cout << "One (or both) of your numbers is not prime. Both must be prime numbers" << endl;
      return 1;
    }
  }
  
  //compute n and t
  ReallyLongInt n = prime1*prime2;
  ReallyLongInt t = (prime1 - 1)*(prime2 - 1);

  ReallyLongInt e = 2;
  bool found = false;
  ReallyLongInt d;
  ReallyLongInt y;
  while (e < t && !found) {
    // find an e that is relatively prime to t
    ReallyLongInt gcd = extendedEuclid(e, t, &d, &y);
    if (gcd == 1) {
      found = true;
    }
    else {
      e++;
    }
  }
  //make sure d is positive
  if (d < 0) {
    d = d+t;
  }
   
  publicOut << e << " " << n << endl;
  privateOut << d << " " << n << endl;

  publicOut.close();
  privateOut.close();
  return 0;
}
