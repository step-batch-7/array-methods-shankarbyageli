#include<stdio.h>
#include<stdlib.h>
#include "../testLib/mocha.h"
#include "../array_void.h"

Object multiply_by_two(Object value) {
  Object result = malloc(sizeof(int));
  *(int *)result = *(int *)value * 2;
  return result;
}

__testStatus create_void_array_of_given_length() {
  ArrayVoid_ptr int_array = create_void_array(4);
  if(int_array->length == 4 && int_array->array != NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus create_empty_void_array() {
  ArrayVoid_ptr int_array = create_void_array(0);
  if(int_array->length == 0 && int_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus map_multiply_by_two() {
  ArrayVoid_ptr int_array = create_void_array(4);
  for(size_t i = 0; i < 4; i++) {
    int_array->array[i] = malloc(sizeof(int));
    *(int *)int_array->array[i] = i + 1;
  }
  int mapping_result[] = {2, 4, 6, 8};
  ArrayVoid_ptr mapped_array = map_void(int_array, &multiply_by_two);
  if(mapped_array->length == 4 && are_equal(mapped_array->array, mapping_result, 4)) {
    return __Success;
  }
  return __Failure;
}

__testStatus map_empty_array() {
  ArrayVoid_ptr int_array = create_void_array(0);
  ArrayVoid_ptr mapped_array = map_void(int_array, &multiply_by_two);
  if(mapped_array->length == 0 && mapped_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

int main(void) {
  describe("create void array");
  test_case("should create void array of given length", create_void_array_of_given_length());
  test_case("should create empty void array if given length is 0", create_empty_void_array());

  describe("map function");
  test_case("should return array of same length as source array with mapped values", map_multiply_by_two());
  test_case("should return empty array if source array is empty", map_empty_array());
  
  return 0;
}
