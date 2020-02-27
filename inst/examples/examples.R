
library(vapour)
dsn <- system.file("gpkg/nc.gpkg", package = "sf", mustWork = TRUE)
## returns a list of single-element character vector
wkt <- vapour_read_geometry_text(dsn, textformat = "wkt")
## returns a list of raw vectors
wkb <- vapour_read_geometry(dsn)

purrr::walk(wkt, libgeos:::geos_test_roundtrip_wkt)
purrr::walk(wkb, ~libgeos:::geos_test_roundtrip_wkb(list(.x)))
purrr::walk(wkt, libgeos:::geos_wkt_is_parseable)
purrr::walk(wkb, ~libgeos:::geos_wkb_is_parseable(list(.x)))

purrr::walk(wkt, libgeos:::geos_wkt_to_wkb)
purrr::walk(wkb, ~libgeos:::geos_wkb_to_wkt(list(.x)))

## wkt to wkt is single-element vector
libgeos:::geos_test_roundtrip_wkt(wkt[[1]])
## comparison not exact
libgeos:::geos_test_roundtrip_wkt(wkt[[1]]) == wkt[[1]]


## wkb to wkb is a single-element list
libgeos:::geos_test_roundtrip_wkb(wkb[1])
## comparison exact
all(libgeos:::geos_test_roundtrip_wkb(wkb[1])[[1]] == wkb[[1]])


libgeos:::geos_capi_version()
libgeos:::geos_version_impl()

libgeos:::geos_test_throw_error()

# list
libgeos:::geos_wkb_is_parseable(wkb[1])

## atomic
libgeos:::geos_wkt_is_parseable(wkt[[1]])

## list to atomic
libgeos:::geos_wkb_to_wkt(wkb[1])

## atomic to list
libgeos:::geos_wkt_to_wkb(wkt[[1]])
