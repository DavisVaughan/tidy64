#include "force.h"
#include "utils.h"
#include "tidy64.h"
#include "pack.h"

// -----------------------------------------------------------------------------

// - 19 comes from printing out `INT64_MAX` and counting the number of digits
// - `+ 1` because it could be negative and have a `-`
// - TODO: And `+ 1` for trailing null?
#define TIDY64_MAX_PRINT_SIZE (19 + 1 + 1)

// [[ include("force.h") ]]
sexp tidy64_force_to_chr_from_tidy64(sexp x) {
  sexp left = tidy64_get_left(x);
  sexp right = tidy64_get_right(x);

  const double* p_left = r_dbl_const_deref(left);
  const double* p_right = r_dbl_const_deref(right);

  r_ssize size = r_length(left);

  sexp out = KEEP(r_new_chr(size));
  sexp* p_out = r_chr_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_chr_na;
      continue;
    }

    const struct tidy64 elt = {
      .left = elt_left,
      .right = elt_right
    };

    const int64_t elt_out = tidy64_pack(elt);

    char c_string[TIDY64_MAX_PRINT_SIZE];

    snprintf(c_string, TIDY64_MAX_PRINT_SIZE, "%" PRId64, elt_out);

    p_out[i] = r_new_string(c_string);
  }

  FREE(1);
  return out;
}

#undef TIDY64_MAX_PRINT_SIZE

// [[ include("force.h") ]]
sexp export_tidy64_force_to_chr_from_tidy64(sexp x) {
  return tidy64_force_to_chr_from_tidy64(x);
}

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_tidy64_from_dbl(sexp x) {
  r_ssize size = r_length(x);

  sexp left = KEEP(r_new_vector(r_type_double, size));
  sexp right = KEEP(r_new_vector(r_type_double, size));

  double* p_left = r_dbl_deref(left);
  double* p_right = r_dbl_deref(right);

  const double* p_x = r_dbl_const_deref(x);

  bool warn_na = false;
  bool warn_precision = false;
  r_ssize warn_na_loc = 0;
  r_ssize warn_precision_loc = 0;

  for (r_ssize i = 0; i < size; ++i) {
    const double x_elt = p_x[i];

    if (DBL_OUTSIDE_TIDY64_RANGE(x_elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      warn_na = true;
      warn_na_loc = i + 1;
      continue;
    }

    if (!warn_precision && DBL_MIGHT_LOSE_PRECISION(x_elt)) {
      warn_precision = true;
      warn_precision_loc = i + 1;
    }

    const int64_t elt = (int64_t) x_elt;

    const struct tidy64 out_elt = tidy64_unpack(elt);

    p_left[i] = out_elt.left;
    p_right[i] = out_elt.right;
  }

  if (warn_na) {
    Rf_warning("Element %td is outside the range of tidy64 values, returning `NA`.", warn_na_loc);
  }
  if (warn_precision) {
    Rf_warning(
      "Element %td is outside the range of double values that can be stored in a tidy64 "
      "with a guarantee that no precision is lost. Conversion will continue, "
      "but check the values!",
      warn_precision_loc
    );
  }

  sexp out = new_tidy64(left, right);

  FREE(2);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_tidy64_from_dbl(sexp x) {
  return tidy64_force_to_tidy64_from_dbl(x);
}

// -----------------------------------------------------------------------------
