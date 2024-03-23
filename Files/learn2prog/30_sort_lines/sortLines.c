#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function is used to figure out the ordering
// of the strings in qsort.  You do not need
// to modify it.
int stringOrder(const void *vp1, const void *vp2) {
  const char *const *p1 = vp1;
  const char *const *p2 = vp2;
  return strcmp(*p1, *p2);
}
// This function will sort and print data (whose length is count).
void sortData(char **data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void print_lines(char **data, size_t count) {
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}

void read_lines(FILE *f) {
  char **lines = NULL;
  char *curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  print_lines(lines, i);
}

int main(int argc, char **argv) {
  // WRITE YOUR CODE HERE!
  if (argc == 1) {
    read_lines(stdin);
    return EXIT_SUCCESS;
  }

  for (size_t i = 1; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "Could not open file.\n");
      return EXIT_FAILURE;
    }
    read_lines(f);
    if (fclose(f) != 0) {
      fprintf(stderr, "Could not close file.\n");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
