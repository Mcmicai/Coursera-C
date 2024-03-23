#include <stdio.h>
#include "counts.h"
#include <stdlib.h>
#include <string.h>

counts_t* createCounts(void) {
  // WRITE ME
  counts_t* c = malloc(sizeof(*c));
  c->num_counts = 0;
  c->num_unknown = 0;
  c->counts = NULL;
  return c;
}

void addCount(counts_t* c, const char* name) {
  // WRITE ME
  if (name == NULL) {
    c->num_unknown++;
    return;
  }

  for (size_t i = 0; i < c->num_counts; i++) {
    if (strcmp(c->counts[i]->content, name) == 0) {
      c->counts[i]->count++;
      return;
    }
  }

  one_count_t* one_count = malloc(sizeof(*one_count));
  one_count->content = malloc((strlen(name) + 1) * sizeof(char));
  strcpy(one_count->content, name);
  one_count->count = 1;

  c->counts = realloc(c->counts, (c->num_counts + 1) * sizeof(one_count_t*));
  c->counts[c->num_counts] = one_count;
  c->num_counts++;
}

void printCounts(counts_t* c, FILE* outFile) {
  // WRITE ME
  for (size_t i = 0; i < c->num_counts; i++) {
    fprintf(outFile, "%s: %d\n", c->counts[i]->content, c->counts[i]->count);
  }

  if (c->num_unknown > 0) {
    fprintf(outFile, "<unknown>: %d\n", c->num_unknown);
  }
}

void freeCounts(counts_t* c) {
  // WRITE ME
  for (size_t i = 0; i < c->num_counts; i++) {
    free(c->counts[i]->content);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}
