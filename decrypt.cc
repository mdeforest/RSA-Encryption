///////////////////////////////////
// decrypt.cc
// Part of homework 1, problem 6
///////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;

int main(int argc, char** argv)
{
  //open file with private key
  ifstream fin(argv[1]);

  //declare key variables
  string a;
  string b;
  fin >> a;
  fin >> b;

  ReallyLongInt d(a);
  ReallyLongInt n(b);

  //open string file to decrypt and decrypted file to which to write
  ifstream encrypted(argv[2]);
  ofstream fout(argv[3]);

  string c;
  encrypted >> c;

  //decrypt every number in file and write the decrypted character to fout
  while(!encrypted.eof()) {
    ReallyLongInt decryptedNumber = modPower(ReallyLongInt(c), d, n);
    long long longDecrypt = decryptedNumber.toLongLong();
    char decryptedChar = char(longDecrypt);
    fout << decryptedChar;
    encrypted >> c;
  }

  fout.close();

}
