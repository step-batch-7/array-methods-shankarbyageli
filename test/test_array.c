#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../testLib/mocha.h"
#include "../array.h"
#include "../array_void.h"

int multiply_by_two(int num) {
  return num * 2;
}

Bool are_equal(int *a1, int *a2, int length) {
  for(size_t i = 0; i < length; i++) {
    if(a1[i] != a2[i]) {
      return False;
    }
  }
  return True;
}

Bool is_even(int num) {
  return num % 2 == 0;
}

int add(int num1, int num2) {
  return num1 + num2;
}

Object convert_to_lowercase(Object value) {
  Object result = malloc(sizeof(char));
  *(char *)result = *(char *)value + 32;
  return result;
}

Object increment_by_1(Object value) {
  Object result = malloc(sizeof(int));
  *(int *)result = *(int *)value + 1;
  return result;
} 

Bool are_int_arrrays_equal(Object *a1, int *a2, int length) {
  for(size_t i = 0; i < length; i++) {
    if(*(int *)a1[i] != a2[i]) {
      return False;
    }
  }
  return True;
}

Bool are_char_arrays_equal(Object *a1, char *a2, int length) {
  for(size_t i = 0; i < length; i++) {
    if(*(char *)a1[i] != a2[i]) {
      return False;
    }
  }
  return True;
}

Bool is_void_even(Object num) {
  return *(int *)num % 2 == 0;
}

Bool is_void_vowel(Object character) {
  char vowels[] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
  for(size_t i = 0; i < 10; i++) {
    if(vowels[i] == *(char *)character) {
      return True;
    }
  }
  return False;
}

