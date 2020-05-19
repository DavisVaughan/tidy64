#include "tidy64.h"

// [[ include("tidy64.h") ]]
sexp tidy64_new(r_ssize size) {
  sexp out = KEEP(r_new_dbl(size));

  sexp cls = KEEP(r_new_chr(2));
  sexp* p_cls = r_chr_deref(cls);
  p_cls[0] = r_new_string("tidy64");
  p_cls[1] = r_new_string("vctrs_vctr");

  r_poke_class(out, cls);

  FREE(2);
  return out;
}
