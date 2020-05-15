#ifndef TIDY64_UTILS_SIZE_H
#define TIDY64_UTILS_SIZE_H

#include "r.h"

// -----------------------------------------------------------------------------

static inline r_ssize r_length(sexp x) {
  return Rf_xlength(x);
}

// -----------------------------------------------------------------------------

#endif
