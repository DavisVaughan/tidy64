#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <stdbool.h> // for bool
#include <R_ext/Rdynload.h>

#include "exports.h"

static const R_CallMethodDef CallEntries[] = {
  // cast.h
  {"export_tidy64_cast_to_tidy64_from_dbl",   (DL_FUNC) &export_tidy64_cast_to_tidy64_from_dbl, 1},
  {"export_tidy64_cast_to_tidy64_from_int",   (DL_FUNC) &export_tidy64_cast_to_tidy64_from_int, 1},
  {"export_tidy64_cast_to_tidy64_from_lgl",   (DL_FUNC) &export_tidy64_cast_to_tidy64_from_lgl, 1},
  {"export_tidy64_cast_to_dbl_from_tidy64",   (DL_FUNC) &export_tidy64_cast_to_dbl_from_tidy64, 1},
  {"export_tidy64_cast_to_int_from_tidy64",   (DL_FUNC) &export_tidy64_cast_to_int_from_tidy64, 1},
  {"export_tidy64_cast_to_lgl_from_tidy64",   (DL_FUNC) &export_tidy64_cast_to_lgl_from_tidy64, 1},

  // force.h
  {"export_tidy64_force_to_chr_from_tidy64",   (DL_FUNC) &export_tidy64_force_to_chr_from_tidy64, 1},
  {"export_tidy64_force_to_dbl_from_tidy64",   (DL_FUNC) &export_tidy64_force_to_dbl_from_tidy64, 1},
  {"export_tidy64_force_to_int_from_tidy64",   (DL_FUNC) &export_tidy64_force_to_int_from_tidy64, 1},
  {"export_tidy64_force_to_lgl_from_tidy64",   (DL_FUNC) &export_tidy64_force_to_lgl_from_tidy64, 1},
  {"export_tidy64_force_to_tidy64_from_chr",   (DL_FUNC) &export_tidy64_force_to_tidy64_from_chr, 1},
  {"export_tidy64_force_to_tidy64_from_dbl",   (DL_FUNC) &export_tidy64_force_to_tidy64_from_dbl, 1},
  {"export_tidy64_force_to_tidy64_from_int",   (DL_FUNC) &export_tidy64_force_to_tidy64_from_int, 1},
  {"export_tidy64_force_to_tidy64_from_lgl",   (DL_FUNC) &export_tidy64_force_to_tidy64_from_lgl, 1},

  // globals.h
  {"export_tidy64_global_max_chr",             (DL_FUNC) &export_tidy64_global_max_chr, 0},
  {"export_tidy64_global_min_chr",             (DL_FUNC) &export_tidy64_global_min_chr, 0},

  // math.h
  {"export_tidy64_log10",                      (DL_FUNC) &export_tidy64_log10, 1},

  // pack.h
  {"export_tidy64_pack",                       (DL_FUNC) &export_tidy64_pack, 1},
  {"export_tidy64_unpack",                     (DL_FUNC) &export_tidy64_unpack, 1},

  {NULL, NULL, 0}
};

void R_init_tidy64(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
