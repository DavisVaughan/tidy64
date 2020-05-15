#include "cast.h"
#include "utils.h"
#include "tidy64.h"
#include "pack.h"

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_tidy64_from_dbl(sexp x) {
  r_ssize size = r_length(x);

  sexp left = KEEP(r_new_vector(r_type_double, size));
  sexp right = KEEP(r_new_vector(r_type_double, size));

  double* p_left = r_dbl_deref(left);
  double* p_right = r_dbl_deref(right);

  const double* p_x = r_dbl_const_deref(x);

  for (r_ssize i = 0; i < size; ++i) {
    const double x_elt = p_x[i];

    if (DBL_OUTSIDE_TIDY64_RANGE(x_elt)) {
      Rf_error("TODO: Incompatible type error");
    }

    if (DBL_MIGHT_LOSE_PRECISION(x_elt)) {
      Rf_error("TODO: Incompatible type error");
    }

    const int64_t elt = (int64_t) x_elt;

    // Catch fractional doubles!
    if (elt != x_elt) {
      Rf_error("TODO: Incompatible type error");
    }

    const struct tidy64 out_elt = tidy64_unpack(elt);

    p_left[i] = out_elt.left;
    p_right[i] = out_elt.right;
  }

  sexp out = new_tidy64(left, right);

  FREE(2);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_cast_to_tidy64_from_dbl(sexp x) {
  return tidy64_cast_to_tidy64_from_dbl(x);
}
