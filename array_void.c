#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "array_void.h"

ArrayVoid_ptr create_void_array(int length) {
  ArrayVoid_ptr void_array = malloc(sizeof(ArrayVoid));
  if(void_array == NULL) {
    return NULL;
  }
  void_array->length = length;
  void_array->array = length ? malloc(sizeof(Object) * length) : NULL;
  return void_array;
}

ArrayVoid_ptr map_void(ArrayVoid_ptr src, MapperVoid mapper) {
  ArrayVoid_ptr mapped = create_void_array(src->length);
  if(mapped == NULL) {
    return NULL;
  }
  for(size_t i = 0; i < src->length; i++) {
    mapped->array[i] = (*mapper)(src->array[i]);
  }
  return mapped;
}