Object sum_numbers(Object num1, Object num2) {
  Object result = malloc(sizeof(int));
  *(int *)result = *(int *)num1 + *(int *)num2;
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

__testStatus map_void_convert_to_lowercase() {
  ArrayVoid_ptr char_array = create_void_array(4);
  for(size_t i = 0; i < 4; i++) {
    char_array->array[i] = malloc(sizeof(char));
    *(char *)char_array->array[i] = 65 + i;
  }
  char mapping_result[] = {'a', 'b', 'c', 'd'};
  ArrayVoid_ptr mapped_array = map_void(char_array, &convert_to_lowercase);
  if(mapped_array->length == 4 && are_char_arrays_equal(mapped_array->array, mapping_result, 4)) {
    return __Success;
  }
  return __Failure;
}

__testStatus map_void_increment_by_1() {
  ArrayVoid_ptr int_array = create_void_array(4);
  for(size_t i = 0; i < 4; i++) {
    int_array->array[i] = malloc(sizeof(int));
    *(int *)int_array->array[i] = i;
  }
  int mapping_result[] = {1, 2, 3, 4};
  ArrayVoid_ptr mapped_array = map_void(int_array, &increment_by_1);
  if(mapped_array->length == 4 && are_int_arrrays_equal(mapped_array->array, mapping_result, 4)) {
    return __Success;
  }
  return __Failure;
}

__testStatus map_void_empty_array() {
  ArrayVoid_ptr int_array = create_void_array(0);
  ArrayVoid_ptr mapped_array = map_void(int_array, &increment_by_1);
  if(mapped_array->length == 0 && mapped_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_void_even_numbers() {
  ArrayVoid_ptr int_array = create_void_array(4);
  for(size_t i = 0; i < 4; i++) {
    int_array->array[i] = malloc(sizeof(int));
    *(int *)int_array->array[i] = i + 1;
  }
  int filter_result[] = {2, 4};
  ArrayVoid_ptr filtered_array = filter_void(int_array, &is_void_even);
  if(filtered_array->length == 2 && are_int_arrrays_equal(filtered_array->array, filter_result,  2)) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_void_vowels() {
  ArrayVoid_ptr char_array = create_void_array(5);
  for(size_t i = 0; i < 5; i++) {
    char_array->array[i] = malloc(sizeof(char));
    *(char *)char_array->array[i] = 65 + i;
  }
  char filter_result[] = {'A', 'E'};
  ArrayVoid_ptr filtered_array = filter_void(char_array, &is_void_vowel);
  if(filtered_array->length == 2 && are_char_arrays_equal(filtered_array->array, filter_result,  2)) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_void_empty_array() {
  ArrayVoid_ptr int_array = create_void_array(0);
  ArrayVoid_ptr filtered_array = filter_void(int_array, &is_void_even);
  if(filtered_array->length == 0 && filtered_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus reduce_void_empty_array() {
  ArrayVoid_ptr int_array = create_void_array(0);
  Object init = malloc(sizeof(int));
  *(int *)init = 1;
  Object result = reduce_void(int_array, init, &sum_numbers);
  if(*(int *)result == 1) {
    return __Success;
  }
  return __Failure;
}

__testStatus reduce_void_sum_of_numbers() {
  ArrayVoid_ptr int_array = create_void_array(5);
  for(size_t i = 0; i < 5; i++) {
    int_array->array[i] = malloc(sizeof(int));
    *(int *)int_array->array[i] = i + 1;
  }
  Object init = malloc(sizeof(int));
  *(int *)init = 0;
  Object sum = reduce_void(int_array, init, &sum_numbers);
  if(*(int *)sum == 15) {
    return __Success;
  }
  return __Failure;
}


__testStatus create_array_of_given_length() {
  Array *int_array = create_array(4);
  if(int_array->length == 4 && int_array->array != NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus create_array_of_length_0() {
  Array *int_array = create_array(0);
  if(int_array->length == 0 && int_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus map_multiply_by_two() {
  Array *int_array = create_array(4);
  for(size_t i = 0; i < 4; i++) {
    int_array->array[i] = i + 1;
  }
  int mapping_result[] = {2, 4, 6, 8};
  Array *mapped_array = map(int_array, &multiply_by_two);
  if(mapped_array->length == 4 && are_equal(mapping_result, mapped_array->array, 4)) {
    return __Success;
  }
  return __Failure;
}

__testStatus map_empty_array() {
  Array *int_array = create_array(0);
  Array *mapped_array = map(int_array, &multiply_by_two);
  if(mapped_array->length == 0 && mapped_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_even_numbers() {
  Array *int_array = create_array(4);
  for(size_t i = 0; i < 4; i++) {
    int_array->array[i] = i + 1;
  }
  int filter_result[] = {2, 4};
  Array *filtered_array = filter(int_array, &is_even);
  if(filtered_array->length == 2 && are_equal(filter_result, filtered_array->array, 2)) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_empty_array() {
  Array *int_array = create_array(0);
  Array *filtered_array = filter(int_array, &is_even);
  if(filtered_array->length == 0 && filtered_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_array_returning_empty() {
  Array *int_array = create_array(1);
  int_array->array[0] = 1;
  Array *filtered_array = filter(int_array, &is_even);
  if(filtered_array->length == 0 && filtered_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

__testStatus reduce_empty_array() {
  Array *int_array = create_array(0);
  int result = reduce(int_array, 1, &add);
  if(result == 1) {
    return __Success;
  }
  return __Failure;
}

__testStatus sum_of_all() {
  Array *int_array = create_array(5);
  for(size_t i = 0; i < 5; i++) {
    int_array->array[i] = i + 1;
  }
  int sum = reduce(int_array, 0, &add);
  if(sum == 15) {
    return __Success;
  }
  return __Failure;
}

int main(void) {
  describe("create array");
  test_case("should create array of given length", create_array_of_given_length());
  test_case("should create empty array if given length is 0", create_array_of_length_0());

  describe("map function");
  test_case("should return array of same length as source array with mapped values", map_multiply_by_two());
  test_case("should return empty array if source array is empty", map_empty_array());

  describe("filter function");
  test_case("should return array of filtered values based on predicate", filter_even_numbers());
  test_case("should return empty array if src is empty", filter_empty_array());
  test_case("should return empty array if filtered values are 0", filter_array_returning_empty());

  describe("reduce function");
  test_case("should return initial value if src array is empty", reduce_empty_array());
  test_case("should return sum of all numbers in src array", sum_of_all());

  describe("create void array");
  test_case("should create void array of given length", create_void_array_of_given_length());
  test_case("should create empty void array if given length is 0", create_empty_void_array());

  describe("map void function");
  test_case("should return array of same length as source array with lowercase converted characters", map_void_convert_to_lowercase());
  test_case("should return array of same length as source array with values incremented by 1", map_void_increment_by_1());
  test_case("should return empty array if source array is empty", map_void_empty_array());

  describe("filter void function");
  test_case("should return array of filtered values based on predicate", filter_void_even_numbers());
  test_case("should return empty array if src is empty", filter_void_empty_array());
  test_case("should return filtered array of vowels", filter_void_vowels());

  describe("reduce void function");
  test_case("should return initial value if src array is empty", reduce_void_empty_array());
  test_case("should return sum of all numbers in src array", reduce_void_sum_of_numbers());

  return 0;
}
