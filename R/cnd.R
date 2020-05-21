warn_tidy64 <- function(message = NULL, class = NULL, ...) {
  warn(message = message, class = c(class, "tidy64_warning"), ...)
}

#' @export
conditionMessage.tidy64_warning <- function(c) {
  cnd_message(c)
}

# ------------------------------------------------------------------------------

warn_to_tidy64_from_dbl_oob <- function(x) {
  warn_tidy64(x = x, class = "tidy64_warning_to_tidy64_from_dbl_oob")
}

#' @export
cnd_header.tidy64_warning_to_tidy64_from_dbl_oob <- function(cnd, ...) {
  "Input is outside the range of a tidy64."
}

#' @export
cnd_body.tidy64_warning_to_tidy64_from_dbl_oob <- function(cnd, ...) {
  x <- cnd$x
  indicator <- x > tidy64_global_max_dbl() | x < tidy64_global_min_dbl()
  locations <- which(indicator)

  locations_string <- make_locations_string(locations)
  locations_collapsed <- collapse_locations(locations)
  locations_collapsed <- ensure_full_stop(locations_collapsed)

  bullet1 <- glue("Range was exceeded at {locations_string} {locations_collapsed}")
  bullet2 <- "Returning `NA` at the exceeded locations."

  format_error_bullets(c(i = bullet1, i = bullet2))
}

# ------------------------------------------------------------------------------

stop_to_tidy64_from_dbl_oob <- function(x, to, x_arg = "", to_arg = "") {
  stop_incompatible_cast(
    x = x,
    to = to,
    x_arg = x_arg,
    to_arg = to_arg,
    class = "tidy64_error_to_tidy64_from_dbl_oob"
  )
}

#' @export
cnd_header.tidy64_error_to_tidy64_from_dbl_oob <- function(cnd, ...) {
  cnd$message
}

#' @export
cnd_body.tidy64_error_to_tidy64_from_dbl_oob <- function(cnd, ...) {
  x <- cnd$x
  indicator <- x > tidy64_global_max_dbl() | x < tidy64_global_min_dbl()
  locations <- which(indicator)

  locations_string <- make_locations_string(locations)
  locations_collapsed <- collapse_locations(locations)
  locations_collapsed <- ensure_full_stop(locations_collapsed)

  bullet1 <- "Input is outside the range of a tidy64."
  bullet2 <- glue("Range was exceeded at {locations_string} {locations_collapsed}")

  format_error_bullets(c(i = bullet1, i = bullet2))
}

# ------------------------------------------------------------------------------

stop_to_dbl_from_tidy64_might_lose_precision <- function(x, to, x_arg = "", to_arg = "") {
  stop_incompatible_cast(
    x = x,
    to = to,
    x_arg = x_arg,
    to_arg = to_arg,
    class = "tidy64_error_to_dbl_from_tidy64_might_lose_precision"
  )
}

#' @export
cnd_header.tidy64_error_to_dbl_from_tidy64_might_lose_precision <- function(cnd, ...) {
  cnd$message
}

#' @export
cnd_body.tidy64_error_to_dbl_from_tidy64_might_lose_precision <- function(cnd, ...) {
  indicator <- tidy64_detect_to_dbl_from_tidy64_might_lose_precision(cnd$x)
  locations <- which(indicator)

  locations_string <- make_locations_string(locations)
  locations_collapsed <- collapse_locations(locations)
  locations_collapsed <- ensure_full_stop(locations_collapsed)

  bullet <- glue("Precision may be lost at {locations_string} {locations_collapsed}")
  bullet <- format_error_bullets(c(i = bullet))

  bullet
}

tidy64_detect_to_dbl_from_tidy64_might_lose_precision <- function(x) {
  .Call(export_tidy64_detect_to_dbl_from_tidy64_might_lose_precision, x)
}

# ------------------------------------------------------------------------------

make_locations_string <- function(locations) {
  if (length(locations) == 1L) {
    "location"
  } else {
    "locations"
  }
}

collapse_locations <- function(locations) {
  if (length(locations) > 5L) {
    locations <- locations[1:5]
    locations <- as.character(locations)
    locations <- c(locations, "...")
    glue::glue_collapse(locations, sep = ", ")
  } else if (length(locations) == 2L) {
    glue::glue_collapse(locations, sep = " and ")
  } else {
    glue::glue_collapse(locations, sep = ", ", last = ", and ")
  }
}

ensure_full_stop <- function (x) {
  n <- nchar(x)

  if (substr(x, n, n) == ".") {
    x
  } else {
    paste0(x, ".")
  }
}
