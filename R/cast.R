# ------------------------------------------------------------------------------

#' @export
vec_cast.tidy64.double <- function(x, to, ..., x_arg = "", to_arg = "") {
  tidy64_cast_to_tidy64_from_dbl(x)
}

tidy64_cast_to_tidy64_from_dbl <- function(x) {
  .Call(export_tidy64_cast_to_tidy64_from_dbl, x)
}

# ------------------------------------------------------------------------------
