#include "tidy64.h"


const struct tidy64 new_na_tidy64() {
  const struct tidy64 out = {
    .first = r_dbl_na,
    .last = r_dbl_na
  };

  return out;
}
