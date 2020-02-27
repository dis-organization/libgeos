#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _libgeos_GEOSversion_c();

static const R_CallMethodDef CallEntries[] = {
    {"_libgeos_GEOSversion_c", (DL_FUNC) &_libgeos_GEOSversion_c, 0},
    {NULL, NULL, 0}
};

void R_init_libgeos(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
