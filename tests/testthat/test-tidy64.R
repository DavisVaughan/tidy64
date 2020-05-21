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
