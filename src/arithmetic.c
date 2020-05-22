#include "arithmetic.h"
#include "utils.h"
#include "tidy64.h"
#include "pack.h"

// -----------------------------------------------------------------------------

static inline bool tidy64_plus_int64_int64_is_oob(int64_t x, int64_t y) {
  return ((y > 0) && (x > (TIDY64_MAX - y))) ||
         ((y < 0) && (x < (TIDY64_MIN - y)));
}

static inline bool tidy64_minus_int64_int64_is_oob(int64_t x, int64_t y) {
  return ((y < 0) && (x > (TIDY64_MAX + y))) ||
         ((y > 0) && (x < (TIDY64_MIN + y)));
}

// Original inspiration:
// https://codereview.stackexchange.com/questions/98791/safe-multiplication-of-two-64-bit-signed-integers
// Simplified equivalent that this is based on:
// https://github.com/JoshuaWise/integer/blob/b8484943180212a6d17d5ad69c336b787354b68e/src/integer.cpp#L146-L152

// Proof:
// - Rearrangements are done to avoid possible division by 0.
// - The case where both inputs are either negative or zero requires an
//   additional non-zero check.
// - Note that when we divide by a negative in the rearrangement step of the
//   case where both inputs are negative or zero, we must flip the comparison
//   sign.
//
// Signs             |  Overflows if  |  Rearranged
// ----------------------------------------------
// [x  > 0, y  > 0]  |  x * y > MAX   |  x > MAX / y
// [x  > 0, y <= 0]  |  x * y < MIN   |  y < MIN / x
// [x <= 0, y  > 0]  |  x * y < MIN   |  x < MIN / y
// [x <= 0, y <= 0]  |  x * y > MAX   |  x != 0 && y < MAX / x

static inline bool tidy64_multiply_int64_int64_is_oob(int64_t x, int64_t y) {
  if (x > 0) {
    if (y > 0) {
      return x > TIDY64_MAX / y;
    } else {
      return y < TIDY64_MIN / x;
    }
  } else {
    if (y > 0) {
      return x < TIDY64_MIN / y;
    } else {
      return x != 0 && y < TIDY64_MAX / x;
    }
  }
}

// -----------------------------------------------------------------------------

static inline const struct tidy64 tidy64_plus_int64_int64_one(int64_t x,
                                                              int64_t y,
                                                              bool* p_warn) {
  if (tidy64_plus_int64_int64_is_oob(x, y)) {
    *p_warn = true;
    return tidy64_new_na();
  }

  const int64_t out_elt = x + y;
  return tidy64_unpack(out_elt);
}

static inline const struct tidy64 tidy64_minus_int64_int64_one(int64_t x,
                                                               int64_t y,
                                                               bool* p_warn) {
  if (tidy64_minus_int64_int64_is_oob(x, y)) {
    *p_warn = true;
    return tidy64_new_na();
  }

  const int64_t out_elt = x - y;
  return tidy64_unpack(out_elt);
}

static inline const struct tidy64 tidy64_multiply_int64_int64_one(int64_t x,
                                                                  int64_t y,
                                                                  bool* p_warn) {
  if (tidy64_multiply_int64_int64_is_oob(x, y)) {
    *p_warn = true;
    return tidy64_new_na();
  }

  const int64_t out_elt = x * y;
  return tidy64_unpack(out_elt);
}

static inline double tidy64_plus_ld_ld_one(long double x, long double y) {
  return (double) (x + y);
}

static inline double tidy64_minus_ld_ld_one(long double x, long double y) {
  return (double) (x - y);
}

static inline double tidy64_multiply_ld_ld_one(long double x, long double y) {
  return (double) (x * y);
}

// -----------------------------------------------------------------------------

