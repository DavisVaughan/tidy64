# ------------------------------------------------------------------------------

delayedAssign("tidy64_global_empty_double", double())
delayedAssign("tidy64_global_empty_tidy64", new_tidy64())

delayedAssign("tidy64_global_int_max", .Machine$integer.max)
delayedAssign("tidy64_global_int_min", -.Machine$integer.max)

delayedAssign("tidy64_global_max", as_tidy64(tidy64_global_max_as_chr()))
delayedAssign("tidy64_global_min", as_tidy64(tidy64_global_max_as_chr()))

delayedAssign("tidy64_global_max_lossless_double_chr", "9007199254740992") # 2^53
delayedAssign("tidy64_global_min_lossless_double_chr", "-9007199254740992") # -2^53
delayedAssign("tidy64_global_max_lossless_double_plus_one_chr", "9007199254740993") # 2^53+1
delayedAssign("tidy64_global_min_lossless_double_minus_one_chr", "-9007199254740993") # -2^53-1

delayedAssign("tidy64_global_max_lossless_double", 9007199254740992)
delayedAssign("tidy64_global_min_lossless_double", -9007199254740992)

# ------------------------------------------------------------------------------

tidy64_global_max_as_chr <- function() {
  .Call(export_tidy64_global_max_as_chr)
}

tidy64_global_min_as_chr <- function() {
  .Call(export_tidy64_global_min_as_chr)
}

tidy64_global_max_dbl <- function() {
  .Call(export_tidy64_global_max_dbl)
}

tidy64_global_min_dbl <- function() {
  .Call(export_tidy64_global_min_dbl)
}
