/*
 * 0 -> "zero"
 * 9 -> "nine"
 * 45 -> "forty five"
 * -130 -> "negative one hundred thirty"
 * 11983 -> "eleven thousand nine hundred eighty three"
 *
 *
 */

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char *itoaaa(int i);
void hundreds(int n, char* eng);

int main(int argc, char **argv) {
  // check for the right number of arguments
  if (argc != 2) {
    printf("Error: Usage: ./cp3-problem1 [int]\n");
    return 0;
  }

  // create the time structure
  long long arg = atol(argv[1]);
  if (arg == (int) arg) {
    // call the function
    char *result = itoaaa((int) arg);

    // print out the result
    printf("%d is: %s\n", (int) arg, result);
  } else {
    printf("Error: Number out of range.\n");
  }

  return 0;
}

// Global defs
char* pNums[] = {"","one","two","three","four","five","six","seven","eight","nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen","eighteen", "nineteen"};
char* pTen[] = {"","", "twenty","thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};


//helper for 3 digits
void hundreds(int n, char *eng) {
	int rHundred = n / 100;
	n = n - rHundred*100;

	int rTen = n /10;
	n = n - rTen*10;
      
	sprintf(eng, "%s%s%s%s%s", 
			pNums[rHundred], rHundred>0?" hundred ":"", 
			rTen>=2?pTen[rTen]:"", rTen>=2?" ":"",
			rTen>=2?pNums[n]:(rTen==1?pNums[n+10]:pNums[n]));
}
	
/**
 * This function should print out the English full representation
 * of the passed-in argument.  See above for more details.
 */
/*
 *	For singned int, it ranges from -2147483648~2147483647
 */
char *itoaaa(int arg) {
  int neg = 0;                  
  if(arg<0){
	  arg = -arg;
	  neg = 1;
  }
  char Billion[260];
  char Million[260];
  char Thousand[260];
  char rest[260];
  char Total[260];

  /// billion less than one hundred
  int rBillion = arg/1000000000;
  arg = arg - rBillion * 1000000000;
  hundreds(rBillion, Billion);

  int rMillion = arg/1000000;
  arg = arg - rMillion*1000000;
  hundreds(rMillion, Million);

  int rThousand= arg/1000;
  arg = arg - rThousand*1000;
  hundreds(rThousand, Thousand);

  hundreds(arg, rest);
  
  sprintf(Total, "%s%s%s%s%s%s%s%s", neg?"negative ":"", Billion, rBillion>0?" billion ":"", 
		  Million, rMillion>0?" million ":"", 
		  Thousand, rThousand>0?" thousand ":"", rest);
  
  char* r = (char*)malloc(strlen(Total));
  if (arg == 0) {
    sprintf(Total, "zero"); }
  strcpy(r, Total);
  return r;
}
