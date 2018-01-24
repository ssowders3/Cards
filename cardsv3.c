#include <stdio.h>  // printf

unsigned long long gcd(unsigned long long a, unsigned long long b);
unsigned long long lcm(unsigned long long a, unsigned long long b);
unsigned long long rounds(int n);
static unsigned count(unsigned deck, unsigned card);
unsigned next_pos(unsigned num_cards, unsigned pos);

/* next_pos() finds the next position of the card in deck */
unsigned next_pos(unsigned num_cards, unsigned pos) {
  if (pos & 1) {
    unsigned diff = num_cards - (pos >> 1) - 1;
    do { 
    	pos += diff;
    	diff = diff >> 1; 
    } while (pos & 1);
  }
  unsigned toReturn = num_cards - 1 - (pos >> 1);
  return toReturn;
}

/* 
* count() computes the number of rounds of an element in a deck size
* or returns 0 if element is not the smallest element in the cycle 
*/
static unsigned count(unsigned deck, unsigned card) {
  unsigned count = 1;
  unsigned i = next_pos(deck, card);
  while (i > card) {
    i = next_pos(deck, i);
    ++count;
  }
  if (i == card) {
  	return count;
  } else {
  	return 0;
  }
}

/*
* rounds() computes the length of the permutation for deck size n 
*/
unsigned long long rounds(int n) {
  unsigned long long toReturn = count(n, 0);
  unsigned j = 1;
  while (j < n) {
    unsigned c = count(n, j);
    if (c) {
    	toReturn = lcm(toReturn, c);
    }
    ++j;
  }
  return toReturn;
}

/*
* lcm() Computes the least-common multiple by reducing by
* the greatest common divisor using the Euclidean 
* algorithm to compute the gcd.
*/
unsigned long long gcd(unsigned long long a, unsigned long long b) {
	while (b){
		a %= b;
		b ^= a;
		a ^= b;
		b ^= a;
	}
	return a;
}

unsigned long long lcm(unsigned long long a, unsigned long long b) {
	return ((unsigned long long) a * b) / gcd(a, b);
}

int main() {
  unsigned int deckSize = 0;
  scanf("%d", &deckSize);
  unsigned int numRounds = rounds(deckSize);
  printf("rounds for %d numbers = %d\n", deckSize, numRounds);
  return 0;
}