#include "tidy64.h"

// [[ include("tidy64.h") ]]
sexp tidy64_new(sexp left, sexp right) {
  sexp out = KEEP(r_new_list(2));

  r_list_set(out, 0, left);
  r_list_set(out, 1, right);

  r_poke_names(out, names_left_right);
  r_poke_class(out, classes_tidy64);

  FREE(1);
  return out;
}
