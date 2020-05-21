#include "cnd.h"
#include "utils.h"
#include "tidy64.h"
#include "pack.h"

// -----------------------------------------------------------------------------

// [[ include("cnd.h") ]]
void warn_to_tidy64_from_dbl_oob(sexp x) {
  sexp syms[2] = {
    syms_x,
    NULL
  };

  sexp args[2] = {
    KEEP(r_protect(x)),
    NULL
  };

  sexp call = KEEP(r_call(syms_warn_to_tidy64_from_dbl_oob, syms, args));
  r_eval(call, tidy64_ns_env);

  UNPROTECT(2);
  return;
}

// -----------------------------------------------------------------------------

// [[ include("cnd.h") ]]
void warn_to_int_from_tidy64_oob(sexp x) {
  sexp syms[2] = {
    syms_x,
    NULL
  };

  sexp args[2] = {
    KEEP(r_protect(x)),
    NULL
  };

  sexp call = KEEP(r_call(syms_warn_to_int_from_tidy64_oob, syms, args));
  r_eval(call, tidy64_ns_env);

  UNPROTECT(2);
  return;
}

// -----------------------------------------------------------------------------

// [[ include("cnd.h") ]]
__attribute__((noreturn))
void stop_to_tidy64_from_dbl_oob(sexp x, sexp to, sexp x_arg, sexp to_arg) {
  sexp syms[5] = {
    syms_x,
    syms_to,
    syms_x_arg,
    syms_to_arg,
    NULL
  };

  sexp args[5] = {
    KEEP(r_protect(x)),
    KEEP(r_protect(to)),
    KEEP(r_protect(x_arg)),
    KEEP(r_protect(to_arg)),
    NULL
  };

  sexp call = KEEP(r_call(syms_stop_to_tidy64_from_dbl_oob, syms, args));
  r_eval(call, tidy64_ns_env);

  never_reached("stop_to_tidy64_from_dbl_oob");
}

// -----------------------------------------------------------------------------

// [[ include("cnd.h") ]]
__attribute__((noreturn))
void stop_to_dbl_from_tidy64_oob_precision(sexp x, sexp to, sexp x_arg, sexp to_arg) {
  sexp syms[5] = {
    syms_x,
    syms_to,
    syms_x_arg,
    syms_to_arg,
    NULL
  };

  sexp args[5] = {
    KEEP(r_protect(x)),
    KEEP(r_protect(to)),
    KEEP(r_protect(x_arg)),
    KEEP(r_protect(to_arg)),
    NULL
  };

  sexp call = KEEP(r_call(syms_stop_to_dbl_from_tidy64_oob_precision, syms, args));
  r_eval(call, tidy64_ns_env);

  never_reached("stop_to_dbl_from_tidy64_oob_precision");
}

static sexp tidy64_detect_to_dbl_from_tidy64_oob_precision(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_lgl(size));
  int* p_out = r_lgl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = false;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    p_out[i] = tidy64_to_dbl_from_tidy64_is_oob_precision(elt);
  }

  FREE(1);
  return out;
}

// [[ include("cnd.h") ]]
sexp export_tidy64_detect_to_dbl_from_tidy64_oob_precision(sexp x) {
  return tidy64_detect_to_dbl_from_tidy64_oob_precision(x);
}

// -----------------------------------------------------------------------------

// [[ include("cnd.h") ]]
__attribute__((noreturn))
void stop_to_tidy64_from_dbl_lossy_fractional(sexp x, sexp to, sexp x_arg, sexp to_arg) {
  sexp syms[5] = {
    syms_x,
    syms_to,
    syms_x_arg,
    syms_to_arg,
    NULL
  };

  sexp args[5] = {
    KEEP(r_protect(x)),
    KEEP(r_protect(to)),
    KEEP(r_protect(x_arg)),
    KEEP(r_protect(to_arg)),
    NULL
  };

  sexp call = KEEP(r_call(syms_stop_to_tidy64_from_dbl_lossy_fractional, syms, args));
  r_eval(call, tidy64_ns_env);

  never_reached("stop_to_tidy64_from_dbl_lossy_fractional");
}

// -----------------------------------------------------------------------------

// [[ include("cnd.h") ]]
__attribute__((noreturn))
void stop_to_int_from_tidy64_oob(sexp x, sexp to, sexp x_arg, sexp to_arg) {
  sexp syms[5] = {
    syms_x,
    syms_to,
    syms_x_arg,
    syms_to_arg,
    NULL
  };

  sexp args[5] = {
    KEEP(r_protect(x)),
    KEEP(r_protect(to)),
    KEEP(r_protect(x_arg)),
    KEEP(r_protect(to_arg)),
    NULL
  };

  sexp call = KEEP(r_call(syms_stop_to_int_from_tidy64_oob, syms, args));
  r_eval(call, tidy64_ns_env);

  never_reached("stop_to_int_from_tidy64_oob");
}

static sexp tidy64_detect_to_int_from_tidy64_oob(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_lgl(size));
  int* p_out = r_lgl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = false;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    p_out[i] = tidy64_to_int_from_tidy64_is_oob(elt);
  }

  FREE(1);
  return out;
}

// [[ include("cnd.h") ]]
sexp export_tidy64_detect_to_int_from_tidy64_oob(sexp x) {
  return tidy64_detect_to_int_from_tidy64_oob(x);
}
