#ifndef TIDY64_UTILS_STRING_H
#define TIDY64_UTILS_STRING_H

#include "r.h"

// -----------------------------------------------------------------------------

static inline sexp r_new_string(const char* x) {
  return Rf_mkChar(x);
}

// -----------------------------------------------------------------------------

#endif
