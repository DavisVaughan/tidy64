#ifndef TIDY64_R_H
#define TIDY64_R_H

// -----------------------------------------------------------------------------

// From: https://rpg.hamsterrepublic.com/source/wip/config.h
// This causes MinGW and MinGW-w64 (Windows) to switch to C99-compliant
// printf and scanf family functions (i.e., this causes __USE_MINGW_ANSI_STDIO
// to be defined).

// According to https://svn.python.org/projects/python/trunk/configure,
// defining _POSIX_C_SOURCE causes lots of broken stuff on virtually every Unix,
// so only set it on MinGW.

// This must be defined before loading in <R.h> or <Rinternals.h> because
// they seem to also include <stdio.h>.

#ifdef __MINGW32__  // MinGW or MinGW-w64
# define _POSIX_C_SOURCE 200809L
#endif

// To link in printf() / scanf() with C99-compliant features
// (i.e. the ability to use %lli which is expanded from %PRId64)
#include <stdio.h>

// -----------------------------------------------------------------------------

// For int64_t
#include <stdint.h>

// For bool
#include <stdbool.h>

// -----------------------------------------------------------------------------

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

// -----------------------------------------------------------------------------

#define sexp SEXP

// -----------------------------------------------------------------------------

enum r_type {
  r_type_null        = 0,
  r_type_symbol      = 1,
  r_type_pairlist    = 2,
  r_type_closure     = 3,
  r_type_environment = 4,
  r_type_promise     = 5,
  r_type_call        = 6,
  r_type_special     = 7,
  r_type_builtin     = 8,
  r_type_string      = 9,
  r_type_logical     = 10,
  r_type_integer     = 13,
  r_type_double      = 14,
  r_type_complex     = 15,
  r_type_character   = 16,
  r_type_dots        = 17,
  r_type_any         = 18,
  r_type_list        = 19,
  r_type_expression  = 20,
  r_type_bytecode    = 21,
  r_type_pointer     = 22,
  r_type_weakref     = 23,
  r_type_raw         = 24,
  r_type_s4          = 25,

  r_type_new         = 30,
  r_type_free        = 31,

  r_type_function    = 99
};

// -----------------------------------------------------------------------------

#define KEEP PROTECT
#define FREE UNPROTECT
#define KEEP_N(x, n) (++n, KEEP(x))
#define KEEP_WITH_INDEX(x, i) PROTECT_WITH_INDEX(x, &i)
#define REKEEP REPROTECT

// -----------------------------------------------------------------------------

#define r_ssize R_xlen_t
#define R_SSIZE_MAX R_XLEN_T_MAX

// -----------------------------------------------------------------------------

#define r_null R_NilValue

#define r_lgl_na NA_LOGICAL
#define r_dbl_na NA_REAL
#define r_int_na NA_INTEGER
#define r_chr_na NA_STRING

#define r_dbl_nan R_NaN

#endif
