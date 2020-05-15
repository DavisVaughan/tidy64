# ------------------------------------------------------------------------------

#' @export
as_tidy64 <- function(x) {
  UseMethod("as_tidy64")
}

#' @export
as_tidy64.default <- function(x) {
  cls <- paste0(class(x), collapse = "/")
  abort(glue("Can't convert <{cls}> to <tidy64>."))
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
as.character.tidy64 <- function(x) {
  tidy64_force_to_chr_from_tidy64(x)
}

tidy64_force_to_chr_from_tidy64 <- function(x) {
  .Call(export_tidy64_force_to_chr_from_tidy64, x)
}
