#ifndef TIDY64_UTILS_VEC_H
#define TIDY64_UTILS_VEC_H

#include "r.h"

// -----------------------------------------------------------------------------

static inline sexp r_new_vector(enum r_type type, r_ssize size) {
  return Rf_allocVector(type, size);
}
static inline sexp r_new_list(r_ssize size) {
  return r_new_vector(r_type_list, size);
}
static inline sexp r_new_dbl(r_ssize size) {
  return r_new_vector(r_type_double, size);
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

#endif
