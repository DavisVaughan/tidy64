#ifndef TIDY64_UTILS_TYPE_H
#define TIDY64_UTILS_TYPE_H

#include "r.h"

// -----------------------------------------------------------------------------

static inline enum r_type r_typeof(sexp x) {
  return TYPEOF(x);
}

// -----------------------------------------------------------------------------

#endif
