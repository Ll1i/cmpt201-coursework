#define _DEFAULT_SOURCE

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

int main(void) {
  const uint64_t EXTRA_SIZE = 256;
  const uint64_t BLOCK_SIZE = 128;

  void *base = sbrk((intptr_t)EXTRA_SIZE);
  if (base == (void *)-1) {
    perror("sbrk");
    return 1;
  }

  struct header *first = (struct header *)base;
  struct header *second = (struct header *)((char *)base + BLOCK_SIZE);

  first->size = BLOCK_SIZE;
  first->next = NULL;

  second->size = BLOCK_SIZE;
  second->next = first;

  unsigned char *first_data = (unsigned char *)(first + 1);
  unsigned char *second_data = (unsigned char *)(second + 1);

  uint64_t data_bytes = BLOCK_SIZE - (uint64_t)sizeof(struct header);

  memset(first_data, 0, (size_t)data_bytes);
  memset(second_data, 1, (size_t)data_bytes);

  printf("first block:       %p\n", (void *)first);
  printf("second block:      %p\n", (void *)second);

  printf("first block size:  %" PRIu64 "\n", first->size);
  printf("first block next:  %p\n", (void *)first->next);
  printf("second block size: %" PRIu64 "\n", second->size);
  printf("second block next: %p\n", (void *)second->next);

  for (uint64_t i = 0; i < data_bytes; i++) {
    printf("%u\n", (unsigned)first_data[i]);
  }
  for (uint64_t i = 0; i < data_bytes; i++) {
    printf("%u\n", (unsigned)second_data[i]);
  }

  return 0;
}
