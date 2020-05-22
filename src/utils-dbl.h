#ifndef TIDY64_UTILS_DBL_H
#define TIDY64_UTILS_DBL_H

#include "r.h"

enum r_dbl_class {
  r_dbl_class_number,
  r_dbl_class_missing,
  r_dbl_class_nan
};

enum r_dbl_class r_dbl_classify(double x);

#endif