#define TIDY64_OP_TIDY64_TIDY64_IMPL(OP_ONE) {                                 \
  const double* p_x_left = tidy64_get_left_const_deref(x);                     \
  const double* p_x_right = tidy64_get_right_const_deref(x);                   \
                                                                               \
  const double* p_y_left = tidy64_get_left_const_deref(y);                     \
  const double* p_y_right = tidy64_get_right_const_deref(y);                   \
                                                                               \
  sexp left = KEEP(tidy64_new_left(size));                                     \
  sexp right = KEEP(tidy64_new_right(size));                                   \
                                                                               \
  double* p_left = tidy64_deref_left(left);                                    \
  double* p_right = tidy64_deref_right(right);                                 \
                                                                               \
  const bool x_recycle = x_size == 1;                                          \
  const bool y_recycle = y_size == 1;                                          \
                                                                               \
  bool warn_oob = false;                                                       \
                                                                               \
  for (r_ssize i = 0; i < size; ++i) {                                         \
    const double x_elt_left = x_recycle ? p_x_left[0] : p_x_left[i];           \
    const double x_elt_right = x_recycle ? p_x_right[0] : p_x_right[i];        \
    const double y_elt_left = y_recycle ? p_y_left[0] : p_y_left[i];           \
    const double y_elt_right = y_recycle ? p_y_right[0] : p_y_right[i];        \
                                                                               \
    if (r_dbl_missing(x_elt_left) || r_dbl_missing(y_elt_left)) {              \
      p_left[i] = r_dbl_na;                                                    \
      p_right[i] = r_dbl_na;                                                   \
      continue;                                                                \
    }                                                                          \
                                                                               \
    const int64_t x_elt_64 = tidy64_pack(x_elt_left, x_elt_right);             \
    const int64_t y_elt_64 = tidy64_pack(y_elt_left, y_elt_right);             \
                                                                               \
    const struct tidy64 out_elt = OP_ONE(x_elt_64, y_elt_64, &warn_oob);       \
                                                                               \
    p_left[i] = out_elt.left;                                                  \
    p_right[i] = out_elt.right;                                                \
  }                                                                            \
                                                                               \
  if (warn_oob) {                                                              \
    Rf_warning("TODO: Warn OOB, returning NA");                                \
  }                                                                            \
                                                                               \
  sexp out = KEEP(tidy64_new(left, right));                                    \
                                                                               \
  FREE(3);                                                                     \
  return out;                                                                  \
}

static sexp tidy64_plus_tidy64_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_TIDY64_IMPL(tidy64_plus_int64_int64_one);
}
static sexp tidy64_minus_tidy64_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_TIDY64_IMPL(tidy64_minus_int64_int64_one);
}
static sexp tidy64_multiply_tidy64_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_TIDY64_IMPL(tidy64_multiply_int64_int64_one);
}

#undef TIDY64_OP_TIDY64_TIDY64_IMPL

// -----------------------------------------------------------------------------

// For integer and logical
#define TIDY64_OP_TIDY64_VECTOR_IMPL(OP_ONE, CTYPE, CONST_DEREF, MISSING) {    \
  const double* p_x_left = tidy64_get_left_const_deref(x);                     \
  const double* p_x_right = tidy64_get_right_const_deref(x);                   \
                                                                               \
  const CTYPE* p_y = CONST_DEREF(y);                                           \
                                                                               \
  sexp left = KEEP(tidy64_new_left(size));                                     \
  sexp right = KEEP(tidy64_new_right(size));                                   \
                                                                               \
  double* p_left = tidy64_deref_left(left);                                    \
  double* p_right = tidy64_deref_right(right);                                 \
                                                                               \
  const bool x_recycle = x_size == 1;                                          \
  const bool y_recycle = y_size == 1;                                          \
                                                                               \
  bool warn_oob = false;                                                       \
                                                                               \
  for (r_ssize i = 0; i < size; ++i) {                                         \
    const double x_elt_left = x_recycle ? p_x_left[0] : p_x_left[i];           \
    const double x_elt_right = x_recycle ? p_x_right[0] : p_x_right[i];        \
    const CTYPE y_elt = y_recycle ? p_y[0] : p_y[i];                           \
                                                                               \
    if (r_dbl_missing(x_elt_left) || MISSING(y_elt)) {                         \
      p_left[i] = r_dbl_na;                                                    \
      p_right[i] = r_dbl_na;                                                   \
      continue;                                                                \
    }                                                                          \
                                                                               \
    const int64_t x_elt_64 = tidy64_pack(x_elt_left, x_elt_right);             \
    const int64_t y_elt_64 = (int64_t) y_elt;                                  \
                                                                               \
    const struct tidy64 out_elt = OP_ONE(x_elt_64, y_elt_64, &warn_oob);       \
                                                                               \
    p_left[i] = out_elt.left;                                                  \
    p_right[i] = out_elt.right;                                                \
  }                                                                            \
                                                                               \
  if (warn_oob) {                                                              \
    Rf_warning("TODO: Warn OOB, returning NA");                                \
  }                                                                            \
                                                                               \
  sexp out = KEEP(tidy64_new(left, right));                                    \
                                                                               \
  FREE(3);                                                                     \
  return out;                                                                  \
}

