#ifndef TIDY64_TIDY64_H
#define TIDY64_TIDY64_H

#include "r.h"
#include "utils.h"

// -----------------------------------------------------------------------------

// Defined equivalently to how base R uses `NA_INTEGER == INT_MIN`
#define r_int64_na INT64_MIN

#define TIDY64_MAX INT64_MAX
#define TIDY64_MIN (INT64_MIN + 1)

// Maximum double value such that it and all smaller integers can be represented
// as an integer without loss of precision. It is 2^53.
// https://stackoverflow.com/questions/1848700/biggest-integer-that-can-be-stored-in-a-double
#define DBL_MAX_NO_PRECISION_LOSS 9007199254740992
#define DBL_MIN_NO_PRECISION_LOSS (-DBL_MAX_NO_PRECISION_LOSS)

// -----------------------------------------------------------------------------

#define DBL_OUTSIDE_TIDY64_RANGE(X) (X < TIDY64_MIN || X > TIDY64_MAX)
#define DBL_TIDY64_MIGHT_LOSE_PRECISION(X) (X < DBL_MIN_NO_PRECISION_LOSS || X > DBL_MAX_NO_PRECISION_LOSS)

// -----------------------------------------------------------------------------

static inline sexp tidy64_get_left(sexp x) {
  return r_list_get(x, 0);
}
static inline sexp tidy64_get_right(sexp x) {
  return r_list_get(x, 1);
}

// -----------------------------------------------------------------------------

struct tidy64 {
  double left;
  double right;
};

// -----------------------------------------------------------------------------

const struct tidy64 new_na_tidy64();

sexp new_tidy64(sexp left, sexp right);

// -----------------------------------------------------------------------------

#endif
