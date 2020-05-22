#include "utils-names.h"
#include "utils-call.h"
#include "utils-globals.h"

// Callback to R level `names()`
static sexp r_names_dispatch(sexp x) {
  sexp syms[2] = {
    syms_x,
    NULL
  };

  sexp args[2] = {
    KEEP(r_protect(x)),
    NULL
  };

  sexp call = KEEP(r_call(syms_names, syms, args));

  sexp out = KEEP(r_eval(call, R_BaseEnv));

  UNPROTECT(3);
  return out;
}

// [[ include("utils-names.h") ]]
sexp r_common_names(sexp x, sexp y, r_ssize x_size, r_ssize y_size) {
  sexp x_names = KEEP(r_names_dispatch(x));
  sexp y_names = KEEP(r_names_dispatch(y));

  sexp out;

  if (x_size == y_size) {
    out = (x_names == r_null) ? y_names : x_names;
  } else if (x_size == 1) {
    out = y_names;
  } else {
    out = x_names;
  }

  FREE(2);
  return out;
}
