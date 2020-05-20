# nocov start

.onLoad <- function(libname, pkgname) {
  .Call(export_tidy64_initialize, asNamespace(pkgname))
}

# nocov end
