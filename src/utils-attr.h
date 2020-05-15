#ifndef TIDY64_UTILS_ATTR_H
#define TIDY64_UTILS_ATTR_H

#include "r.h"

// -----------------------------------------------------------------------------

static inline sexp r_peek_attribute(sexp x, sexp sym) {
  return Rf_getAttrib(x, sym);
}
static inline sexp r_poke_attribute(sexp x, sexp sym, sexp value) {
  return Rf_setAttrib(x, sym, value);
}

// -----------------------------------------------------------------------------

static inline sexp r_peek_names(sexp x) {
  return r_peek_attribute(x, R_NamesSymbol);
}
static inline sexp r_poke_names(sexp x, sexp names) {
  return r_poke_attribute(x, R_NamesSymbol, names);
}

// -----------------------------------------------------------------------------

static inline sexp r_peek_class(sexp x) {
  return r_peek_attribute(x, R_ClassSymbol);
}
static inline sexp r_poke_class(sexp x, sexp cls) {
  return r_poke_attribute(x, R_ClassSymbol, cls);
}

// -----------------------------------------------------------------------------

#endif
