#include "cast.h"
#include "utils.h"
#include "pack.h"
#include "cnd.h"
#include "tidy64.h"
#include "force.h"

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_tidy64_from_dbl(sexp x) {
  const double* p_x = r_dbl_const_deref(x);

  r_ssize size = r_length(x);

  sexp left = KEEP(tidy64_new_left(size));
  sexp right = KEEP(tidy64_new_right(size));

  double* p_left = tidy64_deref_left(left);
  double* p_right = tidy64_deref_right(right);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt = p_x[i];

    if (r_dbl_missing(elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    if (tidy64_dbl_is_outside_tidy64_range(elt)) {
      Rf_error("TODO: Incompatible type error");
    }

    const int64_t elt_64 = (int64_t) elt;

    // Catch fractional doubles!
    if (elt != elt_64) {
      Rf_error("TODO: Incompatible type error");
    }

    const struct tidy64 unpacked = tidy64_unpack(elt_64);

    p_left[i] = unpacked.left;
    p_right[i] = unpacked.right;
  }

  sexp out = tidy64_new(left, right);

  FREE(2);
  return out;
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_tidy64_from_dbl(sexp x) {
  return tidy64_cast_to_tidy64_from_dbl(x);
}

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_tidy64_from_int(sexp x) {
  return tidy64_force_to_tidy64_from_int(x);
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_tidy64_from_int(sexp x) {
  return tidy64_cast_to_tidy64_from_int(x);
}

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_tidy64_from_lgl(sexp x) {
  return tidy64_force_to_tidy64_from_lgl(x);
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_tidy64_from_lgl(sexp x) {
  return tidy64_cast_to_tidy64_from_lgl(x);
}

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_dbl_from_tidy64(sexp x, sexp to, sexp x_arg, sexp to_arg) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_vector(r_type_double, size));
  double* p_out = r_dbl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_dbl_na;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    if (tidy64_to_dbl_from_tidy64_might_lose_precision(elt)) {
      stop_to_dbl_from_tidy64_might_lose_precision(x, to, x_arg, to_arg);
    }

    p_out[i] = (double) elt;
  }

  FREE(1);
  return out;
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_dbl_from_tidy64(sexp x, sexp to, sexp x_arg, sexp to_arg) {
  return tidy64_cast_to_dbl_from_tidy64(x, to, x_arg, to_arg);
}

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_int_from_tidy64(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_vector(r_type_integer, size));
  int* p_out = r_int_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_int_na;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    if (tidy64_is_outside_int_range(elt)) {
      Rf_error("TODO: Incompatible type error.");
    }

    p_out[i] = (int) elt;
  }

  FREE(1);
  return out;
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_int_from_tidy64(sexp x) {
  return tidy64_cast_to_int_from_tidy64(x);
}

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_lgl_from_tidy64(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_vector(r_type_logical, size));
  int* p_out = r_lgl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_lgl_na;
      continue;
    }

    // Hardcoded for performance
    if (elt_left != 0) {
      Rf_error("TODO: Incompatible type error.");
    }

    if (elt_right == 0) {
      p_out[i] = 0;
    } else if (elt_right == 1) {
      p_out[i] = 1;
    } else {
      Rf_error("TODO: Incompatible type error.");
    }
  }

  FREE(1);
  return out;
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_lgl_from_tidy64(sexp x) {
  return tidy64_cast_to_lgl_from_tidy64(x);
}
