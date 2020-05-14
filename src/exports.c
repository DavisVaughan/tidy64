#include "exports.h"
#include "utils.h"

// -----------------------------------------------------------------------------
#include "pack.h"

sexp export_tidy64_pack(sexp x) {
  if (r_typeof(x) != r_type_list) {
    r_abort("Internal error: `x` must have type list.");
  }
  if (r_length(x) != 2) {
    r_abort("Internal error: `x` must have size 2.");
  }

  sexp first = r_list_get(x, 0);
  sexp last = r_list_get(x, 1);

  const r_ssize size = r_length(first);

  if (r_typeof(first) != r_type_double) {
    r_abort("Internal error: `first` must have type double.");
  }
  if (r_typeof(last) != r_type_double) {
    r_abort("Internal error: `last` must have type double.");
  }
  if (r_length(first) != r_length(last)) {
    r_abort("Internal error: `first` and `last` must have the same size.");
  }

  sexp out = KEEP(r_new_vector(r_type_double, size));
  double* p_out = r_dbl_deref(out);

  const double* p_first = r_dbl_const_deref(first);
  const double* p_last = r_dbl_const_deref(last);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_first = p_first[i];
    const double elt_last = p_last[i];

    const struct tidy64 elt = {
      .first = elt_first,
      .last = elt_last
    };

    int64_t out_elt = tidy64_pack(elt);

    // Push into a double.
    // This is only for testing so assume it can hold it without
    // loss of precision.
    p_out[i] = (double) out_elt;
  }

  FREE(1);
  return out;
}

sexp export_tidy64_unpack(sexp x) {
  if (r_typeof(x) != r_type_double) {
    r_abort("Internal error: `x` must have type double.");
  }

  r_ssize size = r_length(x);

  sexp first = KEEP(r_new_vector(r_type_double, size));
  sexp last = KEEP(r_new_vector(r_type_double, size));

  double* p_first = r_dbl_deref(first);
  double* p_last = r_dbl_deref(last);

  const double* p_x = r_dbl_deref(x);

  for (r_ssize i = 0; i < size; ++i) {
    const double x_elt = p_x[i];

    // Assume it comes from a double that can fit without loss of precision.
    // This is only for testing.
    const int64_t elt = (int64_t) x_elt;

    const struct tidy64 out_elt = tidy64_unpack(elt);

    p_first[i] = out_elt.first;
    p_last[i] = out_elt.last;
  }

  sexp out = KEEP(r_new_vector(r_type_list, 2));
  r_list_set(out, 0, first);
  r_list_set(out, 1, last);

  FREE(3);
  return out;
}
