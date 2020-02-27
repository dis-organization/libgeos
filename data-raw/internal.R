
library(vapour)
dsn <- system.file("gpkg/nc.gpkg", package = "sf", mustWork = TRUE)
## returns a list of single-element character vector
wkt <- vapour_read_geometry_text(dsn, textformat = "wkt")
## returns a list of raw vectors
wkb <- vapour_read_geometry(dsn)

usethis::use_data(wkt, wkb, internal = TRUE, overwrite = TRUE)
