#ifndef TIDY64_TIDY64_H
#define TIDY64_TIDY64_H

#include "r.h"
#include "utils.h"

// -----------------------------------------------------------------------------

// Defined equivalently to how base R uses `NA_INTEGER == INT_MIN`
#define tidy64_na INT64_MIN

#define TIDY64_MAX INT64_MAX
#define TIDY64_MIN (INT64_MIN + 1)

#define R_INT_MAX INT_MAX
#define R_INT_MIN (INT_MIN + 1)

// -----------------------------------------------------------------------------

static inline bool tidy64_dbl_is_outside_tidy64_range(double x) {
  return x < TIDY64_MIN || x > TIDY64_MAX;
}

static inline bool tidy64_is_outside_int_range(int64_t x) {
  return x < R_INT_MIN || x > R_INT_MAX;
}

// -----------------------------------------------------------------------------

// Maximum double value such that it and all smaller integers can be represented
// as an integer without loss of precision. It is 2^53.
// https://stackoverflow.com/questions/1848700/biggest-integer-that-can-be-stored-in-a-double
#define DBL_MAX_NO_PRECISION_LOSS 9007199254740992
#define DBL_MIN_NO_PRECISION_LOSS (-DBL_MAX_NO_PRECISION_LOSS)

#define MIGHT_LOSE_PRECISION(X) (X < DBL_MIN_NO_PRECISION_LOSS || X > DBL_MAX_NO_PRECISION_LOSS)

static inline bool tidy64_to_tidy64_from_dbl_might_lose_precision(double x) {
  return MIGHT_LOSE_PRECISION(x);
}
static inline bool tidy64_to_dbl_from_tidy64_might_lose_precision(double x) {
  return MIGHT_LOSE_PRECISION(x);
}

#undef MIGHT_LOSE_PRECISION

#undef DBL_MAX_NO_PRECISION_LOSS
#undef DBL_MIN_NO_PRECISION_LOSS

// -----------------------------------------------------------------------------

struct tidy64 {
  double left;
  double right;
};

// -----------------------------------------------------------------------------

static inline sexp tidy64_get_left(sexp x) {
  return r_list_get(x, 0);
}
static inline sexp tidy64_get_right(sexp x) {
  return r_list_get(x, 1);
}

static inline const double* tidy64_get_left_const_deref(sexp x) {
  return r_dbl_const_deref(tidy64_get_left(x));
}
static inline const double* tidy64_get_right_const_deref(sexp x) {
  return r_dbl_const_deref(tidy64_get_right(x));
}

// -----------------------------------------------------------------------------

static inline sexp tidy64_new_left(r_ssize size) {
  return r_new_dbl(size);
}
static inline sexp tidy64_new_right(r_ssize size) {
  return r_new_dbl(size);
}

static inline double* tidy64_deref_left(sexp left) {
  return r_dbl_deref(left);
}
static inline double* tidy64_deref_right(sexp right) {
  return r_dbl_deref(right);
}

// -----------------------------------------------------------------------------

static inline r_ssize tidy64_size(sexp x) {
  return r_length(tidy64_get_left(x));
}

sexp tidy64_new(sexp left, sexp right);

// -----------------------------------------------------------------------------

#endif
