#include "math.h"
#include "tidy64.h"
#include "pack.h"

// [[ include("math.h") ]]
sexp tidy64_log10(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_dbl(size));
  double* p_out = r_dbl_deref(out);

  bool warn_nan = false;

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_dbl_na;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    // TODO: Check `x_elt` with `tidy64_to_dbl_from_tidy64_is_oob_precision()`?
    // Would that be too annoying?

    // TODO: Cast to `long double` then cast result to `double`? Would have
    // better precision on Mac / Linux, but Windows probably maps long double
    // to double.
    const double elt_out = log10((double) elt);

    if (isnan(elt_out)) {
      p_out[i] = r_dbl_nan;
      warn_nan = true;
    } else {
      p_out[i] = elt_out;
    }
  }

  if (warn_nan) {
    Rf_warning("TODO: Warning NaN produced!");
  }

  sexp names = tidy64_peek_names(x);
  r_poke_names(out, names);

  FREE(1);
  return out;
}

// [[ include("math.h") ]]
sexp export_tidy64_log10(sexp x) {
  return tidy64_log10(x);
}
