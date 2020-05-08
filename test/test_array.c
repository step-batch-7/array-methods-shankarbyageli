#include<stdio.h>
#include "../testLib/mocha.h"
#include "../array.h"

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

int main(void) {
  describe("create array");
  test_case("should create array of given length", create_array_of_given_length());
  test_case("should create empty array if given length is 0", create_array_of_length_0());

  return 0;
}