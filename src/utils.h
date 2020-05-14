#ifndef TIDY64_UTILS_H
#define TIDY64_UTILS_H

#include "r.h"

// -----------------------------------------------------------------------------

static inline r_ssize r_length(sexp x) {
  return Rf_xlength(x);
}

// -----------------------------------------------------------------------------

static inline enum r_type r_typeof(sexp x) {
  return TYPEOF(x);
}

// -----------------------------------------------------------------------------

#endif