static sexp tidy64_plus_tidy64_integer_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR_IMPL(tidy64_plus_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_minus_tidy64_integer_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR_IMPL(tidy64_minus_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_multiply_tidy64_integer_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR_IMPL(tidy64_multiply_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_plus_tidy64_logical_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR_IMPL(tidy64_plus_int64_int64_one, int, r_lgl_const_deref, r_lgl_missing);
}
static sexp tidy64_minus_tidy64_logical_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR_IMPL(tidy64_minus_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_multiply_tidy64_logical_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR_IMPL(tidy64_multiply_int64_int64_one, int, r_int_const_deref, r_int_missing);
}

#undef TIDY64_OP_TIDY64_VECTOR_IMPL


// -----------------------------------------------------------------------------

// For integer and logical
#define TIDY64_OP_VECTOR_TIDY64_IMPL(OP_ONE, CTYPE, CONST_DEREF, MISSING) {    \
  const double* p_y_left = tidy64_get_left_const_deref(y);                     \
  const double* p_y_right = tidy64_get_right_const_deref(y);                   \
                                                                               \
  const CTYPE* p_x = CONST_DEREF(x);                                           \
                                                                               \
  sexp left = KEEP(tidy64_new_left(size));                                     \
  sexp right = KEEP(tidy64_new_right(size));                                   \
                                                                               \
  double* p_left = tidy64_deref_left(left);                                    \
  double* p_right = tidy64_deref_right(right);                                 \
                                                                               \
  const bool x_recycle = x_size == 1;                                          \
  const bool y_recycle = y_size == 1;                                          \
                                                                               \
  bool warn_oob = false;                                                       \
                                                                               \
  for (r_ssize i = 0; i < size; ++i) {                                         \
    const double y_elt_left = y_recycle ? p_y_left[0] : p_y_left[i];           \
    const double y_elt_right = y_recycle ? p_y_right[0] : p_y_right[i];        \
    const CTYPE x_elt = x_recycle ? p_x[0] : p_x[i];                           \
                                                                               \
    if (r_dbl_missing(y_elt_left) || MISSING(x_elt)) {                         \
      p_left[i] = r_dbl_na;                                                    \
      p_right[i] = r_dbl_na;                                                   \
      continue;                                                                \
    }                                                                          \
                                                                               \
    const int64_t y_elt_64 = tidy64_pack(y_elt_left, y_elt_right);             \
    const int64_t x_elt_64 = (int64_t) x_elt;                                  \
                                                                               \
    const struct tidy64 out_elt = OP_ONE(x_elt_64, y_elt_64, &warn_oob);       \
                                                                               \
    p_left[i] = out_elt.left;                                                  \
    p_right[i] = out_elt.right;                                                \
  }                                                                            \
                                                                               \
  if (warn_oob) {                                                              \
    Rf_warning("TODO: Warn OOB, returning NA");                                \
  }                                                                            \
                                                                               \
  sexp out = KEEP(tidy64_new(left, right));                                    \
                                                                               \
  FREE(3);                                                                     \
  return out;                                                                  \
}

static sexp tidy64_plus_integer_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64_IMPL(tidy64_plus_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_minus_integer_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64_IMPL(tidy64_minus_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_multiply_integer_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64_IMPL(tidy64_multiply_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_plus_logical_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64_IMPL(tidy64_plus_int64_int64_one, int, r_lgl_const_deref, r_lgl_missing);
}
static sexp tidy64_minus_logical_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64_IMPL(tidy64_minus_int64_int64_one, int, r_int_const_deref, r_int_missing);
}
static sexp tidy64_multiply_logical_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64_IMPL(tidy64_multiply_int64_int64_one, int, r_int_const_deref, r_int_missing);
}

#undef TIDY64_OP_VECTOR_TIDY64_IMPL

// -----------------------------------------------------------------------------

#define TIDY64_OP_TIDY64_DOUBLE_IMPL(OP_ONE) {                                 \
  const double* p_x_left = tidy64_get_left_const_deref(x);                     \
  const double* p_x_right = tidy64_get_right_const_deref(x);                   \
                                                                               \
  const double* p_y = r_dbl_const_deref(y);                                    \
                                                                               \
  sexp out = KEEP(r_new_dbl(size));                                            \
  double* p_out = r_dbl_deref(out);                                            \
                                                                               \
  const bool x_recycle = x_size == 1;                                          \
  const bool y_recycle = y_size == 1;                                          \
                                                                               \
  for (r_ssize i = 0; i < size; ++i) {                                         \
    const double x_elt_left = x_recycle ? p_x_left[0] : p_x_left[i];           \
    const double x_elt_right = x_recycle ? p_x_right[0] : p_x_right[i];        \
    const double y_elt = y_recycle ? p_y[0] : p_y[i];                          \
                                                                               \
    const enum r_dbl_class y_elt_cls = r_dbl_classify(y_elt);                  \
                                                                               \
    if (y_elt_cls != r_dbl_class_number) {                                     \
      p_out[i] = (y_elt_cls == r_dbl_class_nan) ? r_dbl_nan : r_dbl_na;        \
      continue;                                                                \
    }                                                                          \
                                                                               \
    if (r_dbl_missing(x_elt_left)) {                                           \
      p_out[i] = r_dbl_na;                                                     \
      continue;                                                                \
    }                                                                          \
                                                                               \
    const int64_t x_elt_64 = tidy64_pack(x_elt_left, x_elt_right);             \
                                                                               \
    const long double x_elt_ld = (long double) x_elt_64;                       \
    const long double y_elt_ld = (long double) y_elt;                          \
                                                                               \
    p_out[i] = OP_ONE(x_elt_ld, y_elt_ld);                                     \
  }                                                                            \
                                                                               \
  FREE(1);                                                                     \
  return out;                                                                  \
}

