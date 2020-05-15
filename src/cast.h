#ifndef TIDY64_CAST_H
#define TIDY64_CAST_H

#include "r.h"

// -----------------------------------------------------------------------------

sexp tidy64_cast_to_tidy64_from_dbl(sexp x);
sexp tidy64_cast_to_tidy64_from_int(sexp x);
sexp tidy64_cast_to_tidy64_from_lgl(sexp x);

sexp tidy64_cast_to_dbl_from_tidy64(sexp x);
sexp tidy64_cast_to_int_from_tidy64(sexp x);
sexp tidy64_cast_to_lgl_from_tidy64(sexp x);

// -----------------------------------------------------------------------------

sexp export_tidy64_cast_to_tidy64_from_dbl(sexp x);
sexp export_tidy64_cast_to_tidy64_from_int(sexp x);
sexp export_tidy64_cast_to_tidy64_from_lgl(sexp x);

sexp export_tidy64_cast_to_dbl_from_tidy64(sexp x);
sexp export_tidy64_cast_to_int_from_tidy64(sexp x);
sexp export_tidy64_cast_to_lgl_from_tidy64(sexp x);

#endif
