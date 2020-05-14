#ifndef TIDY64_PACK_H
#define TIDY64_PACK_H

#include "r.h"
#include "tidy64.h"

// -----------------------------------------------------------------------------

const struct tidy64 tidy64_unpack(int64_t x);
int64_t tidy64_pack(const struct tidy64 x);

// -----------------------------------------------------------------------------

#endif
