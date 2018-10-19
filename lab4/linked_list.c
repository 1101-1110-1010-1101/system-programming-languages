#include <stdlib.h>
#include <stdio.h>

typedef struct element {
  struct element* prev;
  struct element* next;
  int value;
} element;

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

void print_list(element* list) {
  while (list != NULL) {
    printf("%d ", list->value);
    list = list->prev;
  }
  printf("\n");
}

int main(int argc, char const *argv[]) {
  int j = 0;
  element* list = NULL;
  printf("Введите элементы списка:\n");
  while (scanf("%d", &j) != EOF) {
    list = add_element(j, list);
  }
  list_add_back(19, &list);
  list_add_front(29, &list);
  print_list(list);
  return 0;
}