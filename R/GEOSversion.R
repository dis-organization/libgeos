#' Version of GEOS library
#'
#' Returns a string of the GEOS library version.
#'
#' On Windows this will be the rwinlib version on CRAN, not a system GEOS.
#' @return character string
#' @export
#'
#' @examples
#' GEOSversion()
GEOSversion <- function() {
  GEOSversion_c()
}
