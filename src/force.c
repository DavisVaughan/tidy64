#include "force.h"
#include "utils.h"
#include "pack.h"
#include "cnd.h"
#include "tidy64.h"

// For `errno`
#include <errno.h>

// For PRId64
#include <inttypes.h>

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_chr_from_tidy64(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_chr(size));
  sexp* p_out = r_chr_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_chr_na;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    char c_string[TIDY64_MAX_PRINT_SIZE];

    snprintf(c_string, TIDY64_MAX_PRINT_SIZE, "%" PRId64, elt);

    p_out[i] = r_new_string(c_string);
  }

  sexp names = tidy64_peek_names(x);
  r_poke_names(out, names);

  FREE(1);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_chr_from_tidy64(sexp x) {
  return tidy64_force_to_chr_from_tidy64(x);
}

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_dbl_from_tidy64(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_dbl(size));
  double* p_out = r_dbl_deref(out);

  bool warn_precision = false;

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_dbl_na;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    if (!warn_precision && tidy64_to_dbl_from_tidy64_is_oob_precision(elt)) {
      warn_precision = true;
    }

    p_out[i] = (double) elt;
  }

  if (warn_precision) {
    warn_to_dbl_from_tidy64_oob_precision(x);
  }

  sexp names = tidy64_peek_names(x);
  r_poke_names(out, names);

  FREE(1);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_dbl_from_tidy64(sexp x) {
  return tidy64_force_to_dbl_from_tidy64(x);
}

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_int_from_tidy64(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_int(size));
  int* p_out = r_int_deref(out);

  bool warn_na = false;

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_int_na;
      continue;
    }

    const int64_t elt = tidy64_pack(elt_left, elt_right);

    if (tidy64_to_int_from_tidy64_is_oob(elt)) {
      p_out[i] = r_int_na;
      warn_na = true;
      continue;
    }

    p_out[i] = (int) elt;
  }

  if (warn_na) {
    warn_to_int_from_tidy64_oob(x);
  }

  sexp names = tidy64_peek_names(x);
  r_poke_names(out, names);

  FREE(1);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_int_from_tidy64(sexp x) {
  return tidy64_force_to_int_from_tidy64(x);
}

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_lgl_from_tidy64(sexp x) {
  const double* p_left = tidy64_get_left_const_deref(x);
  const double* p_right = tidy64_get_right_const_deref(x);

  r_ssize size = tidy64_size(x);

  sexp out = KEEP(r_new_lgl(size));
  int* p_out = r_lgl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const double elt_left = p_left[i];
    const double elt_right = p_right[i];

    if (r_dbl_missing(elt_left)) {
      p_out[i] = r_lgl_na;
      continue;
    }

    // Allow any non-0 value to be coerced to `TRUE`
    // Hardcoded with known values for performance
    if (elt_left == 0 && elt_right == 0) {
      p_out[i] = 0;
    } else {
      p_out[i] = 1;
    }
  }

  sexp names = tidy64_peek_names(x);
  r_poke_names(out, names);

  FREE(1);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_lgl_from_tidy64(sexp x) {
  return tidy64_force_to_lgl_from_tidy64(x);
}

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_tidy64_from_dbl(sexp x) {
  const double* p_x = r_dbl_const_deref(x);

  r_ssize size = r_length(x);

  sexp left = KEEP(tidy64_new_left(size));
  sexp right = KEEP(tidy64_new_right(size));

  double* p_left = tidy64_deref_left(left);
  double* p_right = tidy64_deref_right(right);

  bool warn_oob = false;

  for (r_ssize i = 0; i < size; ++i) {
    const double elt = p_x[i];

    if (r_dbl_missing(elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    if (tidy64_to_tidy64_from_dbl_is_oob(elt)) {
      warn_oob = true;
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    const int64_t elt_64 = (int64_t) elt;

    const struct tidy64 unpacked = tidy64_unpack(elt_64);

    p_left[i] = unpacked.left;
    p_right[i] = unpacked.right;
  }

  if (warn_oob) {
    warn_to_tidy64_from_dbl_oob(x);
  }

  sexp out = KEEP(tidy64_new(left, right));

  sexp names = r_peek_names(x);
  tidy64_poke_names(out, names);

  FREE(3);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_tidy64_from_dbl(sexp x) {
  return tidy64_force_to_tidy64_from_dbl(x);
}

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_tidy64_from_int(sexp x) {
  const int* p_x = r_int_const_deref(x);

  r_ssize size = r_length(x);

  sexp left = KEEP(tidy64_new_left(size));
  sexp right = KEEP(tidy64_new_right(size));

  double* p_left = tidy64_deref_left(left);
  double* p_right = tidy64_deref_right(right);

  for (r_ssize i = 0; i < size; ++i) {
    const int elt = p_x[i];

    if (r_int_missing(elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    const int64_t elt_64 = (int64_t) elt;

    const struct tidy64 unpacked = tidy64_unpack(elt_64);

    p_left[i] = unpacked.left;
    p_right[i] = unpacked.right;
  }

  sexp out = KEEP(tidy64_new(left, right));

  sexp names = r_peek_names(x);
  tidy64_poke_names(out, names);

  FREE(3);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_tidy64_from_int(sexp x) {
  return tidy64_force_to_tidy64_from_int(x);
}

// -----------------------------------------------------------------------------

// [[ include("force.h") ]]
sexp tidy64_force_to_tidy64_from_lgl(sexp x) {
  const int* p_x = r_lgl_const_deref(x);

  r_ssize size = r_length(x);

  sexp left = KEEP(tidy64_new_left(size));
  sexp right = KEEP(tidy64_new_right(size));

  double* p_left = tidy64_deref_left(left);
  double* p_right = tidy64_deref_right(right);

  for (r_ssize i = 0; i < size; ++i) {
    const int elt = p_x[i];

    if (r_lgl_missing(elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    const bool elt_bool = (bool) elt;

    // Hardcode known values for performance
    if (elt_bool) {
      p_left[i] = 0;
      p_right[i] = 1;
    } else {
      p_left[i] = 0;
      p_right[i] = 0;
    }
  }

  sexp out = KEEP(tidy64_new(left, right));

  sexp names = r_peek_names(x);
  tidy64_poke_names(out, names);

  FREE(3);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_tidy64_from_lgl(sexp x) {
  return tidy64_force_to_tidy64_from_lgl(x);
}

// -----------------------------------------------------------------------------

// `long long` is at least 64-bits, `int64_t` is 64-bits. So we parse as
// `long long` and then ensure that it fits in an `int64_t`.

static bool chr_is_number_with_whitespace(const char* x,
                                          const char* endpointer,
                                          const size_t len);

// [[ include("force.h") ]]
sexp tidy64_force_to_tidy64_from_chr(sexp x) {
  const sexp* p_x = r_chr_const_deref(x);

  r_ssize size = r_length(x);

  sexp left = KEEP(tidy64_new_left(size));
  sexp right = KEEP(tidy64_new_right(size));

  double* p_left = tidy64_deref_left(left);
  double* p_right = tidy64_deref_right(right);

  // Reset errno to 0 in case something else has modified it
  errno = 0;

  bool warn = false;

  for (r_ssize i = 0; i < size; ++i) {
    const sexp x_elt = p_x[i];

    if (r_chr_missing(x_elt)) {
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    const char* x_elt_char = CHAR(x_elt);
    const size_t x_elt_len = strlen(x_elt_char);

    // Must special case `""`
    if (x_elt_len == 0) {
      warn = true;
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    char* endpointer;
    const int base = 10;

    const long long x_elt_ll = strtoll(x_elt_char, &endpointer, base);

    // Captures `> LLONG_MAX` and `< LLONG_MIN`
    if (errno == ERANGE) {
      errno = 0;
      warn = true;
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    // `*endpointer` will be non-null if there are any "leftover" values after
    // `x_elt_ll` was extracted, or if it failed completely. In those cases
    // we check that the leftover values were just whitespace.
    if (*endpointer && !chr_is_number_with_whitespace(x_elt_char, endpointer, x_elt_len)) {
      warn = true;
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    // This would only happen if `x_elt_ll` is the `tidy64_na` or if `long long`
    // is larger than `int64_t`, which is unlikely.
    if (x_elt_ll < TIDY64_MIN || x_elt_ll > TIDY64_MAX) {
      warn = true;
      p_left[i] = r_dbl_na;
      p_right[i] = r_dbl_na;
      continue;
    }

    const int64_t x_elt_64 = (int64_t) x_elt_ll;

    const struct tidy64 unpacked = tidy64_unpack(x_elt_64);

    p_left[i] = unpacked.left;
    p_right[i] = unpacked.right;
  }

  if (warn) {
    Rf_warning("TODO: Warn lossy parse");
  }

  sexp out = KEEP(tidy64_new(left, right));

  sexp names = r_peek_names(x);
  tidy64_poke_names(out, names);

  FREE(3);
  return out;
}

// [[ include("force.h") ]]
sexp export_tidy64_force_to_tidy64_from_chr(sexp x) {
  return tidy64_force_to_tidy64_from_chr(x);
}

static bool chr_is_number_with_whitespace(const char* x,
                                          const char* endpointer,
                                          const size_t len) {
  // If `x` is only whitespace, `endpointer` will point to the first value
  if (x == endpointer) {
    return false;
  }

  // Start 1 past the end. Case of `len == 0` is already taken care of.
  const char* x_from_back = x + len;

  // Must be with single quotes
  const unsigned char whitespace = ' ';

  for (size_t i = len; i > 0; --i) {
    --x_from_back;
    unsigned char x_from_back_data = (unsigned char) *x_from_back;

    if (x_from_back_data != whitespace) {
      ++x_from_back;
      break;
    }
  }

  return x_from_back == endpointer;
}
