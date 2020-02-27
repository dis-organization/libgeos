
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

try(libgeos:::geos_test_throw_error(), silent = TRUE)

# list
libgeos:::geos_wkb_is_parseable(wkb[1])

## atomic
libgeos:::geos_wkt_is_parseable(wkt[[1]])

## list to atomic
libgeos:::geos_wkb_to_wkt(wkb[1])

## atomic to list
libgeos:::geos_wkt_to_wkb(wkt[[1]])


## ----------------------- MDSumner

## example from DD's blog
wkt <- libgeos:::wkt
wkb <- libgeos:::wkb
libgeos:::intersect_wkt(wkt[[1]], wkt[[2]], 1L)


## new example with wkb
libgeos:::intersect_wkb(wkb[[1]], wkb[[2]])

