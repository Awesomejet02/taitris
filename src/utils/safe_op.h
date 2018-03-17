/**
 * @file    safe_op.h
 * @author  S4MasterRace
 * @version 2.0
 * @brief   Safe operations
 */
#ifndef TAITRIS_SAFE_OP_H
#define TAITRIS_SAFE_OP_H

#include <limits.h>

#define SAFE_OP_SUCCESS   0
#define SAFE_OP_OVERFLOW  1
#define SAFE_OP_UNDERFLOW (-1)

static inline
int safe_char_add(char a, char b, char *r) {
  if (b >= 0 && a > (CHAR_MAX - b))
    return SAFE_OP_OVERFLOW;
  else if (b < 0 && a < (CHAR_MIN - b))
    return SAFE_OP_UNDERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_uchar_add(unsigned char a, unsigned char b, unsigned char *r) {
  if (a > (UCHAR_MAX - b))
    return SAFE_OP_OVERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_short_add(short a, short b, short *r) {
  if (b >= 0 && a > (SHRT_MAX - b))
    return SAFE_OP_OVERFLOW;
  else if (b < 0 && a < (SHRT_MIN - b))
    return SAFE_OP_UNDERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_ushort_add(unsigned short a, unsigned short b, unsigned short *r) {
  if (a > (USHRT_MAX - b))
    return SAFE_OP_OVERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_int_add(int a, int b, int *r) {
  if (b >= 0 && a > (INT_MAX - b))
    return SAFE_OP_OVERFLOW;
  else if (b < 0 && a < (INT_MIN - b))
    return SAFE_OP_UNDERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_uint_add(unsigned int a, unsigned int b, unsigned int *r) {
  if (a > (UINT_MAX - b))
    return SAFE_OP_OVERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_long_add(long a, long b, long *r) {
  if (b >= 0 && a > (LONG_MAX - b))
    return SAFE_OP_OVERFLOW;
  else if (b < 0 && a < (LONG_MIN - b))
    return SAFE_OP_UNDERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_ulong_add(unsigned long a, unsigned long b, unsigned long *r) {
  if (a > (ULONG_MAX - b))
    return SAFE_OP_OVERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_llong_add(long long a, long long b, long long *r) {
  if (b >= 0 && a > (LLONG_MAX - b))
    return SAFE_OP_OVERFLOW;
  else if (b < 0 && a < (LLONG_MIN - b))
    return SAFE_OP_UNDERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

static inline
int safe_ullong_add(
    unsigned long long a,
    unsigned long long b,
    unsigned long long *r
) {
  if (a > (ULLONG_MAX - b))
    return SAFE_OP_OVERFLOW;

  *r = a + b;
  return SAFE_OP_SUCCESS;
}

#endif //TAITRIS_SAFE_OP_H
