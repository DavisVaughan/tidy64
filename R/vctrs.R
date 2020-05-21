# ------------------------------------------------------------------------------

# Proxy and restore methods are designed to preserve names in an extra data
# frame column. Comparison and equality proxies don't use this column.

#' @export
vec_proxy.tidy64 <- function(x, ...) {
  out <- unclass(x)

  names <- names(x)
  out[["tidy64:::names"]] <- names

  new_data_frame(out)
}

#' @export
vec_restore.tidy64 <- function(x, to, ...) {
  left <- x[["left"]]
  right <- x[["right"]]

  names <- x[["tidy64:::names"]]
  names <- repair_na_names(names)

  new_tidy64(
    left = left,
    right = right,
    `tidy64:::names` = names
  )
}

repair_na_names <- function(names) {
  if (is_null(names)) {
    return(names)
  }
  if (!anyNA(names)) {
    return(names)
  }

  repair_indicator <- vec_equal_na(names)
  names[repair_indicator] <- ""

  names
}

# ------------------------------------------------------------------------------

#' @export
vec_proxy_compare.tidy64 <- function(x, ...) {
  new_data_frame(x)
}

#' @export
vec_proxy_equal.tidy64 <- function(x, ...) {
  new_data_frame(x)
}
