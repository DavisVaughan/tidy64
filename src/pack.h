#ifndef TIDY64_PACK_H
#define TIDY64_PACK_H

#include "r.h"
#include "tidy64.h"

// -----------------------------------------------------------------------------

// Inlined for performance, since pack/unpack are always used in tight loops.

static inline const struct tidy64 tidy64_unpack(int64_t x) {
  if (x == r_int64_na) {
    return new_na_tidy64();
  }

  // Map int64_t -> uint64_t
  uint64_t x_u64;
  if (signbit(x)) {
    x_u64 = (uint64_t) (x + 1 + INT64_MAX) - INT64_MIN;
  } else {
    x_u64 = (uint64_t) x;
  }

  // Split into 32 bit sections
  // TODO: Is this specific to endianness? I think not?
  uint32_t right_u32 = (uint32_t) (x_u64 & 0xFFFFFFFFLL);
  uint32_t left_u32 = (uint32_t) (x_u64 >> 32);

  // Map uint32_t -> int32_t
  // This allows order to be maintained
  int32_t left_32;
  if (left_u32 > INT32_MAX) {
    left_32 = ((int32_t) (left_u32 - 1 - INT32_MAX) + INT32_MIN);
  } else {
    left_32 = (int32_t) left_u32;
  }

  double right = (double) right_u32;
  double left = (double) left_32;


  const struct tidy64 out = {
    .right = right,
    .left = left
  };

  return out;
}

// -----------------------------------------------------------------------------

static inline int64_t tidy64_pack(const struct tidy64 x) {
  double right = x.right;
  double left = x.left;

  if (right == r_dbl_na) {
    return r_int64_na;
  }

  uint32_t right_u32 = (uint32_t) right;
  int32_t left_32 = (int32_t) left;

  // Map int32_t -> uint32_t
  uint32_t left_u32;
  if (signbit(left_32)) {
    left_u32 = (uint32_t) (left_32 + 1 + INT32_MAX) - INT32_MIN;
  } else {
    left_u32 = (uint32_t) left_32;
  }

  // Bind (uint32_t, uint32_t) -> uint64_t
  uint64_t out_u64 = ((uint64_t) left_u32) << 32 | right_u32;

  // Map uint64_t -> int64_t
  int64_t out;
  if (out_u64 > INT64_MAX) {
    out = (int64_t) (out_u64 - 1 - INT64_MAX) + INT64_MIN;
  } else {
    out = (int64_t) out_u64;
  }

  return out;
}

// -----------------------------------------------------------------------------

#endif
