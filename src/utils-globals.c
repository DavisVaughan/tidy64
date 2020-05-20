#include "utils-globals.h"
#include "utils-vec.h"
#include "utils-string.h"

// -----------------------------------------------------------------------------

sexp names_left_right = NULL;

// -----------------------------------------------------------------------------

sexp classes_tidy64 = NULL;

// -----------------------------------------------------------------------------

void tidy64_initialize_utils_globals(sexp ns) {
  names_left_right = r_new_shared_vector(r_type_character, 2);
  r_chr_set(names_left_right, 0, r_new_string("left"));
  r_chr_set(names_left_right, 1, r_new_string("right"));

  classes_tidy64 = r_new_shared_vector(r_type_character, 3);
  r_chr_set(classes_tidy64, 0, r_new_string("tidy64"));
  r_chr_set(classes_tidy64, 1, r_new_string("vctrs_rcrd"));
  r_chr_set(classes_tidy64, 2, r_new_string("vctrs_vctr"));
}
