#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H

#include <iostream>

template <class X>
bool isPrime(const X& num)
{
  if (num == 0 || num == 1) {
    return false;
  }

  X divisor = 2;
  bool primeNum = true;

  while (divisor <= num/2) {
    if (num % divisor == 0) {
      primeNum = false;
    }
    divisor++;
  }

  return primeNum;
}

template <class X>
X modPower(const X& base, const X& exponent, const X& modulus)
{
  X num = 1;
  
  if (exponent == 0) {
    num = 1;
  }
  else if (exponent == 1) {
    num = base % modulus;
  }
  
  else {
    X newPower = modPower(base, exponent/2, modulus);

    if ((exponent%2) == 0) {
      num = (newPower*newPower) % modulus;
    }
    else {
      X num2 = (newPower*newPower) % modulus;
      num = (base*num2) % modulus;   
    }
  }

  return num % modulus;
}

template <class X>
X extendedEuclid(const X& a, const X& b, X* x, X* y)
{
  if (b == 0) {
    *x = 1;
    *y = 0;
    return a;
  }
  else {
    X d = extendedEuclid(b, a%b, x, y);
    X x2 = *y;
    X y2 = *x - *y*(a/b);
    *x = x2;
    *y = y2;
    return d;
  }
}

#endif
 
