#include "math.h"
#include "tidy64.h"

// [[ include("math.h") ]]
sexp tidy64_log10(sexp x) {
  const int64_t* p_x = tidy64_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(r_new_dbl(size));
  double* p_out = r_dbl_deref(out);

  bool warn_nan = false;

  for (r_ssize i = 0; i < size; ++i) {
    const int64_t x_elt = p_x[i];

    if (tidy64_missing(x_elt)) {
      p_out[i] = r_dbl_na;
      continue;
    }

    // TODO: Check `x_elt` with `tidy64_to_dbl_from_tidy64_might_lose_precision()`?
    // Would that be too annoying?

    const double elt = log10((double) x_elt);

    if (isnan(elt)) {
      p_out[i] = r_dbl_nan;
      warn_nan = true;
    } else {
      p_out[i] = elt;
    }
  }

  if (warn_nan) {
    Rf_warning("TODO: Warning NaN produced!");
  }

  FREE(1);
  return out;
}

// [[ include("math.h") ]]
sexp export_tidy64_log10(sexp x) {
  return tidy64_log10(x);
}
