tidy64 <- function(x = double()) {
  vec_cast(x, tidy64_global_empty_tidy64)
}

new_tidy64 <- function(left = double(), right = double(), ..., class = character()) {
  if (!is_double(left)) {
    abort("`left` must be a double.")
  }
  if (!is_double(right)) {
    abort("`right` must be a double.")
  }

  if (length(left) != length(right)) {
    abort("`left` and `right` must have the same size.")
  }

  fields <- list(
    left = left,
    right = right
  )

  new_rcrd(fields, ..., class = c(class, "tidy64"))
}

# ------------------------------------------------------------------------------

#' @export
names.tidy64 <- function(x) {
  attr(x, "tidy64:::names", exact = TRUE)
}

#' @export
`names<-.tidy64` <- function(x, value) {
  value <- check_names(value, x)
  attr(x, "tidy64:::names") <- value
  x
}

check_names <- function(names, x) {
  if (is_null(names)) {
    return(names)
  }

  if (!is_character(names)) {
    abort("Names must be `NULL` or a character vector.")
  }

  if (vec_size(x) != vec_size(names)) {
    abort("A character vector of names must be the same size as `x`.")
  }

  names
}
