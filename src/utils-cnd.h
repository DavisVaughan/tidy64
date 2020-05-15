#ifndef TIDY64_UTILS_CND_H
#define TIDY64_UTILS_CND_H

#include "r.h"

// -----------------------------------------------------------------------------

__attribute__((noreturn)) static inline void never_reached(const char* fn) {
  Rf_errorcall(r_null, "Internal error: Reached the unreachable in `%s()`.", fn);
}

// -----------------------------------------------------------------------------

void r_abort(const char* fmt, ...);

// -----------------------------------------------------------------------------

#endif
