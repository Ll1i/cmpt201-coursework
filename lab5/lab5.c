#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  // TODO: Implement best fit
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // TODO: Implement worst fit
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}

/*
Part 2
when a block is freed, merge it with adjacent free blocks in memory to avoid
fragmentation

FREE_AND_COALESCE(free_list_head, newly_freed_block):
  1) Insert newly_freed_block into the free list
    If list is empty: head = newly_freed_block; return
    Otherwise: find insertion position by comparing addresses

  2) Coalesce with next if contiguous:
     curr = newly_freed_block
     next = curr->next
     if next != NULL AND end(curr) == (char*)next:
        curr->size = curr->size + sizeof(struct header) + next->size
        curr->next = next->next

  3) Coalesce with previous if contiguous:
     prev = node right before curr in the list (if any)
     if prev != NULL AND end(prev) == (char*)curr:
        prev->size = prev->size + sizeof(struct header) + curr->size
        prev->next = curr->next
        curr = prev

  4) After merging, re-check merge with curr->next:
     next = curr->next
     if next != NULL AND end(curr) == (char*)next:
        merge again
*/
