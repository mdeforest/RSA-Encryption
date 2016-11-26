///////////////////////////////////
// encrypt.cc
// Part of homework 1, problem 6
///////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;

int main(int argc, char** argv) {
  //open file with public key
  ifstream fin(argv[1]);

  //declare key variables
  string a;
  string b;
  fin >> a;
  fin >> b;

  ReallyLongInt e(a);
  ReallyLongInt n(b);

  //open string file to encrypt and encrypted file to which to write
  ifstream textFile(argv[2]);
  ofstream fout(argv[3]);

  //encrypt each character and write it to the encrypted file
  char d;
  while (textFile.get(d)){
    ReallyLongInt c(d);
    ReallyLongInt encryptNum = modPower(c, e, n);
    fout << encryptNum << endl;
  }

  fout.close();
}
