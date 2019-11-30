#ifndef  _MATH_UTIL_H
#define	 _MATH_UTIL_H

#include <iostream>
#include <fstream>
#include <string>
#include "CustomException.h"
#include "List.h"
#include "StringUtil.h"
namespace MathUtil
{
	// holds value of the last generated prime number array
	// resets at the start of a new generation
	extern size_t ATKINS_ARRAY_SIZE;
	const size_t MAX_PRIME = 207239;
	/* Generates an array of prime numbers less than the
	specified limit using an implementation of the Sieve of Atkin's algorithm
	@parameter limit bounds the prime number generator
	@return an array of prime numbers less than limit */
	size_t* generatePrimesAtkins(size_t limit);
	/* This function tests for primality using an implementation
	of based on the Miller-Rabins Primality Test
	@param k is an input parameter that determines
	accuracy level. Higher value of k indicates more accuracy.
	@param n is the integer to be tested
	@return returns false if n is composite and returns true if n
	is probably prime.   */
	bool isPrimeMillerRabin(size_t n, int k);
	/* Identify an archived prime that is atleast 2 times greater than target
	@pre size cannot be greater than 9973 and primes2.txt must exist in
	root directory unmodified
	@return prime that is greater than or equal to 2 times argument size */
	size_t findPrime(size_t size);
	/* Utility function to do modular exponentiation.
	@param x is the base
	@param y is the exponenet
	@param p is the modulus of congruence
	@return  (x^y) % p */
	int power(int x, unsigned int y, int p);
	/* This function is called for all k trials. It returns
	false if n is composite and returns false if n is
	probably prime.
	@param d is an odd number such that  d*2^r = n - 1 for some r >= 1
	@param n is an odd integer to be tested for primality
	@return true if n is prime else false if n is composite */
	bool millerTest(int d, int n);

}
#endif // ! _MATH_UTIL_H
