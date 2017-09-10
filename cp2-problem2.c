/*
   The goal is to learn about C structures.  we will
 * be mananging employee records.  Each employee record consists of 
 * the following values:
 *
 *  - A name string (less than 49 chars long)
 *  - A salary (integer, positive, less than $4B)
 *  - A employee ID (integer, positive, less than 4B)
 *  - A location string (less than 49 chars long)
 *
 * we are guaranteed that there will be no more than 10 employees. we
 * should support 10, and exactly 10, employees.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_employee(char *name, unsigned int id, unsigned int salary, char *location);
int remove_employee(unsigned int id);
int get_salary(unsigned int id);

int main(int argc, char **argv) {
  int i;
  for (i=1; i<argc; i++) {
    char *arg = argv[i];
    switch (arg[0]) {
      case 'a': {
        char *name = (char*) malloc(100);
        unsigned int salary;
        unsigned int id;
        char *location = (char*) malloc(100);

        sscanf(arg, "a %[A-Z-a-z] %u %u %[A-Z-a-z]", name, &id, &salary, location);

        int result = add_employee(name, id, salary, location);
        if (result == -1) printf("Err: Employee name already exists.\n");
        if (result == -2) printf("Err: Employee id already exists.\n");
        if (result == -3) printf("Err: Too many employees!\n");
        }
        break;
      case 'r': {
        unsigned int id;

        sscanf(arg, "r %u", &id);

        int result = remove_employee(id);
        if (result == -1) printf("Err: Employee %d not found.\n", id);
        }
        break;
      case 's': {
        unsigned int id;

        sscanf(arg, "s %u", &id);

        int result = get_salary(id);
        if (result == -1) printf("Err: Employee %d not found.\n", id);
        else printf("Salary of %d: %d\n", id, result);
        }
        break;
      default: {
        printf("Error: Unknown command '%c'.\n", arg[0]);
        return -1;
        }
    }
  }

  return 0;
}

//Define employee structure
typedef struct employee1 {
char name[260];
unsigned int id;
unsigned int salary;
char location[260];
} employee;



//Define global storage location for employees
employee employees[10];
unsigned int i;

/**
 * This function should add an employee to the list.  The passed-in arguments
 * describe the employee.  we should add the employee and return one of the following
 * values:
 *   0 - success
 *  -1 - if an employee with an identical name already exists
 *  -2 - if an employee with an identical ID aleady exists
 *  -3 - if there is no more space
 */
int add_employee(char *name, unsigned int id, unsigned int salary, char *location) {
  // Fill in this function
//checking space
  if(i >= 10) {
    return -3; }
//checking existing name
  int findName = -1;
  for (int j=0; j<i; j++) {
    if (!strcmp(employees[j].name, name)) {
      findName = j;
    }
  }
  if(findName != -1) {
    return -1; }

//checking existing ID
  int findId = -1;
  for (int k=0; k<i; k++) {
    if (employees[k].id == id) {
      findId = k;
    }
  }
  if(findId != -1) {
    return -2; }

  employees[i].id = id;
  employees[i].salary= salary;
  strcpy(employees[i].name, name);
  strcpy(employees[i].location, location);
  i++;
  return 0;
}

/**
 * This function should remove an existing employee from the list, based on the
 * provided ID.  we should return one of the following values:
 *  0 - success
 * -1 - if employee was not found
 */
int remove_employee(unsigned int id) {
  // Fill in this function
  //checking existing id
  int findId = -1;
  for (int j=0; j<i; j++) {
    if (employees[j].id == id) {
      findId = j;
    }
  }
  if(findId < 0) {
    return -1;}
 
  i--;
  for (int k=findId; k<i; k++) {
    employees[k].id = employees[k+1].id;
    employees[k].salary = employees[k+1].salary;
    strcpy(employees[k].name, employees[k+1].name);
    strcpy(employees[k].location, employees[k+1].location); 
  }  
  return 0;
}

/**
 * This function should look up the salary of the employee assigned the given ID,
 * and return the corresponding value. You should return one of the following values:
 * >= 0 - success, the salary value
 *   -1 - if employee was not found
 */
int get_salary(unsigned int id) {
  // Fill in this function
   //checking existing id
  int findId = -1;
  for (int j=0; j<i; j++) {
    if (employees[j].id == id) {
      findId = j;
    }
  }
  if(findId == -1) {
    return findId; }

  else {
    return employees[findId].salary; }
}

