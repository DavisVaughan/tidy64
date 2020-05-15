#ifndef TIDY64_TIDY64_H
#define TIDY64_TIDY64_H

#include "r.h"

// -----------------------------------------------------------------------------

// Defined equivalently to how base R uses `NA_INTEGER == INT_MIN`
#define r_int64_na INT64_MIN

// -----------------------------------------------------------------------------

struct tidy64 {
  double left;
  double right;
};

const struct tidy64 new_na_tidy64();

// -----------------------------------------------------------------------------

#endif
