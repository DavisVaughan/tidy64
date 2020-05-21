#include "utils-globals.h"
#include "utils-vec.h"
#include "utils-string.h"

// -----------------------------------------------------------------------------

sexp tidy64_ns_env = NULL;

// -----------------------------------------------------------------------------

sexp syms_x = NULL;
sexp syms_to = NULL;
sexp syms_x_arg = NULL;
sexp syms_to_arg = NULL;
sexp syms_warn_to_tidy64_from_dbl_oob = NULL;
sexp syms_warn_to_int_from_tidy64_oob = NULL;
sexp syms_warn_to_dbl_from_tidy64_oob_precision = NULL;
sexp syms_stop_to_tidy64_from_dbl_oob = NULL;
sexp syms_stop_to_dbl_from_tidy64_oob_precision = NULL;
sexp syms_stop_to_tidy64_from_dbl_lossy_fractional = NULL;
sexp syms_stop_to_int_from_tidy64_oob = NULL;

// -----------------------------------------------------------------------------

sexp names_left_right = NULL;

// -----------------------------------------------------------------------------

sexp classes_tidy64 = NULL;

// -----------------------------------------------------------------------------

sexp fns_quote = NULL;

// -----------------------------------------------------------------------------

void tidy64_initialize_utils_globals(sexp ns) {
  tidy64_ns_env = ns;

  syms_x = Rf_install("x");
  syms_to = Rf_install("to");
  syms_x_arg = Rf_install("x_arg");
  syms_to_arg = Rf_install("to_arg");
  syms_warn_to_tidy64_from_dbl_oob = Rf_install("warn_to_tidy64_from_dbl_oob");
  syms_warn_to_int_from_tidy64_oob = Rf_install("warn_to_int_from_tidy64_oob");
  syms_warn_to_dbl_from_tidy64_oob_precision = Rf_install("warn_to_dbl_from_tidy64_oob_precision");
  syms_stop_to_tidy64_from_dbl_oob = Rf_install("stop_to_tidy64_from_dbl_oob");
  syms_stop_to_dbl_from_tidy64_oob_precision = Rf_install("stop_to_dbl_from_tidy64_oob_precision");
  syms_stop_to_tidy64_from_dbl_lossy_fractional = Rf_install("stop_to_tidy64_from_dbl_lossy_fractional");
  syms_stop_to_int_from_tidy64_oob = Rf_install("stop_to_int_from_tidy64_oob");

  names_left_right = r_new_shared_vector(r_type_character, 2);
  r_chr_set(names_left_right, 0, r_new_string("left"));
  r_chr_set(names_left_right, 1, r_new_string("right"));

  classes_tidy64 = r_new_shared_vector(r_type_character, 3);
  r_chr_set(classes_tidy64, 0, r_new_string("tidy64"));
  r_chr_set(classes_tidy64, 1, r_new_string("vctrs_rcrd"));
  r_chr_set(classes_tidy64, 2, r_new_string("vctrs_vctr"));

  fns_quote = Rf_findVar(Rf_install("quote"), R_BaseEnv);
}
