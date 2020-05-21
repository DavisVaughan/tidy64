#include "pack.h"
#include "utils.h"
#include "cnd.h"

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

    int64_t out_elt = tidy64_pack(elt_left, elt_right);
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

  bool warn_oob = false;

  for (r_ssize i = 0; i < size; ++i) {
    const double x_elt = p_x[i];

    if (tidy64_to_tidy64_from_dbl_oob(x_elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      warn_oob = true;
      continue;
    }

    const int64_t elt = (int64_t) x_elt;

    const struct tidy64 out_elt = tidy64_unpack(elt);

    p_left[i] = out_elt.left;
    p_right[i] = out_elt.right;
  }

  if (warn_oob) {
    warn_to_tidy64_from_dbl_oob(x);
  }

  sexp out = KEEP(r_new_vector(r_type_list, 2));
  r_list_set(out, 0, left);
  r_list_set(out, 1, right);

  FREE(3);
  return out;
}
