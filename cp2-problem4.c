

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// you may need to change this definition as well
void swap(char **a, char **b);

int main(int argc, const char **argv) {
  // check for the right number of arguments
  if (argc != 3) {
    printf("Error: Usage: ./cp2-problem3 [str1] [str2]\n");
    return 0;
  }

  char *str1 = (char *) malloc(strlen(argv[1])+1);
  strcpy(str1, argv[1]);

  char *str2 = (char *) malloc(strlen(argv[2])+1);
  strcpy(str2, argv[2]);

  swap(&str1,&str2);

  printf("The swapped values are: %s %s\n", str1, str2);
}

// swap them
void swap(char **a, char **b) {
  char *temp = *b;
  *b = *a;
  *a = temp;
}
