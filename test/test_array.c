#include<stdio.h>
#include "../testLib/mocha.h"
#include "../array.h"

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
  return 0;
}
