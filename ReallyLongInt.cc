////////////////////////
// ReallyLongInt.cc
// Part of Homework 1
///////////////////////


#include <cmath>
#include <iostream>
#include <climits>

#include "ReallyLongInt.h"


ReallyLongInt::ReallyLongInt()
{
  //Creates a ReallyLongInt of 0 when no parameters are given

  isNeg = false;
  numDigits = 1;

  unsigned int* intArray = new unsigned int[1];
  intArray[0] = 0;
  digits = intArray;
}

ReallyLongInt::ReallyLongInt(long long num)
{
  //Creates a ReallyLongInt from a long long

  int length;
  
  if (num == 0) { //number is 0
    length = 1;
    isNeg = false;
  }
  else if (num < 0) { //number is negative
    length = floor(log10(-num)) + 1;
    num = -num;
    isNeg = true;
  }
  else { //number is positive
    length = floor(log10(num)) + 1;
    isNeg = false;
  }

  unsigned int* longArray = new unsigned int[length];

  for (int i = length - 1; i >= 0; i--) { //inserts digits in array
    longArray[i] = num%10;
    num /= 10;
  }

  numDigits = length;
  digits = longArray;
}

ReallyLongInt::ReallyLongInt(const string& numStr)
{
  //Creates a ReallyLongInt from a number string

  string tempStr;

  if (numStr[0] == '-') { //negative number
    isNeg = true;
    tempStr = numStr.substr(1);
  }
  else { //not negative number
    isNeg = false;
    tempStr = numStr;
  }

  unsigned length = tempStr.size();
  unsigned int* longArray = new unsigned int[length];

  for (unsigned i = 0; i < length; i++) { //inserts numbers in array
    longArray[i] = tempStr[i] - '0';
  }
  
  numDigits = length;
  removeLeadingZeros(longArray, numDigits);

  if (longArray[0] == 0 && numDigits == 1) { //number is 0
    isNeg = false;
  }

  digits = longArray;
}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other)
{
  //Create ReallyLongInt from another ReallyLongInt

  if (other.digits[0] == 0 && other.numDigits == 1) { //number is 0
    isNeg = false;
  }
  else { //number is not 0
    isNeg = other.isNeg;
  }

  numDigits = other.numDigits;

  unsigned int* thisArray = new unsigned int[numDigits];

  for(unsigned i = 0; i < numDigits; i++) { //inserts digits in array
    thisArray[i] = other.digits[i];
  }

  digits = thisArray;
}

ReallyLongInt::ReallyLongInt(unsigned* digitsArr, unsigned arrSize, bool isNeg)
{
  //Create a ReallyLongInt from an array of digits

  removeLeadingZeros(digitsArr, arrSize);
  digits = digitsArr;
  numDigits = arrSize;

  if (digitsArr[0] == 0 && arrSize == 1) { //number is 0
    this -> isNeg = false;
  }
  else { //number is not 0
    this -> isNeg = isNeg;
  }
}

ReallyLongInt::~ReallyLongInt()
{
  //destructor

  delete[] digits;
}

void ReallyLongInt::removeLeadingZeros(unsigned* x, unsigned& xSize)
{
  //Remove zeros before a number

  unsigned i = 0;
  while (x[i] == 0 && i < xSize - 1) { //count number of leading zeros
    i++;
  }

  if (i == xSize-1 && x[i] == 0) { //the number is just a bunch of zeros
    xSize = 1;
  }
  else {
    for (unsigned j = 0; j <= xSize-i; j++) {
      x[j] = x[j+i];
    }
    
    xSize = xSize-i;
  }
}

ostream& ReallyLongInt::print(ostream& out) const
{
  //Print a ReallyLongInt

  if (isNeg == true && digits[0] != 0) { //negative number
    out << '-';
  }
  
  for (unsigned i = 0; i < numDigits; i++) { //print out digits
    out << digits[i];
  }

  return out;
}

void ReallyLongInt::swap(ReallyLongInt other)
{
  //Swap two ReallyLongInts

  bool tempIsNeg = isNeg;
  isNeg = other.isNeg;
  other.isNeg = tempIsNeg;

  unsigned tempNumDigits = numDigits;
  numDigits = other.numDigits;
  other.numDigits = tempNumDigits;

  const unsigned* tempArray = digits;
  digits = other.digits;
  other.digits = tempArray;
  
}

