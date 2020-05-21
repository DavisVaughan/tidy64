#include "globals.h"
#include "tidy64.h"

// For PRId64
#include <inttypes.h>

// -----------------------------------------------------------------------------

static sexp convert_int64_to_chr(int64_t x) {
  char c_string[TIDY64_MAX_PRINT_SIZE];

  snprintf(c_string, TIDY64_MAX_PRINT_SIZE, "%" PRId64, x);

  sexp out = KEEP(r_new_chr(1));
  sexp* p_out = r_chr_deref(out);
  p_out[0] = r_new_string(c_string);

  FREE(1);
  return out;
}

// [[ include("globals.h") ]]
sexp export_tidy64_global_max_as_chr() {
  return convert_int64_to_chr(TIDY64_MAX);
}

// [[ include("globals.h") ]]
sexp export_tidy64_global_min_as_chr() {
  return convert_int64_to_chr(TIDY64_MIN);
}

// [[ include("globals.h") ]]
sexp export_tidy64_global_max_dbl() {
  return Rf_ScalarReal(TIDY64_MAX_DBL);
}

// [[ include("globals.h") ]]
sexp export_tidy64_global_min_dbl() {
  return Rf_ScalarReal(TIDY64_MIN_DBL);
}
