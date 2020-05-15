warn_tidy64 <- function(message = NULL, class = NULL, ...) {
  warn(message = message, class = c(class, "tidy64_warning"), ...)
}

#' @export
conditionMessage.tidy64_warning <- function(c) {
  cnd_message(c)
}

# ------------------------------------------------------------------------------

warn_outside_tidy64_range <- function(x) {
  warn_tidy64(x = x, class = "tidy64_warning_outside_tidy64_range")
}

#' @export
cnd_header.tidy64_warning_outside_tidy64_range <- function(cnd, ...) {
  "Can't losslessly store result in a tidy64."
}

#' @export
cnd_body.tidy64_warning_outside_tidy64_range <- function(cnd, ...) {
  x <- cnd$x
  indicator <- x > 9223372036854775807 | x < -9223372036854775807
  locations <- which(indicator)

  if (length(locations) == 1L) {
    loc_chr <- "location"
  } else {
    loc_chr <- "locations"
  }

  locations <- collapse_locations(locations)
  locations <- ensure_full_stop(locations)

  bullet <- glue("Range was exceeded at {loc_chr} {locations}")

  format_error_bullets(c(i = bullet))
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
