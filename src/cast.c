#include "cast.h"
#include "utils.h"
#include "tidy64.h"
#include "pack.h"
#include "force.h"

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_tidy64_from_dbl(sexp x) {
  const double* p_x = r_dbl_const_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(tidy64_new(size));
  int64_t* p_out = tidy64_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt = p_x[i];

    if (r_dbl_missing(elt)) {
      p_out[i] = r_int64_na;
      continue;
    }

    if (DBL_OUTSIDE_TIDY64_RANGE(elt)) {
      Rf_error("TODO: Incompatible type error");
    }

    if (DBL_TIDY64_MIGHT_LOSE_PRECISION(elt)) {
      Rf_error("TODO: Incompatible type error");
    }

    const int64_t elt_64 = (int64_t) elt;

    // Catch fractional doubles!
    if (elt != elt_64) {
      Rf_error("TODO: Incompatible type error");
    }

    p_out[i] = elt_64;
  }

  FREE(1);
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
sexp tidy64_cast_to_dbl_from_tidy64(sexp x) {
  const int64_t* p_x = tidy64_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(r_new_vector(r_type_double, size));
  double* p_out = r_dbl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const int64_t elt = p_x[i];

    if (tidy64_missing(elt)) {
      p_out[i] = r_dbl_na;
      continue;
    }

    if (DBL_TIDY64_MIGHT_LOSE_PRECISION(elt)) {
      Rf_error("TODO: Incompatible type error");
    }

    p_out[i] = (double) elt;
  }

  FREE(1);
  return out;
}

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_dbl_from_tidy64(sexp x) {
  return tidy64_cast_to_dbl_from_tidy64(x);
}

// -----------------------------------------------------------------------------

// [[ include("cast.h") ]]
sexp tidy64_cast_to_int_from_tidy64(sexp x) {
  const int64_t* p_x = tidy64_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(r_new_vector(r_type_integer, size));
  int* p_out = r_int_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const int64_t elt = p_x[i];

    if (tidy64_missing(elt)) {
      p_out[i] = r_int_na;
      continue;
    }

    if (TIDY64_OUTSIDE_INT_RANGE(elt)) {
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
  const int64_t* p_x = tidy64_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(r_new_vector(r_type_logical, size));
  int* p_out = r_lgl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const int64_t elt = p_x[i];

    if (tidy64_missing(elt)) {
      p_out[i] = r_lgl_na;
      continue;
    }

    if (elt == 0) {
      p_out[i] = 0;
    } else if (elt == 1) {
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
