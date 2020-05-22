tidy64 <- function(x = double()) {
  vec_cast(x, tidy64_global_empty_tidy64)
}

# ------------------------------------------------------------------------------

#' Construct a new tidy64
#'
#' @description
#' _For expert use only!_
#'
#' `new_tidy64()` is a bare bones constructor for
#' creating tidy64 objects from their 32 bit components. You should almost
#' always use [tidy64()] or [as_tidy64()] instead.
#'
#' `new_tidy64_subclass()` is a slightly more developer friendly way to create
#' a subclass of tidy64. It takes an existing tidy64, breaks it apart, and
#' then uses `new_tidy64()` to form a new tidy64 with the subclass and
#' attributes attached.
#'
#' @param left `[double]`
#'
#'   A vector of integerish double values in the range of
#'   `[-2147483648, 2147483647]`. These represent the left most 32 bits
#'   of the `int64_t` extracted by:
#'
#'   - Mapping the `int64_t` to `uint64_t`.
#'
#'   - Right shifting with `x_u64 >> 32` to get the left 32 bits as a
#'     `uint32_t`.
#'
#'   - Mapping the unsigned left 32 bits of `x_u64` to a signed `int32_t`. This
#'     maintains ordering automatically in operations like `vec_order()`.
#'
#'   - Coercing the resulting `int32_t` to a double.
#'
#' @param right `[double]`
#'
#'   A vector of integerish double values in the range of
#'   `[0, 4294967295]`. These represent the right most 32 bits
#'   of the `int64_t` extracted by:
#'
#'   - Mapping the `int64_t` to `uint64_t`.
#'
#'   - Directly coercing the resulting `x_u64` to `uint32_t`, which gives us
#'     the right 32 bits as a `uint32_t`.
#'
#'   - Coercing the resulting `uint32_t` to a double.
#'
#' @param ... `[named dots]`
#'
#'   Name value pairs resulting in extra attributes attached to the new tidy64.
#'
#' @param class `[character]`
#'
#'   A vector of subclasses.
#'
#' @export
#' @examples
#' new_tidy64()
#' new_tidy64(0, 1)
#' new_tidy64(0, 2)
#' new_tidy64(1, 0)
#'
#' new_tidy64_subclass(tidy64(1), names = "x", class = "foobar")
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

#' @param x `[tidy64]`
#'
#'   An existing tidy64 to create the subclass from.
#'
#' @param names `[NULL / character]`
#'
#'   Names to attach to the new tidy64 subclass. Either `NULL` for no names,
#'   or a character vector of names the same size as `x`.
#'
#' @rdname new_tidy64
#' @export
new_tidy64_subclass <- function(x = new_tidy64(),
                                ...,
                                names = NULL,
                                class = character()) {
  if (!is_tidy64(x)) {
    abort("`x` must be a <tidy64>.")
  }

  names <- check_names(names, x)

  left <- field(x, "left")
  right <- field(x, "right")

  new_tidy64(
    left = left,
    right = right,
    `tidy64:::names` = names,
    ...,
    class = class
  )
}

# ------------------------------------------------------------------------------

is_tidy64 <- function(x) {
  inherits(x, "tidy64")
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

  if (anyNA(names)) {
    abort("Names must not be `NA`.")
  }

  names
}
