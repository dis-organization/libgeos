#include <Rcpp.h>
#include <geos_c.h>

using namespace Rcpp;

// [[Rcpp::export]]
CharacterVector intersect_wkt(CharacterVector input1, CharacterVector input2,
                               int precision) {
  // allocate the output
  CharacterVector output(input1.size());

  // create the handle, reader, and writer
  GEOSContextHandle_t context = GEOS_init_r();
  GEOSWKTReader *wkt_reader = GEOSWKTReader_create_r(context);
  GEOSWKTWriter *wkt_writer = GEOSWKTWriter_create_r(context);
  GEOSWKTWriter_setRoundingPrecision_r(context, wkt_writer, precision);

  // allocate the variables that will all
  // be used once in each step of the loop
  GEOSGeometry* geometry1;
  GEOSGeometry* geometry2;
  GEOSGeometry* geometry_output;
  std::string output_wkt;

  for (int i=0; i < input1.size(); i++) {
    geometry1 = GEOSWKTReader_read_r(context, wkt_reader, input1[i]);
    geometry2 = GEOSWKTReader_read_r(context, wkt_reader, input2[i]);
    geometry_output = GEOSIntersection_r(context, geometry1, geometry2);
    output_wkt = GEOSWKTWriter_write_r(context, wkt_writer, geometry_output);
    output[i] = output_wkt;
  }

  // cleanup the reader, writer, and handle
  GEOSWKTWriter_destroy_r(context, wkt_writer);
  GEOSWKTReader_destroy_r(context, wkt_reader);
  GEOS_finish_r(context);

  // return the output
  return output;
}

// [[Rcpp::export]]
RawVector intersect_wkb(RawVector input1, RawVector input2) {

  // create the handle, reader, and writer
  GEOSContextHandle_t context = GEOS_init_r();
  GEOSWKBReader *wkb_reader = GEOSWKBReader_create_r(context);
  GEOSWKBWriter *wkb_writer = GEOSWKBWriter_create_r(context);

  // allocate the variables
  GEOSGeometry* geometry1;
  GEOSGeometry* geometry2;
  GEOSGeometry* geometry_output;

  const unsigned char *rawv1[input1.length()];
  const unsigned char *rawv2[input1.length()];

 for (int i=0; i < input1.size(); i++) {
   rawv1[i] = &input1[i];
   rawv2[i] = &input2[i];
 }
    geometry1 = GEOSWKBReader_read_r(context, wkb_reader, *rawv1, input1.length());
    geometry2 = GEOSWKBReader_read_r(context, wkb_reader, *rawv2, input2.length());
    geometry_output = GEOSIntersection_r(context, geometry1, geometry2);
    size_t asize;
    // inspired by https://github.com/r-spatial/sf/blob/master/src/geos.cpp#L181-L184
    unsigned char *output_wkb = GEOSWKBWriter_write_r(context, wkb_writer, geometry_output, &asize);
    // allocate the output
    Rcpp::RawVector output(asize);
    memcpy(&(output[0]), output_wkb, asize);
    GEOSFree_r(context, output_wkb);

  // cleanup the reader, writer, and handle
  GEOSWKBWriter_destroy_r(context, wkb_writer);
  GEOSWKBReader_destroy_r(context, wkb_reader);
  GEOS_finish_r(context);

  // return the output
  return output;
}
