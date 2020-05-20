# ------------------------------------------------------------------------------
# as_tidy64(<character>)

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
  x <- "9007199254740992"
  expect_identical(as.character(as_tidy64(x)), x)

  # 2^53 + 1
  x <- "9007199254740993"
  expect_identical(as.character(as_tidy64(x)), x)

  # -2^53
  x <- "-9007199254740992"
  expect_identical(as.character(as_tidy64(x)), x)

  # -2^53 - 1
  x <- "-9007199254740993"
  expect_identical(as.character(as_tidy64(x)), x)
})

test_that("can represent TIDY64_MAX but not more", {
  x <- as_tidy64(tidy64_global_max_chr())
  expect_identical(as.character(as_tidy64(x)), tidy64_global_max_chr())

  x <- as_tidy64(tidy64_global_min_chr())
  expect_identical(as.character(as_tidy64(x)), tidy64_global_min_chr())

  TIDY64_MAX_AND_1 <- "9223372036854775808"
  TIDY64_MIN_AND_1 <- "-9223372036854775808"

  expect_warning({
    expect_identical(as_tidy64(TIDY64_MAX_AND_1), as_tidy64(NA))
  })
  expect_warning({
    expect_identical(as_tidy64(TIDY64_MIN_AND_1), as_tidy64(NA))
  })
})
