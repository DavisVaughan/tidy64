warn_tidy64 <- function(message = NULL, class = NULL, ...) {
  warn(message = message, class = c(class, "tidy64_warning"), ...)
}

#' @export
conditionMessage.tidy64_warning <- function(c) {
  cnd_message(c)
}

# ------------------------------------------------------------------------------

warn_dbl_is_outside_tidy64_range <- function(x) {
  warn_tidy64(x = x, class = "tidy64_warning_dbl_is_outside_tidy64_range")
}

#' @export
cnd_header.tidy64_warning_dbl_is_outside_tidy64_range <- function(cnd, ...) {
  "Input is outside the range of a tidy64."
}

#' @export
cnd_body.tidy64_warning_dbl_is_outside_tidy64_range <- function(cnd, ...) {
  x <- cnd$x
  indicator <- x > tidy64_global_max_dbl() | x < tidy64_global_min_dbl()
  locations <- which(indicator)

  if (length(locations) == 1L) {
    loc_chr <- "location"
  } else {
    loc_chr <- "locations"
  }

  locations <- collapse_locations(locations)
  locations <- ensure_full_stop(locations)

  bullet1 <- glue("Range was exceeded at {loc_chr} {locations}")
  bullet2 <- "Returning `NA` at the exceeded locations."

  format_error_bullets(c(i = bullet1, i = bullet2))
}

# ------------------------------------------------------------------------------

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
