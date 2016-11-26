Michaela DeForest
CPS 222 Project 1

ReallyLongInt.cc
ReallyLongInt.h
factorial.cc
numberTheory.h
keygen.cc
encrypt.cc
decrypt.cc
Makefile
Homework 1 Cover Sheet.pdf
readme.txt

This project contains three main programs (keygen.cc, encrypt.cc, and decrypt.cc).
The command 'make all' will compile the entire project into three executable files.
Alternatively, you can compile according to the directions below.


--factorial--
To compile: make factorial'
To run: ./factorial <number>
Description: The factorial program takes a number and returns the factorial
representation of that number. When running the program, give the <number>
of which you want the factorial.

Known issues:

-None


--keygen--
To compile: make keygen
To run: ./keygen <prime1> <prime2> <public key file> <private key file>
Description: The keygen program takes two prime numbers, computes n and t, and
creates a public and private key, which is then written to public and private files,
respectively. When running the program, the user should input two prime numbers,
<prime1> and <prime2>, and files to which to write the keys, <public key file> and
<private key file>.

Known issues:

-None


--encrypt--
To compile: make encrypt
To run: ./encrypt <public key file> <text to encrypt file> <encrypted file>
Description: The encrypt program takes text from a file and encrypts it using
the key in the public key file. When running the program, the user should input
a file with the public key, <public key file>, <text to encrypt>, and file to which
to encrypt, <encrypted file>.

Known issues:

-None


--decrypt--
To compile: make decrypt
To run: ./decrypt <private key file> <encrypted text file> <decrypted file>
Description: The decrypt program takes encrypted text and decrypts it using the
private key from the private key file. When running the program, the user should
input <private key file>, <encrypted text file> and a <decrypted file>.

Known issues:

-Does not decrypt correctly when the prime numbers are too large. I imagine that
this is due to an overload error caused by operations on large prime numbers.

