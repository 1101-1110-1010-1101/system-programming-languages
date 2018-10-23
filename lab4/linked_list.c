#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "linked_list.h"

element* create_list(int el) {
  element* curr_el = (element*)malloc(sizeof(element));
  curr_el->prev = NULL;
  curr_el->next = NULL;
  curr_el->value = el;
  return curr_el;
}

element* add_element(int el, element* list) {
  if (list == NULL) { return create_list(el); }
  element* new_el = (element*)malloc(sizeof(element));
  new_el->value = el;
  new_el->prev = list;
  new_el->next = NULL;
  list->next = new_el;
  return new_el;
}

void list_add_back(int el, element** list) {
  if (*list == NULL) {
    *list = create_list(el);
    return;
  }
  element* new_el = (element*)malloc(sizeof(element));
  new_el->value = el;
  new_el->prev = (*list);
  new_el->next = NULL;
  (*list)->next = new_el;
  *list = new_el;
}

void list_add_front(int el, element** list) {
  element* old_list = *list;
  while ((*list)->prev != NULL) {
    *list = (*list)->prev;
  }
  element* new_el = (element*)malloc(sizeof(element));
  new_el->value = el;
  new_el->next = *list;
  new_el->prev = NULL;
  (*list)->prev = new_el;
  *list = old_list; 
}

void list_add_by_index(int el, element** list, int index) {
  element* new_el = (element*)malloc(sizeof(element));
  element* old_at_index = list_node_at(index, *list);
  new_el->next = old_at_index->next;
  new_el->prev = old_at_index;
  old_at_index->next = new_el;
}

void delete_back(element** list) {
  element* new_last = (*list)->prev;
  new_last->next = NULL;
  free(*list);
  *list = new_last;
}

void list_free(element** list) {
  element* temp_list = NULL;
  while ((*list)->prev != NULL) {
    temp_list = (*list)->prev;
    free(*list);
    *list = temp_list;
  }
  *list = NULL;
}

void print_list(element* list) {
  if (list == NULL) {
    printf("Soory, I'm running out of elements\n");
    return;
  }
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    printf("%d ", list->value);
    list = list->next;
  }
  printf("\n");
}

int list_length(element* list) {
  int i = 0;
  element* old_list = list;
  while (list != NULL) {
    i++;
    list = list->prev;
  }
  list = old_list;
  return i;
}

int list_sum(element* list) {
  int sum = 0;
  while (list != NULL) {
    sum += list->value;
    list = list->prev;
  }
  return sum;
}

void from_stdin(element** list) {
  printf("Введите элементы списка:\n");
  int j = 0;
  int el;
  while ((el = scanf("%d", &j)) != EOF) {
    if (el != 1)
      printf("Cant interpret as int: %c\n", getchar());
    else
      list_add_back(j, list);
  }
}

bool load(element** list, char* file) {
  FILE *f = fopen(file, "r");
  int e = 0;
  if (f == NULL) {
    return false;
  }
  while (fscanf(f, "%d", &e) != EOF) {
    list_add_back(e, list);
  }
  fclose(f);
  return true;
}

element* list_node_at(int index, element* list) {
  int i = 0;
  if (list == NULL) {
    printf("Soory, I'm running out of elements\n");
    return NULL;
  }
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    if (i == index)
      return list;
    list = list->next;
    i++;
  }
  return NULL;
}

int list_get(int index, element* list) {
  element* result = list_node_at(index, list);
  return result == NULL ? 0 : result->value;
}

void foreach(element* list, void (*fun) (int)) {
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    fun(list->value);
    list = list->next;
  }
}

void print_with_newline(int el) {
  printf("%d\n", el);
}

void print_with_space(int el) {
  printf("%d ", el);
}

element* map(element* list, int (*fun) (int)) {
  element* new_list = NULL;
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    list_add_back(fun(list->value), &new_list);
    list = list->next;
  }
  return new_list;
}

int square(int a) {return a*a;}
int cube(int a) {return a*a*a;}

int foldl(element* list, int acc, int (*fun)(int a, int b)) {
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    acc = fun(acc, list->value);
    list = list->next;
  }
  return acc;
}

int sum(int a, int b) {return a + b;}
int min(int a, int b) {return a >= b? b: a;}
int max(int a, int b) {return a >= b? a: b;}

void map_mut(element* list, int (*fun) (int)) {
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    list->value = fun(list->value);
    list = list->next;
  }
}

element* iterate(int first, int amount, int (*fun)(int)) {
  int acc = first;
  element* new_list = NULL;
  for (int i = first; i < (first + amount); i++) {
    list_add_back(acc, &new_list);
    acc = fun(acc);
  }
  return new_list;
}

int mul_by_two(int a) {return 2 * a;}

int abs(int a) {return a < 0? -a: a;}

bool save(element* list, const char* filename) {
  FILE* file = fopen(filename, "w+");
  if (file == NULL) {return false;}
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    fprintf(file, "%d ", list->value);
    list = list->next;
  }
  fclose(file);
  return true;
}

bool serialize(element* list, const char* filename) {
  FILE *file = fopen(filename, "w+");
  int i = 0;
  if (file == NULL)
    return false;
  size_t list_size = list_length(list);
  int* buffer = (int*)malloc(list_size * sizeof(int));
  while (list->prev != NULL) 
    list = list->prev;
  while (list != NULL) {
    buffer[i] = list->value;
    list = list->next;
    i++;
  }
  fwrite(buffer, list_size, sizeof(int), file);
  fclose(file);
  return true;
}

bool deserialize(element** list, const char* filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL)
    return false;
  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  rewind(file);
  int i = 0;
  int* buffer = (int*)malloc(filesize);
  fread(buffer, filesize/sizeof(int), sizeof(int), file);
  for (i = 0; i < filesize / sizeof(int); i++){
    list_add_back(buffer[i], list);
  }
  fclose(file);
  return true;
}