#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#define FLAG_FILE 1

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
  while (scanf("%d", &j) != EOF)
    list_add_back(j, list);
}

void load_from_file(element** list, char* file) {
  FILE *f = fopen(file, "r");
  int e = 0;
  if (f == NULL) {
    fprintf(stderr, "File not found!\n");
  }
  while (fscanf(f, "%d", &e) != EOF) {
    list_add_back(e, list);
  }
}

int main(int argc, char *argv[]) {
  // Checking flags section
  int flags = 0, opt = 0;
  char* file = NULL;
  while ((opt = getopt(argc, argv, "f:")) != -1) {
    switch (opt) {
      case 'f':
        flags |= FLAG_FILE;
        file = optarg;
        break;
      default:
        fprintf(stderr, "Usage: %s [-f]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  // List init section
  element* list = NULL;
  if (flags & FLAG_FILE) {
    load_from_file(&list, file);
    printf("Succesfully loaded from %s\n", file);
  }
  else
    from_stdin(&list);
  // Display list summary section
  printf("\nList info:\n");
  printf("list_length = %d\n", list_length(list));
  printf("list_sum = %d\n", list_sum(list));
  printf("contents: ");
  print_list(list);
  printf("\n");
  // Testing features section
  list_add_back(19, &list);
  list_add_front(29, &list);
  printf("list_length = %d\n", list_length(list));
  print_list(list);
  printf("Clear list...\n");
  list_free(&list);
  print_list(list);

  return 0;
}