#include "utils-call.h"

/**
 * Create a call or pairlist
 *
 * @param tags Optional. If not `NULL`, a null-terminated array of symbols.
 * @param cars Mandatory. A null-terminated array of CAR values.
 * @param fn The first CAR value of the language list.
 *
 * [[ include("utils-call.h") ]]
 */
sexp r_pairlist(sexp* tags, sexp* cars) {
  if (!cars) {
    Rf_error("Internal error: Null `cars` in `r_pairlist()`");
  }

  sexp list = KEEP(Rf_cons(R_NilValue, R_NilValue));
  sexp node = list;

  while (*cars) {
    sexp next_node = Rf_cons(*cars, R_NilValue);
    SETCDR(node, next_node);
    node = next_node;

    if (tags) {
      SET_TAG(next_node, *tags);
      ++tags;
    }

    ++cars;
  }

  FREE(1);
  return CDR(list);
}

// [[ include("utils-call.h") ]]
sexp r_protect(sexp x) {
  return Rf_lang2(fns_quote, x);
}