static sexp tidy64_plus_tidy64_double_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_DOUBLE_IMPL(tidy64_plus_ld_ld_one);
}
static sexp tidy64_minus_tidy64_double_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_DOUBLE_IMPL(tidy64_minus_ld_ld_one);
}
static sexp tidy64_multiply_tidy64_double_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_TIDY64_DOUBLE_IMPL(tidy64_multiply_ld_ld_one);
}

#undef TIDY64_OP_TIDY64_DOUBLE_IMPL

// -----------------------------------------------------------------------------

#define TIDY64_OP_DOUBLE_TIDY64_IMPL(OP_ONE) {                                 \
  const double* p_y_left = tidy64_get_left_const_deref(y);                     \
  const double* p_y_right = tidy64_get_right_const_deref(y);                   \
                                                                               \
  const double* p_x = r_dbl_const_deref(x);                                    \
                                                                               \
  sexp out = KEEP(r_new_dbl(size));                                            \
  double* p_out = r_dbl_deref(out);                                            \
                                                                               \
  const bool x_recycle = x_size == 1;                                          \
  const bool y_recycle = y_size == 1;                                          \
                                                                               \
  for (r_ssize i = 0; i < size; ++i) {                                         \
    const double y_elt_left = y_recycle ? p_y_left[0] : p_y_left[i];           \
    const double y_elt_right = y_recycle ? p_y_right[0] : p_y_right[i];        \
    const double x_elt = x_recycle ? p_x[0] : p_x[i];                          \
                                                                               \
    const enum r_dbl_class x_elt_cls = r_dbl_classify(x_elt);                  \
                                                                               \
    if (x_elt_cls != r_dbl_class_number) {                                     \
      p_out[i] = (x_elt_cls == r_dbl_class_nan) ? r_dbl_nan : r_dbl_na;        \
      continue;                                                                \
    }                                                                          \
                                                                               \
    if (r_dbl_missing(y_elt_left)) {                                           \
      p_out[i] = r_dbl_na;                                                     \
      continue;                                                                \
    }                                                                          \
                                                                               \
    const int64_t y_elt_64 = tidy64_pack(y_elt_left, y_elt_right);             \
                                                                               \
    const long double y_elt_ld = (long double) y_elt_64;                       \
    const long double x_elt_ld = (long double) x_elt;                          \
                                                                               \
    p_out[i] = OP_ONE(x_elt_ld, y_elt_ld);                                     \
  }                                                                            \
                                                                               \
  FREE(1);                                                                     \
  return out;                                                                  \
}

