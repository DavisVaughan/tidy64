#ifndef TIDY64_PACK_H
#define TIDY64_PACK_H

#include "r.h"
#include "tidy64.h"

// -----------------------------------------------------------------------------

// Inlined for performance, since pack/unpack are always used in tight loops.

static inline const struct tidy64 tidy64_unpack(int64_t x) {
  // Map int64_t -> uint64_t
  uint64_t x_u64;
  if (signbit(x)) {
    x_u64 = (uint64_t) (x + 1 + INT64_MAX) - INT64_MIN;
  } else {
    x_u64 = (uint64_t) x;
  }

  // TODO: Is this specific to endianness? I think not?
  //
  // left_u32:
  //   Right shift the left-most 32 bits and then shove them into the
  //   equivalent 32-bit type.
  // right_u32:
  //   Directly shove the right-most 32 bits into the equivalent 32-bit type.
  uint32_t left_u32 = (uint32_t) (x_u64 >> 32);
  uint32_t right_u32 = (uint32_t) (x_u64);

  // Map uint32_t -> int32_t
  // This allows order to be maintained
  int32_t left_32;
  if (left_u32 > INT32_MAX) {
    left_32 = ((int32_t) (left_u32 - 1 - INT32_MAX) + INT32_MIN);
  } else {
    left_32 = (int32_t) left_u32;
  }

  double left = (double) left_32;
  double right = (double) right_u32;

  const struct tidy64 out = {
    .left = left,
    .right = right
  };

  return out;
}

// -----------------------------------------------------------------------------

static inline int64_t tidy64_pack(double left, double right) {
  int32_t left_32 = (int32_t) left;
  uint32_t right_u32 = (uint32_t) right;

  // Map int32_t -> uint32_t
  uint32_t left_u32;
  if (signbit(left_32)) {
    left_u32 = (uint32_t) (left_32 + 1 + INT32_MAX) - INT32_MIN;
  } else {
    left_u32 = (uint32_t) left_32;
  }

  // Bind (uint32_t, uint32_t) -> uint64_t
  // - First cast `left_u32` to 64-bit so it has room when bits are shifted.
  //   The 32 bits should be in the right-most 32 bits of the 64-bit object.
  // - Left shift those 32-bits so they are in the original left-most 32-bits.
  // - Then fill the right-most 32 bits with the 32 bits of `right_u32`.
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

sexp export_tidy64_pack(sexp x);
sexp export_tidy64_unpack(sexp x);

// -----------------------------------------------------------------------------

#endif
