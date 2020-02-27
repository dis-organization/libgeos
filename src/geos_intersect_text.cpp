#include <Rcpp.h>
#include <geos_c.h>
using namespace Rcpp;

// [[Rcpp::export]]
CharacterVector intersect_text(CharacterVector input1, CharacterVector input2,
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

// // [[Rcpp::export]]
// CharacterVector intersect_blob(RawVector input1, RawVector input2,
//                                int precision) {
//   // allocate the output
//   //CharacterVector output(input1.size());
//
//   // create the handle, reader, and writer
//   GEOSContextHandle_t context = GEOS_init_r();
//   GEOSWKBReader *wkb_reader = GEOSWKBReader_create_r(context);
//   GEOSWKBWriter *wkb_writer = GEOSWKBWriter_create_r(context);
//
//   //GEOSWKTWriter_setRoundingPrecision_r(context, wkt_writer, precision);
//
//   // allocate the variables that will all
//   // be used once in each step of the loop
//   GEOSGeometry* geometry1;
//   GEOSGeometry* geometry2;
//   GEOSGeometry* geometry_output;
//   //std::string output_wkt;
//
//  // for (int i=0; i < input1.size(); i++) {
//  const unsigned char *rawv[input1.length()];
//   //  geometry1 = GEOSWKBReader_read_r(context, wkb_reader, input1, input1.length());
//   //  geometry2 = GEOSWKBReader_read_r(context, wkb_reader, input2, input2.length());
// ///    geometry_output = GEOSIntersection_r(context, geometry1, geometry2);
// ///    output_wkt = GEOSWKTWriter_write_r(context, wkt_writer, geometry_output);
// ///    output[i] = output_wkt;
//   //}
//
//   // cleanup the reader, writer, and handle
//   GEOSWKTWriter_destroy_r(context, wkt_writer);
//   GEOSWKTReader_destroy_r(context, wkt_reader);
//   GEOS_finish_r(context);
//
//   // return the output
//   return "output";
// }
