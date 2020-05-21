# ------------------------------------------------------------------------------
# as_tidy64(<default>)

test_that("default method has nice error", {
  verify_errors({
    expect_error(as_tidy64(factor("x")))
  })
})

# ------------------------------------------------------------------------------
# as_tidy64(<double>) / as.double()

test_that("can roundtrip basic doubles", {
  x <- c(-2, -1, 1, 2)
  expect_identical(as.double(as_tidy64(x)), x)
})

test_that("keeps names", {
  expect_named(as.double(set_names(tidy64(1))), "1")
  expect_named(as_tidy64(set_names(1)), "1")
})

test_that("can roundtrip zero", {
  expect_identical(as.double(as_tidy64(0)), 0)
})

test_that("can convert NaN and NA", {
  expect_identical(as.double(as_tidy64(NaN)), NA_real_)
  expect_identical(as.double(as_tidy64(NA_real_)), NA_real_)
})

test_that("can roundtrip doubles past int max / min", {
  x <- c(tidy64_global_int_max + 1, tidy64_global_int_min - 1)
  expect_identical(as.double(as_tidy64(x)), x)
})

test_that("can roundtrip max/min allowed double input", {
  max <- tidy64_global_max_dbl()
  min <- tidy64_global_min_dbl()

  expect_warning({
    x <- as.double(as_tidy64(max))
  })
  expect_warning({
    y <- as.double(as_tidy64(min))
  })

  expect_identical(x, max)
  expect_identical(y, min)
})

test_that("next representable double above max/min double results in NA", {
  # Values in this range have a step size of 1024 (512 on either side)
  next_representable_dbl_above_max <- tidy64_global_max_dbl() + 512
  next_representable_dbl_below_min <- tidy64_global_min_dbl() - 512

  expect_warning({
    x <- as_tidy64(next_representable_dbl_above_max)
  })
  expect_warning({
    y <- as_tidy64(next_representable_dbl_below_min)
  })

  expect_identical(x, tidy64(NA))
  expect_identical(y, tidy64(NA))
})

test_that("double -> tidy64 OOB warnings are informative", {
  verify_errors({
    x1 <- tidy64_global_max_dbl() + 512
    x2 <- vec_rep(x1, 2)
    x10 <- vec_rep(x1, 10)
    expect_warning(as_tidy64(x1))
    expect_warning(as_tidy64(x2))
    expect_warning(as_tidy64(x10))
  })
})

test_that("can handle infinity", {
  expect_warning({
    x <- as_tidy64(Inf)
  })
  expect_warning({
    y <- as_tidy64(-Inf)
  })

  expect_identical(x, tidy64(NA))
  expect_identical(y, tidy64(NA))
})

test_that("no warning when converting doubles above max lossless double to tidy64", {
  # Values like `x + 512 + 1` might not be exactly representable, but the
  # resuling double of that operation (which is `x + 512`) is a whole number
  # that can be converted to int64_t losslessly, so no warning is thrown here.

  x <- tidy64_global_max_lossless_double
  y <- tidy64_global_min_lossless_double

  expect_warning(as_tidy64(x), NA)
  expect_warning(as_tidy64(x + 512), NA)
  expect_warning(as_tidy64(x + 512 + 1), NA)

  expect_warning(as_tidy64(y), NA)
  expect_warning(as_tidy64(y - 512), NA)
  expect_warning(as_tidy64(x + 512 - 1), NA)
})

test_that("as.double() warns if maybe losing precision", {
  x1 <- as_tidy64(tidy64_global_max_lossless_double_plus_one_chr)
  x10 <- rep(x1, 10)
  expect_warning(as.double(x1))
  expect_warning(as.double(x10))
})

# ------------------------------------------------------------------------------
# as_tidy64(<integer>) / as.integer()

test_that("can roundtrip basic integers", {
  x <- c(-2L, -1L, 1L, 2L)
  expect_identical(as.integer(as_tidy64(x)), x)
})

test_that("keeps names", {
  expect_named(as.integer(set_names(tidy64(1))), "1")
  expect_named(as_tidy64(set_names(1L)), "1")
})

test_that("can roundtrip zero", {
  expect_identical(as.integer(as_tidy64(0L)), 0L)
})

test_that("can convert NA", {
  expect_identical(as.integer(as_tidy64(NA_integer_)), NA_integer_)
})

test_that("as.integer() warns if outside int range", {
  verify_errors({
    x1 <- as_tidy64(tidy64_global_int_max + 1)
    x10 <- rep(x1, 10)
    expect_identical(expect_warning(as.integer(x1)), NA_integer_)
    expect_identical(expect_warning(as.integer(x10)), rep(NA_integer_, 10))
  })
})

# ------------------------------------------------------------------------------
# as_tidy64(<logical>)

