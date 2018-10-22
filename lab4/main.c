#include <stdio.h>
#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include "linked_list.h"
#define FLAG_FILE 1

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
    load(&list, file);
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
  printf("list_add_back 19\n");
  list_add_back(19, &list);
  print_list(list);
  printf("\nlist_add_front 29\n");
  list_add_front(29, &list);
  print_list(list);
  printf("\nlist_length = %d\n", list_length(list));
  printf("\nlist_get\n");
  printf("list[0] = %d\n", list_get(0, list));
  printf("list[4] = %d\n", list_get(4, list));
  printf("\nTesting High-Order Functions\n");
  printf("\nLets print our list elements with foreach (newlines)\n");
  foreach(list, *print_with_newline);
  printf("\nLets print our list elements with foreach (spaces)\n");
  foreach(list, *print_with_space);
  printf("\n\nLets square every element using map\n");
  foreach(map(list, *square), *print_with_space);
  printf("\n\nLets cube every element using map\n");
  foreach(map(list, *cube), *print_with_space);
  printf("\n\nLets get the sum of list using foldl\n");
  printf("sum = %d\n", foldl(list, 0, *sum));
  printf("\nLets find min and max element using foldl\n");
  printf("min = %d", foldl(list, INT_MAX, *min));
  printf("\nmax = %d", foldl(list, INT_MIN, *max));
  printf("\n\nLets abs every element using map_mut\n");
  map_mut(list, *abs);
  foreach(list, *print_with_space);
  printf("\n\nThe list of the first 10 powers of two using iterate\n");
  foreach(iterate(1, 10, *mul_by_two), *print_with_space);
  printf("\nLets save our list to the output.txt\n");
  save(list, "output.txt");
  printf("\nLets serialize our list to serialized.txt\n");
  serialize(list, "serialized.txt");
  printf("\nLets deserialize our list\n");
  list_free(&list);
  deserialize(&list, "serialized.txt");
  foreach(list, *print_with_space);
  printf("\nClear list...\n");
  list_free(&list);
  print_list(list);

  return 0;
}