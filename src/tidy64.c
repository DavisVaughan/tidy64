#include "tidy64.h"

// [[ include("tidy64.h") ]]
sexp tidy64_new(sexp left, sexp right) {
  sexp names = KEEP(r_new_chr(2));
  sexp* p_names = r_chr_deref(names);
  p_names[0] = r_new_string("left");
  p_names[1] = r_new_string("right");

  sexp cls = KEEP(r_new_chr(3));
  sexp* p_cls = r_chr_deref(cls);
  p_cls[0] = r_new_string("tidy64");
  p_cls[1] = r_new_string("vctrs_rcrd");
  p_cls[2] = r_new_string("vctrs_vctr");

  sexp out = KEEP(r_new_list(2));

  r_list_set(out, 0, left);
  r_list_set(out, 1, right);

  r_poke_names(out, names);
  r_poke_class(out, cls);

  FREE(3);
  return out;
}
