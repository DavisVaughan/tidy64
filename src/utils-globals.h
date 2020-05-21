#ifndef TIDY64_GLOBALS_H
#define TIDY64_GLOBALS_H

#include "r.h"

// -----------------------------------------------------------------------------

extern sexp tidy64_ns_env;

// -----------------------------------------------------------------------------

extern sexp syms_x;
extern sexp syms_to;
extern sexp syms_x_arg;
extern sexp syms_to_arg;
extern sexp syms_warn_to_tidy64_from_dbl_oob;
extern sexp syms_stop_to_tidy64_from_dbl_oob;
extern sexp syms_stop_to_dbl_from_tidy64_oob_precision;

// -----------------------------------------------------------------------------

extern sexp names_left_right;

// -----------------------------------------------------------------------------

extern sexp classes_tidy64;

// -----------------------------------------------------------------------------

extern sexp fns_quote;

// -----------------------------------------------------------------------------

void tidy64_initialize_utils_globals(sexp ns);

// -----------------------------------------------------------------------------

#endif
