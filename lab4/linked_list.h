#ifndef _LINKED_L_
#define _LINKED_L_

#include <stdlib.h>

typedef struct element element;

typedef struct element {
  struct element* prev;
  struct element* next;
  int value;
} element;

element* create_list(int el);

element* add_element(int el, element* list);

void list_add_back(int el, element** list);

void list_add_front(int el, element** list);

void list_free(element** list);

void print_list(element* list);

int list_length(element* list);

int list_sum(element* list);

void from_stdin(element** list);

bool load(element** list, char* file);

element* list_node_at(int index, element* list);

int list_get(int index, element* list);

void foreach(element* list, void (*fun) (int));

void print_with_newline(int el);

void print_with_space(int el);

element* map(element* list, int (*fun) (int));

int square(int a);

int cube(int a);

int foldl(element* list, int acc, int (*fun)(int a, int b));

int sum(int a, int b);

int min(int a, int b);

int max(int a, int b);

void map_mut(element* list, int (*fun) (int));

element* iterate(int first, int amount, int (*fun)(int));

int mul_by_two(int a);

int abs(int a);

bool save(element* list, const char* filename);

bool serialize(element* list, const char* filename);

bool deserialize(element** list, const char* filename);

#endif