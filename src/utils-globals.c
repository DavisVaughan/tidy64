#include "utils-globals.h"
#include "utils-vec.h"
#include "utils-string.h"

// -----------------------------------------------------------------------------

sexp tidy64_ns_env = NULL;

// -----------------------------------------------------------------------------

sexp syms_x = NULL;
sexp syms_warn_dbl_is_outside_tidy64_range = NULL;

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
  syms_warn_dbl_is_outside_tidy64_range = Rf_install("warn_dbl_is_outside_tidy64_range");

  names_left_right = r_new_shared_vector(r_type_character, 2);
  r_chr_set(names_left_right, 0, r_new_string("left"));
  r_chr_set(names_left_right, 1, r_new_string("right"));

  classes_tidy64 = r_new_shared_vector(r_type_character, 3);
  r_chr_set(classes_tidy64, 0, r_new_string("tidy64"));
  r_chr_set(classes_tidy64, 1, r_new_string("vctrs_rcrd"));
  r_chr_set(classes_tidy64, 2, r_new_string("vctrs_vctr"));

  fns_quote = Rf_findVar(Rf_install("quote"), R_BaseEnv);
}
