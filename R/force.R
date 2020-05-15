#' Coerce to a tidy64
#'
#' `as_tidy64()` converts `x` to tidy64 if possible.
#'
#' @param x A vector.
#'
#' @export
as_tidy64 <- function(x) {
  UseMethod("as_tidy64")
}

#' @export
as_tidy64.default <- function(x) {
  cls <- paste0(class(x), collapse = "/")
  abort(glue("Can't convert <{cls}> to <tidy64>."))
}

#' @export
as_tidy64.tidy64 <- function(x) {
  x
}

# ------------------------------------------------------------------------------

#' @export
as_tidy64.double <- function(x) {
  tidy64_force_to_tidy64_from_dbl(x)
}

tidy64_force_to_tidy64_from_dbl <- function(x) {
  .Call(export_tidy64_force_to_tidy64_from_dbl, x)
}

# ------------------------------------------------------------------------------

#' @export
as_tidy64.integer <- function(x) {
  tidy64_force_to_tidy64_from_int(x)
}

tidy64_force_to_tidy64_from_int <- function(x) {
  .Call(export_tidy64_force_to_tidy64_from_int, x)
}

# ------------------------------------------------------------------------------

#' @export
as_tidy64.logical <- function(x) {
  tidy64_force_to_tidy64_from_lgl(x)
}

tidy64_force_to_tidy64_from_lgl <- function(x) {
  .Call(export_tidy64_force_to_tidy64_from_lgl, x)
}

# ------------------------------------------------------------------------------

#' @export
as_tidy64.character <- function(x) {
  tidy64_force_to_tidy64_from_chr(x)
}

tidy64_force_to_tidy64_from_chr <- function(x) {
  .Call(export_tidy64_force_to_tidy64_from_chr, x)
}

# ------------------------------------------------------------------------------

#' @export
as.character.tidy64 <- function(x, ...) {
  tidy64_force_to_chr_from_tidy64(x)
}

tidy64_force_to_chr_from_tidy64 <- function(x) {
  .Call(export_tidy64_force_to_chr_from_tidy64, x)
}

# ------------------------------------------------------------------------------

#' @export
as.double.tidy64 <- function(x, ...) {
  tidy64_force_to_dbl_from_tidy64(x)
}

tidy64_force_to_dbl_from_tidy64 <- function(x) {
  .Call(export_tidy64_force_to_dbl_from_tidy64, x)
}

# ------------------------------------------------------------------------------

#' @export
as.integer.tidy64 <- function(x, ...) {
  tidy64_force_to_int_from_tidy64(x)
}

tidy64_force_to_int_from_tidy64 <- function(x) {
  .Call(export_tidy64_force_to_int_from_tidy64, x)
}

# ------------------------------------------------------------------------------

#' @export
as.logical.tidy64 <- function(x, ...) {
  tidy64_force_to_lgl_from_tidy64(x)
}

tidy64_force_to_lgl_from_tidy64 <- function(x) {
  .Call(export_tidy64_force_to_lgl_from_tidy64, x)
}
