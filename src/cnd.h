#ifndef TIDY64_CND_H
#define TIDY64_CND_H

#include "r.h"

// -----------------------------------------------------------------------------

void warn_to_tidy64_from_dbl_oob(sexp x);
void warn_to_int_from_tidy64_oob(sexp x);
void warn_to_dbl_from_tidy64_oob_precision(sexp x);

// -----------------------------------------------------------------------------

__attribute__((noreturn))
void stop_to_tidy64_from_dbl_oob(sexp x, sexp to, sexp x_arg, sexp to_arg);

__attribute__((noreturn))
void stop_to_dbl_from_tidy64_oob_precision(sexp x, sexp to, sexp x_arg, sexp to_arg);

__attribute__((noreturn))
void stop_to_tidy64_from_dbl_lossy_fractional(sexp x, sexp to, sexp x_arg, sexp to_arg);

__attribute__((noreturn))
void stop_to_int_from_tidy64_oob(sexp x, sexp to, sexp x_arg, sexp to_arg);

// -----------------------------------------------------------------------------

sexp export_tidy64_detect_to_dbl_from_tidy64_oob_precision(sexp x);
sexp export_tidy64_detect_to_int_from_tidy64_oob(sexp x);

// -----------------------------------------------------------------------------

#endif
