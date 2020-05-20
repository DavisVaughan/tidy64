#ifndef TIDY64_UTILS_CALL_H
#define TIDY64_UTILS_CALL_H

#include "r.h"
#include "utils-globals.h"

// -----------------------------------------------------------------------------

sexp r_pairlist(sexp* tags, sexp* cars);

static inline sexp r_call(sexp fn, sexp* tags, sexp* cars) {
  return Rf_lcons(fn, r_pairlist(tags, cars));
}

sexp r_protect(sexp x);

// -----------------------------------------------------------------------------

static inline sexp r_eval(sexp x, sexp env) {
  return Rf_eval(x, env);
}

// -----------------------------------------------------------------------------

#endif
