#include "MathUtil.h"
size_t MathUtil::ATKINS_ARRAY_SIZE = 0;

/* Generates an array of prime numbers less than the
specified limit using an implementation of the Sieve of Atkin's algorithm
@parameter limit bounds the prime number generator
@return an array of prime numbers less than limit */
size_t* MathUtil::generatePrimesAtkins(size_t limit)
{
	ATKINS_ARRAY_SIZE = 0;
	bool* sieve = new bool[limit];
	// Initialise the sieve array with false values 
	for (size_t i = 0; i < limit; i++)
		sieve[i] = false;
	/* Mark sieve[n] true if one of the following is true:
		a) n = (4*x*x)+(y*y) has odd number of
		   solutions, i.e., there exist
		   odd number of distinct pairs (x, y)
		   that satisfy the equation and
			n % 12 = 1 or n % 12 = 5.
		b) n = (3*x*x)+(y*y) has odd number of
		   solutions and n % 12 = 7
		c) n = (3*x*x)-(y*y) has odd number of
		   solutions, x > y and n % 12 = 11		*/
	for (size_t a = 1; a * a < limit; a++) {
		for (size_t b = 1; b * b < limit; b++) {
			// Main part of Sieve of Atkin
			size_t n = (4 * a* a) + (b * b);
			if (n <= limit && (n % 12 == 1 || n % 12 == 5))
				sieve[n] ^= true;
			n = (3 * a * a) + (b * b);
			if (n <= limit && n % 12 == 7)
				sieve[n] ^= true;
			n = (3 * a * a) - (b * b);
			if (a > b && n <= limit && n % 12 == 11)
				sieve[n] ^= true;
		}
	}
	size_t PRIME_SIZE = limit;
	// Mark all multiples of squares as non-prime 
	for (size_t r = 5; r * r < limit; r++) {
		if (sieve[r]) {
			for (size_t i = r * r; i < limit; i += r * r)
			{
				sieve[i] = false;
				PRIME_SIZE--;
			}
		}
	}
	size_t* primes = new size_t[PRIME_SIZE];
	for (size_t i = 0; i < PRIME_SIZE; i++)
		primes[i] = 0;
	size_t i = 0;
	// Prsize_t primes using sieve[] 
	for (size_t x = 5; x < limit && i < PRIME_SIZE; x++)
		if (sieve[x])
		{
			primes[i] = x;
			i++;
		}
	ATKINS_ARRAY_SIZE = PRIME_SIZE;
	return primes;
}
/* Identify the first archived prime greater than the input argument size
using the primes2.txt in the root directory
@param size is the 
@return first prime greater than the input argument size */
size_t MathUtil::findPrime(size_t size)
{
	std::ifstream infile;
	const size_t SIZE = 1862;
	List < std::string>* pPrimes;
	size_t primes[SIZE];
	infile.open("primes2.txt", std::ios::in);
	std::string data;
	if (infile.good())
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			if (getline(infile, data, '\n'))
			{
				pPrimes = StringUtil::split(data, ",");
				primes[i] = std::stoi(pPrimes->getEntry(0));
				pPrimes->clear();
				delete pPrimes;
			}
			//std::cout << primes[i] << std::endl;	// DEBUG
		}
	}
	infile.close();
	/*size_t low, mid, high;
	low = 0;
	mid = SIZE / 2;
	high = SIZE - 1;
	bool done = false;
	while (!done)
	{
		if ()
	}*/
	for (size_t i = 0; i < SIZE; i++)
	{
		if (primes[i] >=  size)
			return primes[i];
	}
	return primes[SIZE - 1];
}
/* Utility function to do modular exponentiation.
@param x is the base
@param y is the exponenet
@param p is the modulus of congruence
@return  (x^y) % p */
int MathUtil::power(int x, unsigned int y, int p)
{
	int res = 1;      // Initialize result 
	x = x % p;  // Update x if it is more than or 
				// equal to p 
	while (y > 0)
	{
		// If y is odd, multiply x with result 
		if (y & 1)
			res = (res*x) % p;

		// y must be even now 
		y = y >> 1; // y = y/2 
		x = (x*x) % p;
	}
	return res;
}
/* This function is called for all k trials. It returns
false if n is composite and returns false if n is
probably prime. 
@param d is an odd number such that  d*2^r = n - 1 for some r >= 1
@param n is an odd integer to be tested for primality
@return true if n is prime else false if n is composite */
bool MathUtil::millerTest(int d, int n)
{
	// Pick a random number in [2..n-2] 
	// Corner cases make sure that n > 4 
	int a = 2 + rand() % (n - 4);

	// Compute a^d % n 
	int x = MathUtil::power(a, d, n);

	if (x == 1 || x == n - 1)
		return true;

	// Keep squaring x while one of the following doesn't 
	// happen 
	// (i)   d does not reach n-1 
	// (ii)  (x^2) % n is not 1 
	// (iii) (x^2) % n is not n-1 
	while (d != n - 1)
	{
		x = (x * x) % n;
		d *= 2;

		if (x == 1)      return false;
		if (x == n - 1)    return true;
	}

	// Return composite 
	return false;
}
/* This function tests for primality using an implementation
of based on the Miller-Rabins Primality Test 
@param k is an input parameter that determines
accuracy level. Higher value of k indicates more accuracy.
@param n is the integer to be tested 
@return returns false if n is composite and returns true if n
is probably prime.   */
bool MathUtil::isPrimeMillerRabin(size_t n, int k)
{ 
    // Corner cases 
    if (n <= 1 || n == 4)  return false; 
    if (n <= 3) return true; 
  
    // Find r such that n = 2^d * r + 1 for some r >= 1 
	size_t d = n - 1;
    while (d % 2 == 0) 
        d /= 2; 
  
    // Iterate given number of 'k' times 
    for (int i = 0; i < k; i++) 
         if (!MathUtil::millerTest(d, n)) 
              return false; 
  
    return true; 
} 

bool
MathUtil::isPrime(std::size_t x)
{
	std::size_t o = 4;
	for (std::size_t i = 5; true; i += o)
	{
		std::size_t q = x / i;
		if (q < i)
			return true;
		if (x == q * i)
			return false;
		o ^= 6;
	}
	return true;
}

std::size_t
MathUtil::nextPrime(std::size_t x)
{
	switch (x)
	{
	case 0:
	case 1:
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
	case 5:
		return 5;
	}
	std::size_t k = x / 6;
	std::size_t i = x - 6 * k;
	std::size_t o = i < 2 ? 1 : 5;
	x = 6 * k + o;
	for (i = (3 + o) / 2; !isPrime(x); x += i)
		i ^= 6;
	return x;
}