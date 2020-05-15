#include "tidy64.h"


const struct tidy64 new_na_tidy64() {
  const struct tidy64 out = {
    .right = r_dbl_na,
    .left = r_dbl_na
  };

  return out;
}
