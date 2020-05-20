#include "initialize.h"
#include "utils.h"

sexp export_tidy64_initialize(sexp ns) {
  tidy64_initialize_utils_globals(ns);
  return r_null;
}
