test_that("default error is thrown", {
  expect_error(vec_ptype2(new_tidy64(), character()), class = "vctrs_error_incompatible_type")
  expect_error(vec_ptype2(character(), new_tidy64()), class = "vctrs_error_incompatible_type")
})

test_that("tidy64 - tidy64", {
  expect_identical(vec_ptype2(new_tidy64(), new_tidy64()), new_tidy64())
})

test_that("tidy64 - double", {
  expect_identical(vec_ptype2(new_tidy64(), double()), double())
  expect_identical(vec_ptype2(double(), new_tidy64()), double())
})

test_that("tidy64 - integer", {
  expect_identical(vec_ptype2(new_tidy64(), integer()), new_tidy64())
  expect_identical(vec_ptype2(integer(), new_tidy64()), new_tidy64())
})

test_that("tidy64 - logical", {
  expect_identical(vec_ptype2(new_tidy64(), logical()), new_tidy64())
  expect_identical(vec_ptype2(logical(), new_tidy64()), new_tidy64())
})
