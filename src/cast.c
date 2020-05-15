#include "cast.h"
#include "utils.h"
#include "tidy64.h"
#include "pack.h"

// -----------------------------------------------------------------------------

// - 19 comes from printing out `INT64_MAX` and counting the number of digits
// - `+ 1` because it could be negative and have a `-`
// - TODO: And `+ 1` for trailing null?
#define TIDY64_MAX_PRINT_SIZE (19 + 1 + 1)

// [[ include("cast.h") ]]
sexp tidy64_cast_to_chr_from_tidy64(sexp x) {
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

// [[ include("cast.h") ]]
sexp export_tidy64_cast_to_chr_from_tidy64(sexp x) {
  return tidy64_cast_to_chr_from_tidy64(x);
}

// -----------------------------------------------------------------------------
