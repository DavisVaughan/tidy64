#ifndef TIDY64_ARITHMETIC_H
#define TIDY64_ARITHMETIC_H

#include "r.h"

sexp export_tidy64_plus_tidy64_tidy64(sexp x, sexp y, sexp size);

sexp export_tidy64_plus_tidy64_integer(sexp x, sexp y, sexp size);
sexp export_tidy64_plus_integer_tidy64(sexp x, sexp y, sexp size);

sexp export_tidy64_plus_tidy64_logical(sexp x, sexp y, sexp size);
sexp export_tidy64_plus_logical_tidy64(sexp x, sexp y, sexp size);

sexp export_tidy64_plus_tidy64_double(sexp x, sexp y, sexp size);
sexp export_tidy64_plus_double_tidy64(sexp x, sexp y, sexp size);

#endif