static sexp tidy64_plus_double_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_DOUBLE_TIDY64_IMPL(tidy64_plus_ld_ld_one);
}
static sexp tidy64_minus_double_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_DOUBLE_TIDY64_IMPL(tidy64_minus_ld_ld_one);
}
static sexp tidy64_multiply_double_tidy64_impl(sexp x, sexp y, r_ssize x_size, r_ssize y_size, r_ssize size) {
  TIDY64_OP_DOUBLE_TIDY64_IMPL(tidy64_multiply_ld_ld_one);
}

#undef TIDY64_OP_DOUBLE_TIDY64_IMPL

// -----------------------------------------------------------------------------

#define TIDY64_OP_TIDY64_TIDY64(IMPL, POKE_NAMES) {                \
  const r_ssize x_size = tidy64_size(x);                           \
  const r_ssize y_size = tidy64_size(y);                           \
                                                                   \
  sexp out = KEEP(IMPL(x, y, x_size, y_size, size));               \
                                                                   \
  sexp names = r_common_names(x, y, x_size, y_size);               \
  POKE_NAMES(out, names);                                          \
                                                                   \
  FREE(1);                                                         \
  return out;                                                      \
}

static sexp tidy64_plus_tidy64_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_TIDY64(tidy64_plus_tidy64_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_minus_tidy64_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_TIDY64(tidy64_minus_tidy64_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_multiply_tidy64_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_TIDY64(tidy64_multiply_tidy64_tidy64_impl, tidy64_poke_names);
}

#undef TIDY64_OP_TIDY64_TIDY64


#define TIDY64_OP_TIDY64_VECTOR(IMPL, POKE_NAMES) {              \
  const r_ssize x_size = tidy64_size(x);                         \
  const r_ssize y_size = r_length(y);                            \
                                                                 \
  sexp out = KEEP(IMPL(x, y, x_size, y_size, size));             \
                                                                 \
  sexp names = r_common_names(x, y, x_size, y_size);             \
  POKE_NAMES(out, names);                                        \
                                                                 \
  FREE(1);                                                       \
  return out;                                                    \
}

