#include "tidy64.h"

// [[ include("tidy64.h") ]]
const struct tidy64 new_na_tidy64() {
  const struct tidy64 out = {
    .left = r_dbl_na,
    .right = r_dbl_na
  };

  return out;
}
