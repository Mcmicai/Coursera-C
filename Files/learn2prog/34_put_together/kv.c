#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t* convertKV(char* line) {
  kvpair_t* kv;
  kv = malloc(sizeof(*kv));

  char* left = strtok(line, "=");
  char* right = strtok(NULL, "\n");
  kv->key = malloc((strlen(left) + 1) * sizeof(char));
  kv->val = malloc((strlen(right) + 1) * sizeof(char));
  strcpy(kv->key, left);
  strcpy(kv->val, right);

  return kv;
}

kvarray_t* readKVs(const char* fname) {
  // WRITE ME
  FILE* f = fopen(fname, "r");
  kvpair_t** kvs = NULL;
  char* curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    kvs = realloc(kvs, (i + 1) * sizeof(*kvs));

    kvs[i] = convertKV(curr);
    free(curr);
    curr = NULL;
    i++;
  }
  free(curr);

  kvarray_t* kvarray = malloc(sizeof(*kvarray));
  kvarray->kvs = kvs;
  kvarray->num_kvs = i;

  if (fclose(f) != 0) {
    fprintf(stderr, "Could not close file\n");
    return NULL;
  }

  return kvarray;
}

void freeKVs(kvarray_t* pairs) {
  // WRITE ME
  for (size_t i = 0; i < pairs->num_kvs; i++) {
    free(pairs->kvs[i]->key);
    free(pairs->kvs[i]->val);
    free(pairs->kvs[i]);
  }
  free(pairs->kvs);
  free(pairs);
}

void printKVs(kvarray_t* pairs) {
  // WRITE ME
  for (size_t i = 0; i < pairs->num_kvs; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvs[i]->key, pairs->kvs[i]->val);
  }
}

char* lookupValue(kvarray_t* pairs, const char* key) {
  // WRITE ME
  for (size_t i = 0; i < pairs->num_kvs; i++) {
    if (strcmp(key, pairs->kvs[i]->key) == 0) {
      return pairs->kvs[i]->val;
    }
  }
  return NULL;
}
