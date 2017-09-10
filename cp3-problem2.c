
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/**
 * The list elements
 */
struct double_linked_list_element_s;

typedef struct double_linked_list_element_s {
  struct double_linked_list_element_s *prev;
  struct double_linked_list_element_s *next;
  int i;
  char *v;
} double_linked_list_element;

/**
 * The list itself
 */
typedef struct double_linked_list_s {
  double_linked_list_element *head;
} double_linked_list;

double_linked_list *make_list();
int size(double_linked_list *list);
void delete_list(double_linked_list *list);
int add_element(double_linked_list *list, int i, char *string);
int delete_element(double_linked_list *list, int i);
char *lookup_element(double_linked_list *list, int i);
void print_list(double_linked_list *list);

int main(int argc, char **argv) {
  double_linked_list *list = make_list();

  int i;
  for (i=1; i<argc; i++) {
    char *arg = argv[i];
    switch (arg[0]) {
      case 'a': {
        int i;
        char *v = (char*) malloc(strlen(arg));

        sscanf(arg, "a %d %[A-Z-a-z]", &i, v);

        int result = add_element(list, i, v);
        if (result == 1) printf("Adding %d overwrite old value.\n", i);
        }
        break;
      case 'r': {
        int i;

        sscanf(arg, "r %d", &i);

        int result = delete_element(list, i);
        if (result == 0) printf("Err: Element %d not found.\n", i);
        }
        break;
      case 'l': {
        int i;

        sscanf(arg, "l %d", &i);

        char *result = lookup_element(list, i);
        if (result == NULL) printf("Err: Element %d not found.\n", i);
        else printf("Element %d is '%s'\n", i, result);
        }
        break;
      default: {
        printf("Error: Unknown command '%c'.\n", arg[0]);
        return -1;
        }
     }

     print_list(list);
  }

  delete_list(list);

  return 0;
}

/**
 * This function should allocate a new list structure (via malloc)
 * and return it.  Later, this list should be delete-able via 
 * the delete_list function.
 */
double_linked_list *make_list() {
  double_linked_list *list = (double_linked_list *) malloc(sizeof(double_linked_list));
  list->head = NULL;
  return list;
}

/**
 * This function should delete a previously allocated list.  If
 * the list has any elements in it, the function should first
 * delete all the elements (freeing the memory associated with them)
 * before freeing the list itself.
 */
void delete_list(double_linked_list *list) {
  while (size(list) > 0) 
    delete_element(list, list->head->i);
  
  free(list);
}

/**
 * This function should return the number of elements present in
 * the list.
 */
int size(double_linked_list *list) {
  // Should return the number of elements in the list
  double_linked_list_element *pHead = list->head;
  int size = 0;
  while (pHead != NULL) {
	  size++;
	  pHead = pHead->next;
  }

  return size; 
}

/**
 * This function should add the given element to the provided
 * list.  Note that you *must* create a copy of the string for
 * use in the list (i.e., the caller is allowed to delete/overwrite
 * the string after this function returns).  If the list already
 * has an element with the given int value, you should delete
 * that element and overwrite it with the new value.
 *
 * **You should store the elements in the list in numerical order 
 *   based on the ints, from lowest to highest.**
 *
 * You should return 0 if the element did not exist previously,
 * or 1 if the element did exist previously and you overwrite it.
 */
