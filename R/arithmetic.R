#' vctrs compatibility functions
#'
#' These functions are the extensions that allow stepper objects to
#' work with vctrs.
#'
#' @param x,y Objects.
#' @param op An arithmetic operator as a string.
#' @param ... Used to pass along error message information.
#'
#' @return
#'
#' See the corresponding vctrs function for the exact return value.
#'
#' @name tidy64-vctrs-compat
#'
NULL

# ------------------------------------------------------------------------------

#' @rdname tidy64-vctrs-compat
#' @export vec_arith.tidy64
#' @method vec_arith tidy64
#' @export
vec_arith.tidy64 <- function(op, x, y, ...) {
  UseMethod("vec_arith.tidy64", y)
}

#' @method vec_arith.tidy64 default
#' @export
vec_arith.tidy64.default <- function(op, x, y, ...) {
  stop_incompatible_op(op, x, y)
}

# ------------------------------------------------------------------------------

#' @method vec_arith.tidy64 tidy64
#' @export
vec_arith.tidy64.tidy64 <- function(op, x, y, ...) {
  size <- vec_size_common(x = x, y = y)

  switch (op,
    "+" = tidy64_plus_tidy64_tidy64(x, y, size),
    stop_incompatible_op(op, x, y)
  )
}

tidy64_plus_tidy64_tidy64 <- function(x, y, size) {
  .Call(export_tidy64_plus_tidy64_tidy64, x, y, size)
}

# ------------------------------------------------------------------------------

#' @method vec_arith.tidy64 numeric
#' @export
vec_arith.tidy64.numeric <- function(op, x, y, ...) {
  if (is_integer(y)) {
    vec_arith_tidy64_integer(op, x, y, ...)
  } else {
    vec_arith_tidy64_double(op, x, y, ...)
  }
}

#' @method vec_arith.numeric tidy64
#' @export
vec_arith.numeric.tidy64 <- function(op, x, y, ...) {
  if (is_integer(x)) {
    vec_arith_integer_tidy64(op, x, y, ...)
  } else {
    vec_arith_double_tidy64(op, x, y, ...)
  }
}

# ------------------------------------------------------------------------------

vec_arith_tidy64_integer <- function(op, x, y, ...) {
  size <- vec_size_common(x = x, y = y)

  switch (op,
    "+" = tidy64_plus_tidy64_integer(x, y, size),
    stop_incompatible_op(op, x, y)
  )
}

tidy64_plus_tidy64_integer <- function(x, y, size) {
  .Call(export_tidy64_plus_tidy64_integer, x, y, size)
}


vec_arith_integer_tidy64 <- function(op, x, y, ...) {
  size <- vec_size_common(x = x, y = y)

  switch (op,
    "+" = tidy64_plus_integer_tidy64(x, y, size),
    stop_incompatible_op(op, x, y)
  )
}

tidy64_plus_integer_tidy64 <- function(x, y, size) {
  .Call(export_tidy64_plus_integer_tidy64, x, y, size)
}

# ------------------------------------------------------------------------------

vec_arith_tidy64_double <- function(op, x, y, ...) {
  size <- vec_size_common(x = x, y = y)

  switch (op,
    "+" = tidy64_plus_tidy64_double(x, y, size),
    stop_incompatible_op(op, x, y)
  )
}

tidy64_plus_tidy64_double <- function(x, y, size) {
  .Call(export_tidy64_plus_tidy64_double, x, y, size)
}


vec_arith_double_tidy64 <- function(op, x, y, ...) {
  size <- vec_size_common(x = x, y = y)

  switch (op,
    "+" = tidy64_plus_double_tidy64(x, y, size),
    stop_incompatible_op(op, x, y)
  )
}

tidy64_plus_double_tidy64 <- function(x, y, size) {
  .Call(export_tidy64_plus_double_tidy64, x, y, size)
}

# ------------------------------------------------------------------------------

#' @method vec_arith.tidy64 logical
#' @export
vec_arith.tidy64.logical <- function(op, x, y, ...) {
  size <- vec_size_common(x = x, y = y)

  switch (op,
    "+" = tidy64_plus_tidy64_logical(x, y, size),
    stop_incompatible_op(op, x, y)
  )
}

tidy64_plus_tidy64_logical <- function(x, y, size) {
  .Call(export_tidy64_plus_tidy64_logical, x, y, size)
}

#' @method vec_arith.logical tidy64
#' @export
vec_arith.logical.tidy64 <- function(op, x, y, ...) {
  size <- vec_size_common(x = x, y = y)

  switch (op,
    "+" = tidy64_plus_logical_tidy64(x, y, size),
    stop_incompatible_op(op, x, y)
  )
}

tidy64_plus_logical_tidy64 <- function(x, y, size) {
  .Call(export_tidy64_plus_logical_tidy64, x, y, size)
}
