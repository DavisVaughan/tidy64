#ifndef TIDY64_UTILS_SIZE_H
#define TIDY64_UTILS_SIZE_H

#include "r.h"
#include "utils-cnd.h"
#include "utils-vec.h"
#include "utils-type.h"

// -----------------------------------------------------------------------------

static inline r_ssize r_length(sexp x) {
  return Rf_xlength(x);
}

// -----------------------------------------------------------------------------

static inline r_ssize r_length_get(sexp x) {
  if (r_length(x) != 1) {
    r_abort("Size vector `x` must have length 1.");
  }

  switch (r_typeof(x)) {
  case r_type_integer:
    return (r_ssize) r_int_const_deref(x)[0];
  case r_type_double:
    return (r_ssize) r_dbl_const_deref(x)[0];
  default:
    r_abort("Size vector `x` can only be integer or double.");
  }

  never_reached("r_length_get");
}

// -----------------------------------------------------------------------------

#endif
