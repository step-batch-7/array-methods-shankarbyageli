#include<stdio.h>
#include<stdlib.h>
#include "../testLib/mocha.h"
#include "../array_void.h"

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

Bool is_even(Object num) {
  return *(int *)num % 2 == 0;
}

Bool is_vowel(Object character) {
  char vowels[] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
  for(size_t i = 0; i < 10; i++) {
    if(vowels[i] == *(char *)character) {
      return True;
    }
  }
  return False;
}

Object add(Object num1, Object num2) {
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
  ArrayVoid_ptr filtered_array = filter_void(int_array, &is_even);
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
  ArrayVoid_ptr filtered_array = filter_void(char_array, &is_vowel);
  if(filtered_array->length == 2 && are_char_arrays_equal(filtered_array->array, filter_result,  2)) {
    return __Success;
  }
  return __Failure;
}

__testStatus filter_void_empty_array() {
  ArrayVoid_ptr int_array = create_void_array(0);
  ArrayVoid_ptr filtered_array = filter_void(int_array, &is_even);
  if(filtered_array->length == 0 && filtered_array->array == NULL) {
    return __Success;
  }
  return __Failure;
}

int main(void) {
  describe("create void array");
  test_case("should create void array of given length", create_void_array_of_given_length());
  test_case("should create empty void array if given length is 0", create_empty_void_array());

  describe("map function");
  test_case("should return array of same length as source array with lowercase converted characters", map_void_convert_to_lowercase());
  test_case("should return array of same length as source array with values incremented by 1", map_void_increment_by_1());
  test_case("should return empty array if source array is empty", map_void_empty_array());

  describe("filter function");
  test_case("should return array of filtered values based on predicate", filter_void_even_numbers());
  test_case("should return empty array if src is empty", filter_void_empty_array());
  test_case("should return filtered array of vowels", filter_void_vowels());

  return 0;
}
