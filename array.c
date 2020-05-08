#include<stdio.h>
#include<stdlib.h>
#include "array.h"

Array *create_array(int length) {
  Array *new_array = malloc(sizeof(Array));
  if(new_array == NULL) {
    return NULL;
  }
  new_array->length = length;
  new_array->array = malloc(length * sizeof(int));
  if(new_array->array == NULL) {
    return NULL;
  }
  return new_array;
}

Array *map(Array *array, Mapper mapper) {
  Array *mapped_array = create_array(array->length);
  if(mapped_array == NULL) {
    return NULL;
  }
  for(size_t i = 0; i < array->length; i++) {
    mapped_array->array[i] = (*mapper)(array->array[i]);
  }
  return mapped_array;
}

Array *filter(Array *array, Predicate predicate) {
  Array *filtered_array = create_array(array->length);
  if(filtered_array == NULL) {
    return NULL;
  }
  int filtered_array_index = 0;
  for(size_t i = 0; i < array->length; i++) {
    Bool result = (*predicate)(array->array[i]);
    if(result) {
      filtered_array->array[filtered_array_index] = array->array[i];
      filtered_array_index++;
    }
  }
  filtered_array->array = realloc(filtered_array->array, sizeof(int) * filtered_array_index);
  filtered_array->length = filtered_array_index;
  return filtered_array;
}

int reduce(Array *array, int init, Reducer reducer) {
  int result = init;
  for(size_t i = 0; i < array->length; i++) {
    result = (*reducer)(result, array->array[i]);
  }
  return result;
}
