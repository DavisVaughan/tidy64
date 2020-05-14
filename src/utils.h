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

static inline sexp r_new_vector(enum r_type type, r_ssize size) {
  return Rf_allocVector(type, size);
}

// -----------------------------------------------------------------------------

static inline sexp r_list_get(sexp x, r_ssize i) {
  return VECTOR_ELT(x, i);
}
static inline sexp r_list_set(sexp x, r_ssize i, sexp value) {
  return SET_VECTOR_ELT(x, i, value);
}

// -----------------------------------------------------------------------------

static inline double* r_dbl_deref(sexp x) {
  return REAL(x);
}


static inline const double* r_dbl_const_deref(sexp x) {
  return (const double*) REAL(x);
}

// -----------------------------------------------------------------------------

__attribute__((noreturn)) static inline void never_reached(const char* fn) {
  Rf_errorcall(r_null, "Internal error: Reached the unreachable in `%s()`.", fn);
}

// -----------------------------------------------------------------------------

void r_abort(const char* fmt, ...);

// -----------------------------------------------------------------------------

#endif
