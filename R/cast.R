#' @export
vec_cast.tidy64.tidy64 <- function(x, to, ..., x_arg = "", to_arg = "") {
  x
}

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

#' @export
vec_cast.integer.tidy64 <- function(x, to, ..., x_arg = "", to_arg = "") {
  tidy64_cast_to_int_from_tidy64(x)
}

tidy64_cast_to_int_from_tidy64 <- function(x) {
  .Call(export_tidy64_cast_to_int_from_tidy64, x)
}

# ------------------------------------------------------------------------------

#' @export
vec_cast.tidy64.logical <- function(x, to, ..., x_arg = "", to_arg = "") {
  tidy64_cast_to_tidy64_from_lgl(x)
}

tidy64_cast_to_tidy64_from_lgl <- function(x) {
  .Call(export_tidy64_cast_to_tidy64_from_lgl, x)
}

# ------------------------------------------------------------------------------

#' @export
vec_cast.logical.tidy64 <- function(x, to, ..., x_arg = "", to_arg = "") {
  tidy64_cast_to_lgl_from_tidy64(x)
}

tidy64_cast_to_lgl_from_tidy64 <- function(x) {
  .Call(export_tidy64_cast_to_lgl_from_tidy64, x)
}

# ------------------------------------------------------------------------------
