#include <iostream>

#include "ReallyLongInt.h"

int main(int argc, char** argv)
{
  ReallyLongInt num(argv[1]);
  ReallyLongInt i(2);
  ReallyLongInt product(1);

  if (!(num == 0 || num == 1)) {
    while (num >= i) {
      product*= i;
      i++;
    }
  }

  cout << product; 

}
