/* * C Bootcamp, Homework 2, Problem 3
 * (c) 2012 Alan Mislove
 *
 * In this problem, your goal is to learn about strings (character arrays).
 * You should fill in the functions below, as described, and be sure to
 * not touch anything in the main() function.
 *
 * Also note that you may not use any of the functions provided by <string.h>;
 * you must do all of the string manipulation yourself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_cat(char *str1, char *str2, char *dst);
int count_lowercase(char *str);
void reverse(char *str);

int main(int argc, const char **argv) {
  // check for the right number of arguments
  if (argc != 3) {
    printf("Error: Usage: ./cp2-problem3 [str1] [str2]\n");
    return 0;
  }

  char *str1 = (char *) argv[1];
  char *str2 = (char *) argv[2];
  char *str3 = (char *) malloc(strlen(argv[1])+strlen(argv[2])+1);

  str_cat(str1, str2, str3);
  printf("The concatenation is: %s\n", str3);

  int t = count_lowercase(str3);
  printf("There are a total of %d lowercase characters.\n", t);

  reverse(str3);
  printf("The reverse is: %s\n", str3);
}

/**
 * This function takes in three char*s, and should concatenate the
 * first two and store the result in the third.  For example, if the
 * value of str1 is "foo" and str2 is "bar", you should store the
 * string "foobar" into dst.  Be careful about the trailing \0s.  
 * You can assume that dst has sufficient space for the result (but
 * no more).
 */
void str_cat(char *str1, char *str2, char *dst) {
  // TODO: Delete the line below and fill in this functiin.
  while(*str1 != '\0') {
    *dst = *str1;
    str1++;
    dst++;
  }

  while (*str2) {
    *dst =*str2;
    str2++;
    dst++;
  }
  *dst = '\0';
}

/**
 * This function should count the number of lowercase letters ('a' .. 'z') 
 * that occur in the argument and return the result.
 */
int count_lowercase(char *str) {
  // TODO: Fill in this function
  int lower = 0;
  while(*str) { 
    if (*str >= 'a' && *str <= 'z') {
      lower++;
    }
    str++;
  }
  return lower;
}

/**
 * This function should reverse the string argument *in-place*.  In other
 * words, you should change the characters in str so that they are in the 
 * reverse order.
 */
void reverse(char *str) {
  // TODO: Fill in this function  
  char temp;
  char* end;
  end = str + strlen(str)-1;

  while(end>str){
    temp = *end;
    *end = *str;
    *str = temp;
    end--;
    str++;
  } 
}










