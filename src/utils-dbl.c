#include "utils-dbl.h"


#ifdef WORDS_BIGENDIAN
static const int r_dbl_indicator_pos = 1;
#else
static const int r_dbl_indicator_pos = 0;
#endif

union r_dbl_indicator {
  double value;        // 8 bytes
  unsigned int key[2]; // 4 * 2 bytes
};


// [[ include("utils-dbl.h") ]]
enum r_dbl_class r_dbl_classify(double x) {
  if (!isnan(x)) {
    return r_dbl_class_number;
  }

  union r_dbl_indicator indicator;
  indicator.value = x;

  if (indicator.key[r_dbl_indicator_pos] == 1954) {
    return r_dbl_class_missing;
  } else {
    return r_dbl_class_nan;
  }
}
