Q1:

Algorithm Explanation

You are given a deck containing N cards.  While holding the deck:

1. Take the top card off the deck and set it on the table
2. Take the next card off the top and put it on the bottom of the deck
in your hand.
3. Continue steps 1 and 2 until all cards are on the table.  This is a
round.
4. Pick up the deck from the table and repeat steps 1-3 until the deck
is in the original order.

Write a program to determine how many rounds it will take to put a
deck back into the original order.  This will involve creating a data
structure to represent the order of the cards. Do not use an array.
This program should be written in C only. It should take a number of
cards in the deck as a command line argument and write the result to
stdout.  Please ensure the program compiles and runs correctly (no
pseudo-code).  This isn't a trick question; it should be fairly
straightforward.

I calculated the cycle groups, and then computed the least-common-multiple (LCM) of the lengths of the cycle groups by taking progress of the single card through permutations, and then specifying a incrementing count until we get back to the original location. I optimized this process by only counting cycles which start with their smallest element. Since every cycle has a unique smallest element, that will find every cycle once.

Q2:

A fellow developer has asked you to review the following code. Please
provide your feedback:

1.  char *GetErrorString( int x )
2.  {
3.      char errorString[20];
4.
5.      switch ( x )
6.      {
7.          case 0:
8.              errorString = "Success -- No error.";
9.              break;
10.         case 2:
11.             errorString = "Overflow!";
12.             break;
13.     }
14.
15.     errorString[19] = 0;
16.     return errorString;
17. }
18.
19. void main( void )
20. {
21.     int err = DoSomething();
22.     if ( err )
23.     {
24.         printf( "%s\n", GetErrorString( err ) );
25.     }
26. }

Code review:

1. Comments to char *GetErrorString( int x ):

Line 3: the function GetErrorString returns a local char array (in line 16), this is not allowed by the standard: char errorString[20];
  - Change to static char errorString[20] or you could also allocate the char array on the heap (using malloc), this should be followed by
  deallocation using free
  - initialize the declared errorString array: memset(&errorString, '\0', sizeof(errorString));
Line 8: the string assignment is wrong: errorString = "Success -- No error.";
  - Change to strcpy(errorString, "Success -- No error.")
Line 11: the string assignment is wrong: errorString = "Overflow!";
  - Change to strcpy(errorString, "Overflow!")
Line 13: you need to handle case default in the switch statement, this is not strictly required but helps reduce bugs and increase clarity
Line 15: remove line 15, we just initalized the errorString at the beginning
Line 16: return statement is wrong: return errorString;
  - Return the address of the char array: return &errorString[0];

2. Comments to void main( void ):

Line 21/22: DoSomething returns an error code, but calls GetErrorString only if the value err is not 0.
  - case 0 in GetErrorString will never be called
  	- either add a call or delete the case
  	- if case is deleted please change switch to if
  - case 1 in GetErrorString is not implemented, is this correct?
  	- if not please change case 2 to case 1
  - which error codes will DoSomething return? 
  	- please make DoSomething more clear, it would be helpful to change the name to something more meaningful

3. Comments on general spacing and comments

This is really up to what the team has as an implemented norm for code spacing and comments. I would ask to reduce the spaces above and below
the switch statement, and to add general comments. Usually its good to have a description at the top of what the code does, and comment above
functions to state what they do.