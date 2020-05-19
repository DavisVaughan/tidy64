#include "force.h"
#include "utils.h"
#include "tidy64.h"
#include <errno.h>
#include <ctype.h>

// -----------------------------------------------------------------------------

// - 19 comes from printing out `INT64_MAX` and counting the number of digits
// - `+ 1` because it could be negative and have a `-`
// - TODO: And `+ 1` for trailing null?
#define TIDY64_MAX_PRINT_SIZE (19 + 1 + 1)

// [[ include("force.h") ]]
sexp tidy64_force_to_chr_from_tidy64(sexp x) {
  const int64_t* p_x = tidy64_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(r_new_chr(size));
  sexp* p_out = r_chr_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const int64_t elt = p_x[i];

    if (tidy64_missing(elt)) {
      p_out[i] = r_chr_na;
      continue;
    }

    char c_string[TIDY64_MAX_PRINT_SIZE];

    snprintf(c_string, TIDY64_MAX_PRINT_SIZE, "%" PRId64, elt);

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
sexp tidy64_force_to_dbl_from_tidy64(sexp x) {
  const int64_t* p_x = tidy64_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(r_new_vector(r_type_double, size));
  double* p_out = r_dbl_deref(out);

  bool warn_precision = false;

  for (r_ssize i = 0; i < size; ++i) {
    const int64_t elt = p_x[i];

    if (tidy64_missing(elt)) {
      p_out[i] = r_dbl_na;
      continue;
    }

    if (!warn_precision && tidy64_to_dbl_from_tidy64_might_lose_precision(elt)) {
      warn_precision = true;
    }

    p_out[i] = (double) elt;
  }

  if (warn_precision) {
    Rf_warning("TODO: Lost precision warning");
  }

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
  const int64_t* p_x = tidy64_deref(x);

  r_ssize size = r_length(x);

  sexp out = KEEP(r_new_vector(r_type_integer, size));
  int* p_out = r_int_deref(out);

  bool warn_na = false;

  for (r_ssize i = 0; i < size; ++i) {
    const int64_t elt = p_x[i];

    if (tidy64_missing(elt)) {
      p_out[i] = r_int_na;
      continue;
    }

    if (tidy64_is_outside_int_range(elt)) {
      p_out[i] = r_int_na;
      warn_na = true;
      continue;
    }

    p_out[i] = (int) elt;
  }

  if (warn_na) {
    Rf_warning("TODO: OOB warning. NA returned.");
  }

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

    // Allow any non-0 value to be coerced to `TRUE`
    p_out[i] = elt ? 1 : 0;
  }

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

  sexp out = KEEP(tidy64_new(size));
  int64_t* p_out = tidy64_deref(out);

  bool warn_na = false;
  bool warn_precision = false;
  r_ssize warn_na_loc = 0;
  r_ssize warn_precision_loc = 0;

  for (r_ssize i = 0; i < size; ++i) {
    const double elt = p_x[i];

    if (r_dbl_missing(elt)) {
      p_out[i] = tidy64_na;
      continue;
    }

    if (tidy64_dbl_is_outside_tidy64_range(elt)) {
      warn_na = true;
      warn_na_loc = i + 1;
      p_out[i] = tidy64_na;
      continue;
    }

    if (!warn_precision && tidy64_to_tidy64_from_dbl_might_lose_precision(elt)) {
      warn_precision = true;
      warn_precision_loc = i + 1;
    }

    p_out[i] = (int64_t) elt;
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

  FREE(1);
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

  sexp out = KEEP(tidy64_new(size));
  int64_t* p_out = tidy64_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const int elt = p_x[i];

    if (r_int_missing(elt)) {
      p_out[i] = tidy64_na;
    } else {
      p_out[i] = (int64_t) elt;
    }
  }

  FREE(1);
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

  sexp out = KEEP(tidy64_new(size));
  int64_t* p_out = tidy64_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    const int elt = p_x[i];

    if (r_lgl_missing(elt)) {
      p_out[i] = tidy64_na;
    } else {
      p_out[i] = (int64_t) elt;
    }
  }

  FREE(1);
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

  sexp out = KEEP(tidy64_new(size));
  int64_t* p_out = tidy64_deref(out);

  // Reset errno to 0 in case something else has modified it
  errno = 0;

  bool warn = false;

  for (r_ssize i = 0; i < size; ++i) {
    const sexp x_elt = p_x[i];

    if (r_chr_missing(x_elt)) {
      p_out[i] = tidy64_na;
      continue;
    }

    const char* x_elt_char = CHAR(x_elt);
    const size_t x_elt_len = strlen(x_elt_char);

    // Must special case `""`
    if (x_elt_len == 0) {
      warn = true;
      p_out[i] = tidy64_na;
      continue;
    }

    char* endpointer;
    const int base = 10;

    const long long x_elt_ll = strtoll(x_elt_char, &endpointer, base);

    // Captures `> LLONG_MAX` and `< LLONG_MIN`
    if (errno == ERANGE) {
      errno = 0;
      warn = true;
      p_out[i] = tidy64_na;
      continue;
    }

    // `*endpointer` will be non-null if there are any "leftover" values after
    // `x_elt_ll` was extracted, or if it failed completely. In those cases
    // we check that the leftover values were just whitespace.
    if (*endpointer && !chr_is_number_with_whitespace(x_elt_char, endpointer, x_elt_len)) {
      warn = true;
      p_out[i] = tidy64_na;
      continue;
    }

    // This would only happen if `x_elt_ll` is the `tidy64_na` or if `long long`
    // is larger than `int64_t`, which is unlikely.
    if (x_elt_ll < TIDY64_MIN || x_elt_ll > TIDY64_MAX) {
      warn = true;
      p_out[i] = tidy64_na;
      continue;
    }

    const int64_t out_elt = (int64_t) x_elt_ll;

    p_out[i] = out_elt;
  }

  if (warn) {
    Rf_warning("TODO: Warn lossy parse");
  }

  FREE(1);
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
