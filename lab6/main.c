#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdbool.h>

#define MIN_QUERY_SIZE 8
#define INIT_BLOCK_SIZE 4096

typedef struct block_header block_header;
char* start;

struct __attribute__((packed)) block_header {
  block_header* next;
  size_t capacity;
  bool is_free;
};

block_header* init() {
  start = mmap(NULL, INIT_BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
  block_header* header = (block_header*)start;
  header->next = NULL;
  header->capacity = INIT_BLOCK_SIZE;
  header->is_free = true;
  return header;
}

void* customalloc(size_t query) {
  if (query < MIN_QUERY_SIZE)
    query = MIN_QUERY_SIZE;
  block_header* header = (block_header*)start;
  while (header->is_free == false || header->capacity < query) {
    header = header->next;
    if (header == NULL) {
      header = init();
      break;
    }
  }
  header->is_free = false;
  // so, next step - we need to transfer remaining space to another block
  if (header->capacity - query >= MIN_QUERY_SIZE + sizeof(block_header)) {
    block_header* new_header = (block_header*)((uint8_t*)header + query + sizeof(block_header));
    new_header->capacity = header->capacity - query - sizeof(block_header);
    new_header->is_free = true;
    printf("size of new header = %ld\n", new_header->capacity);
    header->next = new_header;
  }
  return (void*)((uint8_t*)header + sizeof(block_header));
}

int main() {
  block_header* header = init();
  void* smth = customalloc(4000);
  void* smth_else = customalloc(1000);
  return 0;
}
