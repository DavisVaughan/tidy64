#ifndef TIDY64_FORCE_H
#define TIDY64_FORCE_H

#include "r.h"

// -----------------------------------------------------------------------------

sexp tidy64_force_to_chr_from_tidy64(sexp x);

sexp tidy64_force_to_tidy64_from_dbl(sexp x);

// -----------------------------------------------------------------------------

sexp export_tidy64_force_to_chr_from_tidy64(sexp x);

sexp export_tidy64_force_to_tidy64_from_dbl(sexp x);

#endif