bool ReallyLongInt::equal(const ReallyLongInt& other) const
{
  //compare two ReallyLongInts for equality

  unsigned int i = 0;
  
  if (this -> isNeg != other.isNeg) {
    return false;
  }

  if (this -> numDigits != other.numDigits) { //not equal sizes
    return false;
  }

  while (i < this -> numDigits) { //check each digit
    if (this -> digits[i] != other.digits[i]) {
      return false;
    }
    i ++;
  }
  return true;
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const
{
  //If the absolute value of this is greater than other, returns true

  unsigned int i = 0;
  
  if (this -> numDigits > other.numDigits) { 
    return true;
  }
  else if (this -> numDigits < other.numDigits) { 
    return false;
  }
  else{ //same number of digits
    while (i < this -> numDigits) {
      if (this -> digits[i] > other.digits[i]) { 
	return true;
      }
      else if (this -> digits[i] < other.digits[i]) {
	return false;
      }
      i++;
    }
    return false;
  }
}

bool ReallyLongInt::greater(const ReallyLongInt& other) const
{
  //If this is greater than other, returns true

  bool isGreater = absGreater(other);

  if (this -> isNeg == true && other.isNeg == true) {
    return !isGreater;
  }
  
  if (isGreater == true && this -> isNeg == true) {
    return !isGreater;
  }

  if (isGreater == false && other.isNeg == true) {
    return !isGreater;
  }

  return isGreater;
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const
{
  //adds two ReallyLongInts and returns a ReallyLongInt

  int length; //determine longer int
  if (this -> numDigits > other.numDigits) {
    length = this -> numDigits;
  }
  else{
    length = other.numDigits;
  }

  unsigned int* resultArray = new unsigned int[length+1];
  
  int i = -1;
  unsigned int temp = 0;
  unsigned int xValue;
  unsigned int yValue;

  while (i >= -1*(length+1)) { //using addition algorithm
    if (i <= -1*(this -> numDigits + 1)){
      xValue = 0;
    }
    else {
      xValue = this -> digits[this -> numDigits+i];
    }
    if (i <= -1*(other.numDigits+1)) {
      yValue = 0;
    }
    else {
      yValue = other.digits[other.numDigits+i];
    }

    unsigned int newValue = xValue + yValue + temp; //add carried digit
    temp = newValue/10;
    unsigned int finalValue = newValue%10;
    resultArray[length+1+i] = finalValue;
    i--;
  }

  length++;
  return ReallyLongInt(resultArray, length, false);
}

ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const
{
  //subtract the absolute value of other from the absolute value of this

  const unsigned int* x;
  unsigned int xSize;
  const unsigned int* y;
  unsigned int ySize;
  bool negative;

  if (this -> absGreater(other) || this -> equal(other)) {
    negative = false;
    x = this -> digits;
    xSize = this -> numDigits;
    y = other.digits;
    ySize = other.numDigits;
  }
  else {
    negative = true;
    x = other.digits;
    xSize = other.numDigits;
    y = this -> digits;
    ySize = this -> numDigits;
  }

  int length; //determine longer int
  if (this -> numDigits > other.numDigits) {
    length = this -> numDigits;
  }
  else{
    length = other.numDigits;
  }

  unsigned int* resultArray = new unsigned int[length];
  
  int i = length-1;
  int temp = x[xSize-1];
  int xValue;
  int yValue;

  while (i >= 0) {   
    xValue = temp;

    if ((xSize - ySize) > i) {
      yValue = 0;
    }
    else {
      yValue = y[i - (xSize-ySize)];
    }
      
    if (xValue < yValue) {
      xValue = xValue+10;
      temp = x[i-1] - 1;
    }
    else {
      temp = x[i-1];
    }
 
    unsigned int newValue = xValue - yValue;
    resultArray[i] = newValue;
    i--;
  }

  return ReallyLongInt(resultArray, length, negative);
}

ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const
{
  //Multiply the absolute value of this to the absolute value of other

  unsigned int* resultArray = new unsigned int[this -> numDigits + other.numDigits];
  
  for (int i = 0; i < this -> numDigits + other.numDigits; i++) {
    resultArray[i] = 0;
  }

  for (int i = 0; i <= this -> numDigits - 1; i++) { //using multiplication algorithm
    int c = 0;
    for (int j = 0; j <= other.numDigits - 1; j++) {
      int d = this -> numDigits + other.numDigits - i - j;
      int s = resultArray[d-1] + this -> digits[this -> numDigits-i-1]*other.digits[other.numDigits-j-1] + c;
      resultArray[d-1] = s%10;
      c = s/10;
    }
    resultArray[this -> numDigits-1-i] = resultArray[this -> numDigits-1-i] + c;
  }

  unsigned int resultSize = this -> numDigits + other.numDigits;
  return ReallyLongInt(resultArray, resultSize, false);
}

void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  remainder = 0;
  unsigned int curDigit;
  unsigned int* q = new unsigned int[this -> numDigits];

  for (unsigned int i = 0; i < this -> numDigits; i++) {
    remainder = 10*remainder;
    curDigit = this -> digits[i];
    remainder = remainder.absAdd(ReallyLongInt(curDigit));
    unsigned int d = 0;
    while (remainder.absGreater(other) || remainder.equal(other)) {
      remainder = remainder.absSub(other);
      d++;
    } 
    q[i] = d;
  }
  
  ReallyLongInt num(q, this -> numDigits, false);
  quotient = num;
} 

ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const
{
  if (this -> isNeg == true && other.isNeg == true) { 
    ReallyLongInt num(absAdd(other));
    num.flipSign();
    return num;
  }
  if (this -> isNeg == false && other.isNeg == false) {
    return absAdd(other);
    
  }
  if (this -> isNeg == true && other.isNeg == false) {
    return other.absSub(*this);
  }
  return absSub(other);
}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const
{
  if (this -> isNeg == true && other.isNeg == true) {
    ReallyLongInt num(absSub(other));
    num.flipSign();
    return num;
  }
  if (this -> isNeg == false && other.isNeg == false) {
    return absSub(other);
  }

  if (this -> isNeg == true && other.isNeg == false) {
    ReallyLongInt num(absAdd(other));
    num.flipSign();
    return num;
  }

  return absAdd(other);
 
}

ReallyLongInt ReallyLongInt::mult(const ReallyLongInt & other) const
{
  if (this -> isNeg == true && other.isNeg == true) {
    return absMult(other);
  }
  if (this -> isNeg == false && other.isNeg == false) {
    return absMult(other);
  }
  ReallyLongInt num(absMult(other));
  num.flipSign();
  return num;
}

void ReallyLongInt::div(const ReallyLongInt& denominator, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  if (this -> isNeg == true && denominator.isNeg == true) {
    absDiv(denominator, quotient, remainder);
    remainder.flipSign();
  }
  else if (this -> isNeg == false && denominator.isNeg == false) {
    absDiv(denominator, quotient, remainder);
  }
  else if (this -> isNeg == true && denominator.isNeg == false) {
    absDiv(denominator, quotient, remainder);
    quotient.flipSign();
    remainder.flipSign();
  }
  else {
    absDiv(denominator, quotient, remainder);
    quotient.flipSign();
  }
}

void ReallyLongInt::flipSign()
{
  if(digits[0] == 0 && numDigits == 1){
    isNeg = false;
  }
  else {
    isNeg = !isNeg;
  }
}

long long ReallyLongInt::toLongLong() const
{
  ReallyLongInt longMax(LLONG_MAX);
  longMax++;
  
  ReallyLongInt intAnswer = *this%longMax;
  long long longAnswer = 0;

  for(unsigned int i = 0; i < intAnswer.numDigits; i++) {
    long long digit = intAnswer.digits[i];
    unsigned int j = 1;
    while (j < intAnswer.numDigits - i) {
      digit *= 10;
      j++;
    }
    longAnswer += digit;
  }

  if (isNeg == true) {
    longAnswer*= -1;
  }
  
  return longAnswer;
}

ostream& operator<<(ostream& out, const ReallyLongInt& x)
{
  x.ReallyLongInt::print(out);

  return out;
}

bool operator==(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.ReallyLongInt::equal(y);
}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return !x.ReallyLongInt::equal(y);
}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.ReallyLongInt::greater(y);
}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return y.ReallyLongInt::greater(x);
}

bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.ReallyLongInt::greater(y) || x.ReallyLongInt::equal(y);
}

bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return y.ReallyLongInt::greater(x) || x.ReallyLongInt::equal(y);
}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other)
{
  swap(other);
  return *this;
}

ReallyLongInt ReallyLongInt::operator-() const
{
  ReallyLongInt x(*this);
  x.flipSign();
  return x;
}

ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.add(y);
}

ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.sub(y);
}

ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.mult(y);
}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt quotient;
  ReallyLongInt remainder;
  x.div(y, quotient, remainder);
  return quotient;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt quotient;
  ReallyLongInt remainder;
  x.div(y, quotient, remainder);
  return remainder;
}

ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other)
{
  swap(add(other));
  return *this;
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other)
{
  swap(sub(other));
  return *this;
}

ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other)
{
  swap(mult(other));
  return *this;
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other)
{
  ReallyLongInt quotient;
  ReallyLongInt remainder;
  div(other, quotient, remainder);
  *this = quotient;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other)
{
  ReallyLongInt quotient;
  ReallyLongInt remainder;
  div(other, quotient, remainder);
  *this = remainder;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator++()
{
  ReallyLongInt x(1);
  swap(add(x));
  return *this;
}

ReallyLongInt& ReallyLongInt::operator--()
{
  ReallyLongInt x(1);
  swap(sub(x));
  return *this;
}

ReallyLongInt ReallyLongInt::operator++(int dummy)
{
  ReallyLongInt num(*this);
  ReallyLongInt x(1);
  swap(add(x));
  return num;
}

ReallyLongInt ReallyLongInt::operator--(int dummy)
{
  ReallyLongInt num(*this);
  ReallyLongInt x(1);
  swap(sub(x));
  return num;
}
