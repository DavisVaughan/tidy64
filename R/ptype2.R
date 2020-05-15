# ------------------------------------------------------------------------------

delayedAssign("tidy64_global_empty_double", double())
delayedAssign("tidy64_global_empty_tidy64", new_tidy64())

# ------------------------------------------------------------------------------

#' @export
vec_ptype2.tidy64.tidy64 <- function(x, y, ...) {
  tidy64_global_empty_tidy64
}

# ------------------------------------------------------------------------------

#' @export
vec_ptype2.tidy64.double <- function(x, y, ...) {
  tidy64_global_empty_double
}

#' @export
vec_ptype2.double.tidy64 <- function(x, y, ...) {
  tidy64_global_empty_double
}

# ------------------------------------------------------------------------------

#' @export
vec_ptype2.tidy64.integer <- function(x, y, ...) {
  tidy64_global_empty_tidy64
}

#' @export
vec_ptype2.integer.tidy64 <- function(x, y, ...) {
  tidy64_global_empty_tidy64
}
