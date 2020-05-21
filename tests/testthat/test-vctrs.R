# ------------------------------------------------------------------------------
# vec_proxy() / vec_restore()

test_that("proxy is a data frame", {
  expect_identical(
    vec_proxy(tidy64(1)),
    new_data_frame(list(left = 0, right = 1))
  )
})

test_that("proxy has optional names column", {
  x <- set_names(tidy64(1), "x")
  names <- vec_proxy(x)[["tidy64:::names"]]
  expect_identical(names, "x")
})

test_that("can rountrip proxy/restore", {
  x <- tidy64(1:5)
  expect_identical(vec_restore(vec_proxy(x), x), x)
})

test_that("can rountrip named input with proxy/restore", {
  x <- set_names(tidy64(1:5))
  expect_identical(vec_restore(vec_proxy(x), x), x)
})

# ------------------------------------------------------------------------------
# vec_proxy_compare()

test_that("comparison proxy is a data frame", {
  expect_identical(
    vec_proxy_compare(tidy64(1)),
    new_data_frame(list(left = 0, right = 1))
  )
})

test_that("comparison proxy doesn't include names column", {
  x <- set_names(tidy64(1), "x")
  names <- vec_proxy_compare(x)[["tidy64:::names"]]
  expect_null(names)
})

# ------------------------------------------------------------------------------
# vec_proxy_equal()

test_that("equality proxy is a data frame", {
  expect_identical(
    vec_proxy_equal(tidy64(1)),
    new_data_frame(list(left = 0, right = 1))
  )
})

test_that("equality proxy doesn't include names column", {
  x <- set_names(tidy64(1), "x")
  names <- vec_proxy_equal(x)[["tidy64:::names"]]
  expect_null(names)
})

# ------------------------------------------------------------------------------
# vec_slice() / `[`

test_that("can slice", {
  x <- tidy64(1:5)

  expect_identical(vec_slice(x, 1), tidy64(1))
  expect_identical(x[1], tidy64(1))

  expect_identical(vec_slice(x, c(3, 2)), tidy64(c(3, 2)))
})

test_that("slicing preserves names", {
  x <- set_names(tidy64(1:2), c("x", "y"))
  expect_named(vec_slice(x, 1), "x")
  expect_named(vec_slice(x, c(2, 2)), c("y", "y"))
})

test_that("`NA_integer_` slicing returns empty character names", {
  x <- set_names(tidy64(1:2), c("x", "y"))
  expect_named(vec_slice(x, NA_integer_), "")
  expect_named(vec_slice(tidy64(1), NA_integer_), NULL)
})
