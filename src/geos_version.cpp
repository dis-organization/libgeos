#include <Rcpp.h>
#include <geos_c.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::string GEOSversion_c() {
  return GEOSversion();
}
