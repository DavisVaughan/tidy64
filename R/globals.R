# ------------------------------------------------------------------------------

delayedAssign("tidy64_global_empty_double", double())
delayedAssign("tidy64_global_empty_tidy64", new_tidy64())
delayedAssign("tidy64_global_max", as_tidy64(tidy64_global_max_chr()))
delayedAssign("tidy64_global_min", as_tidy64(tidy64_global_min_chr()))

# ------------------------------------------------------------------------------

tidy64_global_max_chr <- function() {
  .Call(export_tidy64_global_max_chr)
}

tidy64_global_min_chr <- function() {
  .Call(export_tidy64_global_min_chr)
}
