# RSA Cryptography Lab

This project is my SIT102 H1 "Something Awesome" project.

The RSA Cryptography Lab is a C++ terminal-based program that demonstrates how RSA encryption works. It connects programming concepts from SIT102 with mathematical concepts from discrete mathematics, including prime numbers, modular arithmetic, greatest common divisors, modular inverses, and modular exponentiation.

## Project Purpose

The purpose of this project is to create an interactive cryptography simulator that helps users understand how RSA public-key encryption works. The program allows users to generate RSA keys, encrypt and decrypt messages, save and load encrypted messages, view an explanation of the RSA process, and test how small RSA keys can be cracked by factorisation.

## Features

- Generate RSA keys using two prime numbers
- Validate prime numbers
- Calculate `n = p × q`
- Calculate `phi = (p - 1)(q - 1)`
- Check greatest common divisor using Euclid's algorithm
- Find the modular inverse for the private key
- Encrypt messages using the public key
- Decrypt messages using the private key
- Save encrypted messages to a text file
- Load encrypted messages from a text file
- Show an explanation of the RSA mathematics
- Attempt a simple crack of small RSA keys by factorising `n`
- Run a guided RSA demonstration

## Why This Is HD-Level

This project goes beyond basic introductory programming because it combines C++ programming with cryptography and discrete mathematics.

It demonstrates programming concepts such as:

- structs
- arrays
- functions
- loops
- conditionals
- input validation
- references
- file input/output
- modular program design

It also demonstrates concepts beyond the standard SIT102 scope, including:

- RSA encryption
- prime number testing
- Euclid's algorithm
- modular inverses
- modular exponentiation
- simple factorisation attacks

The simple crack mode shows why real RSA encryption requires very large prime numbers. This connects the program to real-world cybersecurity and computer science.

## How to Compile

Use the SplashKit compiler command:

```bash
skm clang++ rsa_lab.cpp -o rsa_lab
```

## How to Run

On Windows/MSYS2:

```bash
./rsa_lab.exe
```

## Example Test Values

Use these values when generating keys:

```text
p = 17
q = 11
e = 7
```

Expected results:

```text
n = 187
phi = 160
d = 23
```

You can then encrypt a short message such as:

```text
HELLO
```

The program will convert each character to an ASCII number, encrypt it, and then decrypt it back to the original message.

## Iterative Development

This project was developed iteratively using GitHub commits. Each commit represents a development checkpoint, such as creating the menu, adding prime checking, generating RSA keys, adding encryption and decryption, adding file input/output, and adding the RSA explanation and crack mode.

## Author

Abby