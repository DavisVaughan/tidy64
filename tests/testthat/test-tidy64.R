# ------------------------------------------------------------------------------
# new_tidy64()

test_that("can construct tidy64 from bare bones", {
  expect_s3_class(new_tidy64(), "tidy64")
  expect_identical(new_tidy64(), tidy64())
})

test_that("can construct tidy64 with bits", {
  expect_identical(new_tidy64(0, 0), tidy64(0))
  expect_identical(new_tidy64(0, 1), tidy64(1))
})

test_that("`left` and `right` are validated", {
  expect_error(new_tidy64(left = "x"), "must be a double")
  expect_error(new_tidy64(right = "x"), "must be a double")

  expect_error(new_tidy64(left = 1, right = c(1, 1)), "same size")
})

# ------------------------------------------------------------------------------
# new_tidy64_subclass()

test_that("default is equivalent to new_tidy64()", {
  expect_identical(new_tidy64_subclass(), new_tidy64())
})

test_that("can add a subclass", {
  expect_s3_class(new_tidy64_subclass(class = "foobar"), "foobar")
})

test_that("can add names", {
  expect_named(new_tidy64_subclass(tidy64(1), names = "x"), "x")
})

test_that("names are validated", {
  expect_error(new_tidy64_subclass(tidy64(1), names = 1), "or a character vector")
  expect_error(new_tidy64_subclass(tidy64(1), names = c("x", "y")), "same size as `x`")
  expect_error(new_tidy64_subclass(tidy64(1), names = NA_character_), "must not be `NA`")
})

test_that("x is validated", {
  expect_error(new_tidy64_subclass(1), "must be")
})

# ------------------------------------------------------------------------------
# names() / `names<-`()

test_that("can have NULL names", {
  expect_null(names(tidy64(1)))
})

test_that("can set names", {
  x <- set_names(tidy64(1), "x")
  expect_identical(names(x), "x")
})

test_that("names can be set to NULL", {
  x <- set_names(tidy64(1), "x")
  names(x) <- NULL
  expect_named(x, NULL)
})

test_that("names are validated", {
  x <- tidy64(1)
  expect_error(`names<-`(x, 1), "`NULL` or a character vector")
  expect_error(`names<-`(x, c("x", "y")), "same size as `x`")
})

# ------------------------------------------------------------------------------
# output

test_that("tidy64 methods have informative output", {
  verify_output(test_path("output", "test-tidy64.txt"), {
    "# names print out"
    set_names(tidy64(1), "x")
  })
})
