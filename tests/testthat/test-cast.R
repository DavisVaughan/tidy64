# ------------------------------------------------------------------------------
# default

test_that("default cast method kicks in", {
  expect_error(vec_cast(new_tidy64(), character()), class = "vctrs_error_incompatible_type")
  expect_error(vec_cast(character(), new_tidy64()), class = "vctrs_error_incompatible_type")
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

test_that("casting to double is an error if it might lose precision", {
  verify_errors({
    x1 <- as_tidy64(tidy64_global_max_lossless_double_plus_one_chr)
    x10 <- rep(x1, 10)
    expect_error(vec_cast(x1, double()), class = "tidy64_error_to_dbl_from_tidy64_might_lose_precision")
    expect_error(vec_cast(x10, double()), class = "tidy64_error_to_dbl_from_tidy64_might_lose_precision")
    expect_error(vec_cast(x1, double(), x_arg = "x", to_arg = "to"), class = "tidy64_error_to_dbl_from_tidy64_might_lose_precision")
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
  })
})