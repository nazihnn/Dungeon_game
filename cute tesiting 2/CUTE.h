/* 
   C Unit Testing at Essex (CUTE)
   Author: Prof Riccardo Poli (2022)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CUTE_asserts_done = 0;
int CUTE_asserts_failed = 0;
char *current_test = NULL;

void __print_test_function_name_if_first_assert(const char *__function) {
  if ( !current_test || strcmp(current_test, __function) ) {
    fprintf(stderr,"Test %s:\n",  __function );
    current_test = strdup(__function);
  }
}

void __assert_fail (const char *__assertion, const char *__file,
		    unsigned int __line, const char *__function, const char *__message) {
  __print_test_function_name_if_first_assert(__function);
  fprintf(stderr,"    Assert *FAILED* (%s line %d) %s\n", __file+12, __line-1, __message);
  CUTE_asserts_failed++;
}

void __assert_pass (const char *__assertion, const char *__file,
		    unsigned int __line, const char *__function) {
  __print_test_function_name_if_first_assert(__function);
  fprintf(stderr,"    Assert passed.\n");
}

#define CUTEassert(expr, message)						\
  (CUTE_asserts_done++,(expr)						\
     ? __assert_pass (#expr, __FILE__, __LINE__, __func__)		\
   : __assert_fail (#expr, __FILE__, __LINE__, __func__, message))

#define GET_MACRO2(_1,_2,NAME,...) NAME
#define GET_MACRO3(_1,_2,_3,NAME,...) NAME
#define GET_MACRO4(_1,_2,_3,_4,NAME,...) NAME
#define GET_MACRO5(_1,_2,_3,_4,_5,NAME,...) NAME

#define assert_equals2(a,b) CUTEassert((a)==(b),"")
#define assert_equals3(a,b,message) CUTEassert((a)==(b),message)
#define assert_equals(...) GET_MACRO3(__VA_ARGS__, assert_equals3, assert_equals2)(__VA_ARGS__)

//#define GET_MACRO(_3,_4,NAME,...) NAME
#define assert_near_equals(...) GET_MACRO4(__VA_ARGS__, assert_near_equals4, assert_near_equals3)(__VA_ARGS__)
#define assert_near_equals3(a,b,tollerance) CUTEassert(abs((a)-(b))<= (tollerance),"")
#define assert_near_equals4(a,b,tollerance,message) CUTEassert(abs((a)-(b))<= (tollerance),message)

#define assert_true(...) GET_MACRO2(__VA_ARGS__, assert_true2, assert_true1)(__VA_ARGS__)
#define assert_true1(a) CUTEassert((a),"")
#define assert_true2(a,message) CUTEassert((a),message)

#define assert_equals_strings(...) GET_MACRO3(__VA_ARGS__, assert_equals_strings3, assert_equals_strings2)(__VA_ARGS__)
#define assert_equals_strings2(a,b) CUTEassert(strcmp((a),(b))==0,"")
#define assert_equals_strings3(a,b,message) CUTEassert(strcmp((a),(b))==0,message)

#define assert_equals_arrays(...) GET_MACRO5(__VA_ARGS__, assert_equals_arrays5, assert_equals_arrays4)(__VA_ARGS__)
#define assert_equals_arrays4(a,b,num,size) CUTEassert(memcmp((a), (b), (num)*(size)) == 0,"")
#define assert_equals_arrays5(a,b,num,size,message) CUTEassert(memcmp((a), (b), (num)*(size)) == 0,message)

/* More to be added */
