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

    if (DBL_TIDY64_MIGHT_LOSE_PRECISION(x_elt)) {
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

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_tidy64_from_dbl(sexp x) {
  return tidy64_cast_to_tidy64_from_dbl(x);
}

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_dbl_from_tidy64(sexp x) {
  sexp left = tidy64_get_left(x);
  sexp right = tidy64_get_right(x);

  const double* p_left = r_dbl_const_deref(left);
  const double* p_right = r_dbl_const_deref(right);

  r_ssize size = r_length(left);

  sexp out = KEEP(r_new_vector(r_type_double, size));
  double* p_out = r_dbl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    const struct tidy64 elt = {
      .left = elt_left,
      .right = elt_right
    };

    int64_t out_elt = tidy64_pack(elt);

    if (DBL_TIDY64_MIGHT_LOSE_PRECISION(out_elt)) {
      Rf_error("TODO: Incompatible type error");
    }

    p_out[i] = (double) out_elt;
  }

  FREE(1);
  return out;
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_dbl_from_tidy64(sexp x) {
  return tidy64_cast_to_dbl_from_tidy64(x);
}