test_that("can roundtrip logicals", {
  x <- c(TRUE, FALSE)
  expect_identical(as.logical(as_tidy64(x)), x)
})

test_that("keeps names", {
  expect_named(as.logical(set_names(tidy64(1))), "1")
  expect_named(as_tidy64(set_names(TRUE)), "TRUE")
})

test_that("can convert NA", {
  expect_identical(as.logical(as_tidy64(NA)), NA)
})

test_that("as.integer() forces any non-zero value to TRUE", {
  x <- as_tidy64(5)
  expect_identical(as.logical(x), TRUE)
})

# ------------------------------------------------------------------------------
# as_tidy64(<character>) / as.character()

test_that("keeps names", {
  expect_named(as.character(set_names(tidy64(1))), "1")
  expect_named(as_tidy64(set_names("1")), "1")

  expect_named(expect_warning(as_tidy64(set_names("x"))), "x")
})

test_that("can parse simple case", {
  expect_identical(as_tidy64("1"), as_tidy64(1))
  expect_identical(as_tidy64("0"), as_tidy64(0))
})

test_that("can parse negative numbers", {
  expect_identical(as_tidy64("-1"), as_tidy64(-1))
  expect_identical(as_tidy64("-500"), as_tidy64(-500))
})

test_that("can fail on non-numbers", {
  expect_warning({
    expect_identical(as_tidy64("x"), as_tidy64(NA))
    expect_identical(as_tidy64("xx"), as_tidy64(NA))
    expect_identical(as_tidy64(" x"), as_tidy64(NA))
  })
})

test_that("can parse blank string as `NA`", {
  expect_warning({
    expect_identical(as_tidy64(""), as_tidy64(NA))
  })
})

test_that("can parse whitespace as `NA`", {
  expect_warning({
    expect_identical(as_tidy64(" "), as_tidy64(NA))
    expect_identical(as_tidy64("  "), as_tidy64(NA))
  })
})

test_that("numbers must be followed by space are allowed", {
  expect_identical(as_tidy64("1 "), as_tidy64(1))
  expect_identical(as_tidy64("1  "), as_tidy64(1))
  expect_identical(as_tidy64("12  "), as_tidy64(12))
})

test_that("numbers can only be followed by whitespace", {
  expect_warning({
    expect_identical(as_tidy64("1 1"), as_tidy64(NA))
    expect_identical(as_tidy64("1x"), as_tidy64(NA))
  })
})

test_that("NA_character_ can be converted", {
  expect_identical(as_tidy64(NA_character_), as_tidy64(NA))
})

test_that("can represent numbers above maximum representable double losslessly", {
  # 2^53
  x <- tidy64_global_max_lossless_double_chr
  expect_identical(as.character(as_tidy64(x)), x)

  # 2^53 + 1
  x <- tidy64_global_max_lossless_double_plus_one_chr
  expect_identical(as.character(as_tidy64(x)), x)

  # -2^53
  x <- tidy64_global_min_lossless_double_chr
  expect_identical(as.character(as_tidy64(x)), x)

  # -2^53 - 1
  x <- tidy64_global_min_lossless_double_minus_one_chr
  expect_identical(as.character(as_tidy64(x)), x)
})

test_that("can represent TIDY64_MAX but not more", {
  x <- as_tidy64(tidy64_global_max_as_chr())
  expect_identical(as.character(as_tidy64(x)), tidy64_global_max_as_chr())

  x <- as_tidy64(tidy64_global_min_as_chr())
  expect_identical(as.character(as_tidy64(x)), tidy64_global_min_as_chr())

  TIDY64_MAX_AND_1 <- "9223372036854775808"
  TIDY64_MIN_AND_1 <- "-9223372036854775808"

  expect_warning({
    expect_identical(as_tidy64(TIDY64_MAX_AND_1), as_tidy64(NA))
  })
  expect_warning({
    expect_identical(as_tidy64(TIDY64_MIN_AND_1), as_tidy64(NA))
  })
})

# ------------------------------------------------------------------------------
# errors

test_that("force functions have informative errors", {
  verify_output(test_path("output", "test-force.txt"), {
    "# default method has nice error"
    as_tidy64(factor("x"))

    "# double -> tidy64 OOB warnings are informative"
    x1 <- tidy64_global_max_dbl() + 512
    x2 <- vec_rep(x1, 2)
    x10 <- vec_rep(x1, 10)
    as_tidy64(x1)
    as_tidy64(x2)
    as_tidy64(x10)

    "as.double() warns if maybe losing precision"
    x1 <- as_tidy64(tidy64_global_max_lossless_double_plus_one_chr)
    x10 <- rep(x1, 10)
    as.double(x1)
    as.double(x10)

    "# as.integer() warns if outside int range"
    x1 <- as_tidy64(tidy64_global_int_max + 1)
    x10 <- rep(x1, 10)
    as.integer(x1)
    as.integer(x10)
  })
})
