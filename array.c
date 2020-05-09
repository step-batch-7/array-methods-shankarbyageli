#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "array.h"

Array *create_array(int length) {
  Array *new_array = malloc(sizeof(Array));
  if(new_array == NULL) {
    return NULL;
  }
  new_array->length = length;
  new_array->array = length ? malloc(length * sizeof(int)) : NULL;
  return new_array;
}

Array *map(Array *src, Mapper mapper) {
  Array *mapped_array = create_array(src->length);
  if(mapped_array == NULL) {
    return NULL;
  }
  for(size_t i = 0; i < src->length; i++) {
    mapped_array->array[i] = (*mapper)(src->array[i]);
  }
  return mapped_array;
}

Array *filter(Array *src, Predicate predicate) {
  int temp[src->length];
  int filtered_array_index = 0;
  for(size_t i = 0; i < src->length; i++) {
    Bool result = (*predicate)(src->array[i]);
    if(result) {
      temp[filtered_array_index] = src->array[i];
      filtered_array_index++;
    }
  }
  Array *filtered_array = create_array(filtered_array_index);
  if(filtered_array == NULL) {
    return NULL;
  }
  if(filtered_array->length != 0) {
    memcpy(filtered_array->array, temp, filtered_array_index * sizeof(int));
  }
  return filtered_array;
}

int reduce(Array *src, int init, Reducer reducer) {
  int result = init;
  for(size_t i = 0; i < src->length; i++) {
    result = (*reducer)(result, src->array[i]);
  }
  return result;
}