int add_element(double_linked_list *list, int i, char *string) {

  double_linked_list_element *pHead = list->head;
  /// insert as head
  if (pHead==NULL){
	  double_linked_list_element *pAdd = (double_linked_list_element *)malloc(sizeof(double_linked_list_element));
	  pAdd->i = i;
	  pAdd->v = (char*)malloc(sizeof(char)*260);
	  strcpy(pAdd->v, string);
	  list->head = pAdd;
	  return 0;
  }
  int szList = size(list);

  if (szList==1)
  {
	  if (pHead->i>i)
	  {       
		  double_linked_list_element *pAdd = (double_linked_list_element *)malloc(sizeof(double_linked_list_element));
		  pAdd->i = i;
		  pAdd->v = (char*)malloc(sizeof(char)*260);
		  strcpy(pAdd->v, string);
		  pAdd->next = pHead;
		  pHead->prev = pAdd;
		  list->head = pAdd;
		  return 0;
	  }
	  if (pHead->i==i)
	  {
		free(pHead->v);
		pHead->v = (char*)malloc(sizeof(char)*260);
		strcpy(pHead->v, string);
		return 1; 
	  }  
	  else //(pHead->i<i)
	  {      
		  double_linked_list_element *pAdd = (double_linked_list_element *)malloc(sizeof(double_linked_list_element));
		  pAdd->i = i;
		  pAdd->v = (char*)malloc(sizeof(char)*260);
		  strcpy(pAdd->v, string);	
		  pHead->next = pAdd;
		  pAdd->prev = pHead;
		  return 0;
	  }
  }

  double_linked_list_element *pNext = (double_linked_list_element *)malloc(sizeof(double_linked_list_element));
  while (pHead->next != NULL)
  {
	  pNext = pHead->next;
	  if (pNext->i==i)
	  {
		  free(pNext->v);
		  pNext->v = (char*)malloc(sizeof(char)*260);
		  strcpy(pNext->v, string);
		  return 1;
                  break; 
	  }
	  if (pNext->i>i)
	  {       
		  double_linked_list_element *pAdd = (double_linked_list_element *)malloc(sizeof(double_linked_list_element));
		  pAdd->i = i;
		  pAdd->v = (char*)malloc(sizeof(char)*260);
		  strcpy(pAdd->v, string);
		  pAdd->next = pHead->next;
		  pHead->next->prev = pAdd;
		  pHead->next =  pAdd;
		  pAdd->prev = pHead;
		  return 0;
                  break;
	  }
	  pHead=pNext;
  }
  /// be inserted as trail
  double_linked_list_element *pAdd = (double_linked_list_element *)malloc(sizeof(double_linked_list_element));
  pAdd->i = i;
  pAdd->v = (char*)malloc(sizeof(char)*260);
  strcpy(pAdd->v, string);
  pAdd->prev = pHead;
  pHead->next = pAdd;


  return 0;
}

/**
 * This function should delete the element in the list with 
 * the corresponding int value.  It should be sure to free() any
 * allocated memory.  It should return 0 if the element was not
 * found, and 1 if the element was found.
 */
int delete_element(double_linked_list *list, int i) {
  double_linked_list_element *pHead = list->head;
   double_linked_list_element *pNext= (double_linked_list_element *)malloc(sizeof(double_linked_list_element));
  int szList = size(list);

  if (pHead == NULL) {
  return 0; }  

  if (pHead->i==i)
  {
	  if (szList==1) {
		  list->head = NULL;
		  free(pHead->v);
		  free(pHead);
	  }
	  else {  list->head->next->prev = NULL;
		  list->head = pHead->next; 
		  free(pHead->v);
		  free(pHead);
	  }
	  return 1;
  }
  
  while(pHead->next != NULL)
  {
	  pNext = pHead->next;
	  if (pNext->i==i)
	  {	
		  if (szList==2) {
			  pHead->next= NULL;
			  free(pNext->v);
			  free(pNext);
		  }
		  else
		  {
			  pHead->next = pNext->next;
			  pNext->next->prev = pHead;
			  free(pNext->v);			  
			  free(pNext);
		  }
		  return 1;
	  }
	  pHead = pNext;
  } 
  return 0;
}

/**
 * This function should look up the given element in the list, and
 * shoudl return the correspoinding string value.  If the element is
 * found, it should return the list's copy of the string (e.g., the
 * caller is *not* expected to change or free() the string).  If
 * the element is not found, it should return NULL.
 */
char *lookup_element(double_linked_list *list, int i) {
  double_linked_list_element *pHead = list->head;
  while (pHead != NULL) { 
	  if(pHead->i==i) {
            char *a = (char*)malloc(sizeof(char)*260);
             strcpy(a, pHead->v);

		  return a; }
          pHead = pHead->next;
  }

  return NULL;
}

/**
 * Prints out the list as a utility function. Do not modify this
 * function, but you're welcome to use it during debugging.
 */
void print_list(double_linked_list *list) {
  printf("[");

  double_linked_list_element *e = list->head;
  
  while (e != NULL) {
    printf(" {%d, '%s'}", e->i, e->v);
    e = e->next;
  }

  printf(" ]\n");
}
 


