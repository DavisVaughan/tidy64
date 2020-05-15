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
