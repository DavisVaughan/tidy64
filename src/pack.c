#include "pack.h"
#include "utils.h"

// -----------------------------------------------------------------------------

// [[ include("pack.h") ]]
sexp export_tidy64_pack(sexp x) {
  if (r_typeof(x) != r_type_list) {
    r_abort("Internal error: `x` must have type list.");
  }
  if (r_length(x) != 2) {
    r_abort("Internal error: `x` must have size 2.");
  }

  sexp left = r_list_get(x, 0);
  sexp right = r_list_get(x, 1);

  const r_ssize size = r_length(left);

  if (r_typeof(left) != r_type_double) {
    r_abort("Internal error: `left` must have type double.");
  }
  if (r_typeof(right) != r_type_double) {
    r_abort("Internal error: `right` must have type double.");
  }
  if (size != r_length(right)) {
    r_abort("Internal error: `left` and `right` must have the same size.");
  }

  const double* p_left = r_dbl_const_deref(left);
  const double* p_right = r_dbl_const_deref(right);

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
    p_out[i] = (double) out_elt;
  }

  FREE(1);
  return out;
}

// -----------------------------------------------------------------------------

// [[ include("pack.h") ]]
sexp export_tidy64_unpack(sexp x) {
  if (r_typeof(x) != r_type_double) {
    r_abort("Internal error: `x` must have type double.");
  }

  r_ssize size = r_length(x);

  sexp left = KEEP(r_new_vector(r_type_double, size));
  sexp right = KEEP(r_new_vector(r_type_double, size));

  double* p_left = r_dbl_deref(left);
  double* p_right = r_dbl_deref(right);

  const double* p_x = r_dbl_deref(x);

  bool warn_na = false;
  bool warn_precision = false;
  r_ssize warn_na_loc = 0;
  r_ssize warn_precision_loc = 0;

  for (r_ssize i = 0; i < size; ++i) {
    const double x_elt = p_x[i];

    if (tidy64_dbl_is_outside_tidy64_range(x_elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      warn_na = true;
      warn_na_loc = i + 1;
      continue;
    }

    if (!warn_precision && tidy64_to_tidy64_from_dbl_might_lose_precision(x_elt)) {
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

  sexp out = KEEP(r_new_vector(r_type_list, 2));
  r_list_set(out, 0, left);
  r_list_set(out, 1, right);

  FREE(3);
  return out;
}
