# ------------------------------------------------------------------------------
# default

test_that("default cast method kicks in", {
  expect_error(vec_cast(new_tidy64(), character()), class = "vctrs_error_incompatible_type")
  expect_error(vec_cast(character(), new_tidy64()), class = "vctrs_error_incompatible_type")
})

# ------------------------------------------------------------------------------
# tidy64 <-> tidy64

test_that("can cast to self", {
  expect_identical(vec_cast(tidy64(1), tidy64(2)), tidy64(1))
})

# ------------------------------------------------------------------------------
# tidy64 <-> double

test_that("can cast both ways", {
  expect_identical(vec_cast(tidy64(2), double()), 2)
  expect_identical(vec_cast(2, new_tidy64()), tidy64(2))
})

test_that("can cast NA both ways", {
  expect_identical(vec_cast(tidy64(NA), double()), NA_real_)
  expect_identical(vec_cast(NA_real_, new_tidy64()), tidy64(NA))
})

test_that("keeps names", {
  expect_named(vec_cast(set_names(tidy64(1)), double()), "1")
  expect_named(vec_cast(set_names(1), tidy64()), "1")
})

test_that("casting to double is an error if it might lose precision", {
  verify_errors({
    x1 <- as_tidy64(tidy64_global_max_lossless_double_plus_one_chr)
    x10 <- rep(x1, 10)
    expect_error(vec_cast(x1, double()), class = "tidy64_error_to_dbl_from_tidy64_oob_precision")
    expect_error(vec_cast(x10, double()), class = "tidy64_error_to_dbl_from_tidy64_oob_precision")
    expect_error(vec_cast(x1, double(), x_arg = "x", to_arg = "to"), class = "tidy64_error_to_dbl_from_tidy64_oob_precision")
  })
})

test_that("casting to tidy64 from double is an error if OOB", {
  verify_errors({
    x1 <- .Machine$double.xmax
    x10 <- rep(x1, 10)
    expect_error(vec_cast(x1, new_tidy64()), class = "tidy64_error_to_tidy64_from_dbl_oob")
    expect_error(vec_cast(x10, new_tidy64()), class = "tidy64_error_to_tidy64_from_dbl_oob")
    expect_error(vec_cast(x1, new_tidy64(), x_arg = "x", to_arg = "to"), class = "tidy64_error_to_tidy64_from_dbl_oob")
  })
})

test_that("casting to tidy64 from double is an error if fractional", {
  verify_errors({
    x1 <- 1.5
    x10 <- rep(x1, 10)
    expect_error(vec_cast(x1, new_tidy64()), class = "tidy64_error_to_tidy64_from_dbl_lossy_fractional")
    expect_error(vec_cast(x10, new_tidy64()), class = "tidy64_error_to_tidy64_from_dbl_lossy_fractional")
    expect_error(vec_cast(x1, new_tidy64(), x_arg = "x", to_arg = "to"), class = "tidy64_error_to_tidy64_from_dbl_lossy_fractional")
  })
})

# ------------------------------------------------------------------------------
# tidy64 <-> integer

test_that("can cast both ways", {
  expect_identical(vec_cast(tidy64(2), integer()), 2L)
  expect_identical(vec_cast(2L, new_tidy64()), tidy64(2))
})

test_that("can cast NA both ways", {
  expect_identical(vec_cast(tidy64(NA), integer()), NA_integer_)
  expect_identical(vec_cast(NA_integer_, new_tidy64()), tidy64(NA))
})

test_that("keeps names", {
  expect_named(vec_cast(set_names(tidy64(1)), integer()), "1")
  expect_named(vec_cast(set_names(1L), tidy64()), "1")
})

test_that("casting to integer is an error if it is oob", {
  verify_errors({
    x1 <- as_tidy64(.Machine$integer.max + 1)
    x10 <- rep(x1, 10)
    expect_error(vec_cast(x1, integer()), class = "tidy64_error_to_int_from_tidy64_oob")
    expect_error(vec_cast(x10, integer()), class = "tidy64_error_to_int_from_tidy64_oob")
    expect_error(vec_cast(x1, integer(), x_arg = "x", to_arg = "to"), class = "tidy64_error_to_int_from_tidy64_oob")
  })
})

# ------------------------------------------------------------------------------
# tidy64 <-> logical

test_that("can cast both ways", {
  expect_identical(vec_cast(tidy64(1), logical()), TRUE)
  expect_identical(vec_cast(tidy64(0), logical()), FALSE)
  expect_identical(vec_cast(TRUE, new_tidy64()), tidy64(1))
  expect_identical(vec_cast(FALSE, new_tidy64()), tidy64(0))
})

test_that("can cast NA both ways", {
  expect_identical(vec_cast(tidy64(NA), logical()), NA)
  expect_identical(vec_cast(NA, new_tidy64()), tidy64(NA))
})

test_that("keeps names", {
  expect_named(vec_cast(set_names(tidy64(1)), logical()), "1")
  expect_named(vec_cast(set_names(TRUE), tidy64()), "TRUE")
})

# TODO: Need better error message
test_that("casting to logical is an error if it is not 1 or 0", {
  # verify_errors({
  #   x1 <- as_tidy64(2)
  #   x10 <- rep(x1, 10)
  #   expect_error(vec_cast(x1, logical()), class = "tidy64_error_to_int_from_tidy64_oob")
  #   expect_error(vec_cast(x10, logical()), class = "tidy64_error_to_int_from_tidy64_oob")
  #   expect_error(vec_cast(x1, logical(), x_arg = "x", to_arg = "to"), class = "tidy64_error_to_int_from_tidy64_oob")
  # })

  x1 <- as_tidy64(2)
  x2 <- as_tidy64(-2)
  expect_error(vec_cast(x1, logical()))
  expect_error(vec_cast(x2, logical()))
})

# ------------------------------------------------------------------------------

test_that("cast methods have informative errors", {
  verify_output(test_path("output", "test-cast.txt"), {
    "# casting to double is an error if it might lose precision"
    x1 <- as_tidy64(tidy64_global_max_lossless_double_plus_one_chr)
    x10 <- rep(x1, 10)
    vec_cast(x1, double())
    vec_cast(x10, double())
    vec_cast(x1, double(), x_arg = "x", to_arg = "to")

    "# casting to tidy64 from double is an error if OOB"
    x1 <- .Machine$double.xmax
    x10 <- rep(x1, 10)
    vec_cast(x1, new_tidy64())
    vec_cast(x10, new_tidy64())
    vec_cast(x1, new_tidy64(), x_arg = "x", to_arg = "to")

    "# casting to tidy64 from double is an error if fractional"
    x1 <- 1.5
    x10 <- rep(x1, 10)
    vec_cast(x1, new_tidy64())
    vec_cast(x10, new_tidy64())
    vec_cast(x1, new_tidy64(), x_arg = "x", to_arg = "to")

    "# casting to integer is an error if it is oob"
    x1 <- as_tidy64(.Machine$integer.max + 1)
    x10 <- rep(x1, 10)
    vec_cast(x1, integer())
    vec_cast(x10, integer())
    vec_cast(x1, integer(), x_arg = "x", to_arg = "to")
  })
})
