# ------------------------------------------------------------------------------
# tidy64 + tidy64

test_that("can add together", {
  x <- tidy64(1)
  y <- tidy64(2)

  expect_identical(x + y, tidy64(3))
  expect_identical(y + x, tidy64(3))
})

test_that("can propagate NA", {
  x <- tidy64(1)
  y <- tidy64(NA)

  expect_identical(x + y, tidy64(NA))
  expect_identical(y + x, tidy64(NA))
})

test_that("uses tidy recycling", {
  x <- tidy64(1)
  y <- tidy64(c(1, 2))
  z <- tidy64(c(1, 2, 3))

  expect_identical(x + y, tidy64(c(2, 3)))
  expect_error(y + z, class = "vctrs_error_incompatible_size")
})

test_that("warns and returns NA on overflow", {
  x <- tidy64_global_max
  y <- tidy64(1)

  expect_identical(expect_warning(x + y), tidy64(NA))
  expect_identical(expect_warning(y + x), tidy64(NA))
})

# ------------------------------------------------------------------------------
# tidy64 + integer
# integer + tidy64

test_that("can add together", {
  x <- tidy64(1)
  y <- 2L

  expect_identical(x + y, tidy64(3))
  expect_identical(y + x, tidy64(3))
})

test_that("can propagate NA", {
  x <- tidy64(1)
  y <- tidy64(NA)
  a <- 1L
  b <- NA_integer_

  expect_identical(x + b, tidy64(NA))
  expect_identical(b + x, tidy64(NA))

  expect_identical(a + y, tidy64(NA))
  expect_identical(y + a, tidy64(NA))
})

test_that("uses tidy recycling", {
  x <- tidy64(1)
  y <- tidy64(c(1, 2))
  z <- tidy64(c(1, 2, 3))
  a <- 1L
  b <- c(1L, 2L)
  c <- c(1L, 2L, 3L)

  expect_identical(x + b, tidy64(c(2, 3)))
  expect_identical(b + x, tidy64(c(2, 3)))

  expect_identical(y + a, tidy64(c(2, 3)))
  expect_identical(a + y, tidy64(c(2, 3)))

  expect_error(y + c, class = "vctrs_error_incompatible_size")
  expect_error(c + y, class = "vctrs_error_incompatible_size")

  expect_error(z + b, class = "vctrs_error_incompatible_size")
  expect_error(b + z, class = "vctrs_error_incompatible_size")
})

test_that("warns and returns NA on overflow", {
  x <- tidy64_global_max
  y <- 1L

  expect_identical(expect_warning(x + y), tidy64(NA))
  expect_identical(expect_warning(y + x), tidy64(NA))
})

# ------------------------------------------------------------------------------
# tidy64 + logical
# logical + tidy64

test_that("can add together", {
  x <- tidy64(1)
  y <- TRUE

  expect_identical(x + y, tidy64(2))
  expect_identical(y + x, tidy64(2))
})

test_that("can propagate NA", {
  x <- tidy64(1)
  y <- tidy64(NA)
  a <- TRUE
  b <- NA

  expect_identical(x + b, tidy64(NA))
  expect_identical(b + x, tidy64(NA))

  expect_identical(a + y, tidy64(NA))
  expect_identical(y + a, tidy64(NA))
})

test_that("uses tidy recycling", {
  x <- tidy64(1)
  y <- tidy64(c(1, 2))
  z <- tidy64(c(1, 2, 3))
  a <- TRUE
  b <- c(TRUE, FALSE)
  c <- c(TRUE, FALSE, TRUE)

  expect_identical(x + b, tidy64(c(2, 1)))
  expect_identical(b + x, tidy64(c(2, 1)))

  expect_identical(y + a, tidy64(c(2, 3)))
  expect_identical(a + y, tidy64(c(2, 3)))

  expect_error(y + c, class = "vctrs_error_incompatible_size")
  expect_error(c + y, class = "vctrs_error_incompatible_size")

  expect_error(z + b, class = "vctrs_error_incompatible_size")
  expect_error(b + z, class = "vctrs_error_incompatible_size")
})

test_that("warns and returns NA on overflow", {
  x <- tidy64_global_max
  y <- TRUE

  expect_identical(expect_warning(x + y), tidy64(NA))
  expect_identical(expect_warning(y + x), tidy64(NA))
})

# ------------------------------------------------------------------------------
# tidy64 + double
# double + tidy64

test_that("can add together", {
  x <- tidy64(1)
  y <- 2

  expect_identical(x + y, 3)
  expect_identical(y + x, 3)
})

test_that("can propagate NA", {
  x <- tidy64(1)
  y <- tidy64(NA)
  a <- 1
  b <- NA_real_

  expect_identical(x + b, NA_real_)
  expect_identical(b + x, NA_real_)

  expect_identical(a + y, NA_real_)
  expect_identical(y + a, NA_real_)
})

test_that("uses tidy recycling", {
  x <- tidy64(1)
  y <- tidy64(c(1, 2))
  z <- tidy64(c(1, 2, 3))
  a <- 1
  b <- c(1, 2)
  c <- c(1, 2, 3)

  expect_identical(x + b, c(2, 3))
  expect_identical(b + x, c(2, 3))

  expect_identical(y + a, c(2, 3))
  expect_identical(a + y, c(2, 3))

  expect_error(y + c, class = "vctrs_error_incompatible_size")
  expect_error(c + y, class = "vctrs_error_incompatible_size")

  expect_error(z + b, class = "vctrs_error_incompatible_size")
  expect_error(b + z, class = "vctrs_error_incompatible_size")
})

test_that("no overflow warning since we convert to double", {
  x <- tidy64_global_max
  y <- 1

  expect_warning(x + y, NA)
  expect_warning(y + x, NA)
})

test_that("can propagate NaN", {
  x <- tidy64(1)
  y <- tidy64(NA)
  a <- NaN

  expect_identical(x + a, NaN)
  expect_identical(a + x, NaN)

  # NaN trumps NA
  expect_identical(a + y, NaN)
  expect_identical(y + a, NaN)
})

test_that("infinity propagates", {
  x <- tidy64(1)
  y <- Inf
  z <- -Inf

  expect_identical(x + y, Inf)
  expect_identical(y + x, Inf)
  expect_identical(x + z, -Inf)
  expect_identical(z + x, -Inf)
})
