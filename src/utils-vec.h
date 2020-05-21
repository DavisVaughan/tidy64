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
static inline sexp r_new_chr(r_ssize size) {
  return r_new_vector(r_type_character, size);
}
static inline sexp r_new_int(r_ssize size) {
  return r_new_vector(r_type_integer, size);
}
static inline sexp r_new_lgl(r_ssize size) {
  return r_new_vector(r_type_logical, size);
}

// -----------------------------------------------------------------------------

static inline sexp r_list_get(sexp x, r_ssize i) {
  return VECTOR_ELT(x, i);
}
static inline sexp r_list_set(sexp x, r_ssize i, sexp value) {
  return SET_VECTOR_ELT(x, i, value);
}

static inline sexp r_chr_get(sexp x, r_ssize i) {
  return STRING_PTR(x)[i];
}
static inline void r_chr_set(sexp x, r_ssize i, sexp value) {
  SET_STRING_ELT(x, i, value);
}

// -----------------------------------------------------------------------------

static inline int* r_lgl_deref(sexp x) {
  return LOGICAL(x);
}
static inline const int* r_lgl_const_deref(sexp x) {
  return (const int*) r_lgl_deref(x);
}

static inline int* r_int_deref(sexp x) {
  return INTEGER(x);
}
static inline const int* r_int_const_deref(sexp x) {
  return (const int*) r_int_deref(x);
}

static inline double* r_dbl_deref(sexp x) {
  return REAL(x);
}
static inline const double* r_dbl_const_deref(sexp x) {
  return (const double*) r_dbl_deref(x);
}

static inline sexp* r_chr_deref(sexp x) {
  return STRING_PTR(x);
}
static inline const sexp* r_chr_const_deref(sexp x) {
  return (const sexp*) r_chr_deref(x);
}

// -----------------------------------------------------------------------------

static inline bool r_lgl_missing(int x) {
  return x == r_lgl_na;
}
static inline bool r_dbl_missing(double x) {
  return isnan(x);
}
static inline bool r_int_missing(int x) {
  return x == r_int_na;
}
static inline bool r_chr_missing(sexp x) {
  return x == r_chr_na;
}

// -----------------------------------------------------------------------------

static inline sexp r_new_shared_vector(enum r_type type, r_ssize size) {
  sexp out = r_new_vector(type, size);
  R_PreserveObject(out);
  MARK_NOT_MUTABLE(out);
  return out;
}

// -----------------------------------------------------------------------------

#endif
