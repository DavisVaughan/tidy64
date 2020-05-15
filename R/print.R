#' @export
format.tidy64 <- function(x, ...) {
  out <- tidy64_cast_to_chr_from_tidy64(x)

  # Because `print(quote = FALSE)` prints `<NA>` for missing characters
  out[is.na(out)] <- "NA"

  out
}
