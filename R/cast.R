# ------------------------------------------------------------------------------

#' @export
vec_cast.tidy64.double <- function(x, to, ..., x_arg = "", to_arg = "") {
  tidy64_cast_to_tidy64_from_dbl(x)
}

tidy64_cast_to_tidy64_from_dbl <- function(x) {
  .Call(export_tidy64_cast_to_tidy64_from_dbl, x)
}

# ------------------------------------------------------------------------------

#' @export
vec_cast.double.tidy64 <- function(x, to, ..., x_arg = "", to_arg = "") {
  tidy64_cast_to_dbl_from_tidy64(x)
}

tidy64_cast_to_dbl_from_tidy64 <- function(x) {
  .Call(export_tidy64_cast_to_dbl_from_tidy64, x)
}

# ------------------------------------------------------------------------------

#' @export
vec_cast.tidy64.integer <- function(x, to, ..., x_arg = "", to_arg = "") {
  tidy64_cast_to_tidy64_from_int(x)
}

tidy64_cast_to_tidy64_from_int <- function(x) {
  .Call(export_tidy64_cast_to_tidy64_from_int, x)
}

# ------------------------------------------------------------------------------