static sexp tidy64_plus_tidy64_integer(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_plus_tidy64_integer_impl, tidy64_poke_names);
}
static sexp tidy64_minus_tidy64_integer(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_minus_tidy64_integer_impl, tidy64_poke_names);
}
static sexp tidy64_multiply_tidy64_integer(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_multiply_tidy64_integer_impl, tidy64_poke_names);
}
static sexp tidy64_plus_tidy64_logical(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_plus_tidy64_logical_impl, tidy64_poke_names);
}
static sexp tidy64_minus_tidy64_logical(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_minus_tidy64_logical_impl, tidy64_poke_names);
}
static sexp tidy64_multiply_tidy64_logical(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_multiply_tidy64_logical_impl, tidy64_poke_names);
}
static sexp tidy64_plus_tidy64_double(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_plus_tidy64_double_impl, r_poke_names);
}
static sexp tidy64_minus_tidy64_double(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_minus_tidy64_double_impl, r_poke_names);
}
static sexp tidy64_multiply_tidy64_double(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_TIDY64_VECTOR(tidy64_multiply_tidy64_double_impl, r_poke_names);
}

#undef TIDY64_OP_TIDY64_VECTOR


#define TIDY64_OP_VECTOR_TIDY64(IMPL, POKE_NAMES) {              \
  const r_ssize x_size = r_length(x);                            \
  const r_ssize y_size = tidy64_size(y);                         \
                                                                 \
  sexp out = KEEP(IMPL(x, y, x_size, y_size, size));             \
                                                                 \
  sexp names = r_common_names(x, y, x_size, y_size);             \
  POKE_NAMES(out, names);                                        \
                                                                 \
  FREE(1);                                                       \
  return out;                                                    \
}

static sexp tidy64_plus_integer_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_plus_integer_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_minus_integer_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_minus_integer_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_multiply_integer_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_multiply_integer_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_plus_logical_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_plus_logical_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_minus_logical_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_minus_logical_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_multiply_logical_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_multiply_logical_tidy64_impl, tidy64_poke_names);
}
static sexp tidy64_plus_double_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_plus_double_tidy64_impl, r_poke_names);
}
static sexp tidy64_minus_double_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_minus_double_tidy64_impl, r_poke_names);
}
static sexp tidy64_multiply_double_tidy64(sexp x, sexp y, r_ssize size) {
  TIDY64_OP_VECTOR_TIDY64(tidy64_multiply_double_tidy64_impl, r_poke_names);
}

#undef TIDY64_OP_VECTOR_TIDY64

// -----------------------------------------------------------------------------

// [[ include("arithmetic.h") ]]
sexp export_tidy64_plus_tidy64_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_plus_tidy64_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_minus_tidy64_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_minus_tidy64_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_multiply_tidy64_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_multiply_tidy64_tidy64(x, y, c_size);
}


// [[ include("arithmetic.h") ]]
sexp export_tidy64_plus_tidy64_integer(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_plus_tidy64_integer(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_minus_tidy64_integer(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_minus_tidy64_integer(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_multiply_tidy64_integer(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_multiply_tidy64_integer(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_plus_integer_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_plus_integer_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_minus_integer_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_minus_integer_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_multiply_integer_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_multiply_integer_tidy64(x, y, c_size);
}


// [[ include("arithmetic.h") ]]
sexp export_tidy64_plus_tidy64_logical(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_plus_tidy64_logical(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_minus_tidy64_logical(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_minus_tidy64_logical(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_multiply_tidy64_logical(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_multiply_tidy64_logical(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_plus_logical_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_plus_logical_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_minus_logical_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_minus_logical_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_multiply_logical_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_multiply_logical_tidy64(x, y, c_size);
}


// [[ include("arithmetic.h") ]]
sexp export_tidy64_plus_tidy64_double(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_plus_tidy64_double(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_minus_tidy64_double(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_minus_tidy64_double(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_multiply_tidy64_double(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_multiply_tidy64_double(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_plus_double_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_plus_double_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_minus_double_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_minus_double_tidy64(x, y, c_size);
}

// [[ include("arithmetic.h") ]]
sexp export_tidy64_multiply_double_tidy64(sexp x, sexp y, sexp size) {
  const r_ssize c_size = r_int_const_deref(size)[0];
  return tidy64_multiply_double_tidy64(x, y, c_size);
}
