#include "cnd.h"
#include "utils.h"

// [[ include("cnd.h") ]]
void warn_dbl_is_outside_tidy64_range(sexp x) {
  sexp syms[2] = {
    syms_x,
    NULL
  };

  sexp args[6] = {
    KEEP(r_protect(x)),
    NULL
  };

  sexp call = KEEP(r_call(syms_warn_dbl_is_outside_tidy64_range, syms, args));

  r_eval(call, tidy64_ns_env);

  UNPROTECT(2);
  return;
}
