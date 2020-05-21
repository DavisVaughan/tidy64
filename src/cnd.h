#ifndef TIDY64_CND_H
#define TIDY64_CND_H

#include "r.h"

// -----------------------------------------------------------------------------

void warn_to_tidy64_from_dbl_oob(sexp x);

// -----------------------------------------------------------------------------

__attribute__((noreturn))
void stop_to_tidy64_from_dbl_oob(sexp x, sexp to, sexp x_arg, sexp to_arg);

__attribute__((noreturn))
void stop_to_dbl_from_tidy64_oob_precision(sexp x, sexp to, sexp x_arg, sexp to_arg);

// -----------------------------------------------------------------------------

sexp export_tidy64_detect_to_dbl_from_tidy64_oob_precision(sexp x);

// -----------------------------------------------------------------------------

#endif
