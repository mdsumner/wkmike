#include "cpp11.hpp"
using namespace cpp11;
#include "wk-v1-reader.hpp"

#define HANDLE_CONTINUE_OR_BREAK(expr)                         \
result = expr;                                                 \
if (result == WK_ABORT_FEATURE) continue; else if (result == WK_ABORT) break

[[cpp11::linking_to(wk)]]
[[cpp11::register]]
sexp cpp_handle_xy(data_frame input, sexp handler_xptr) {
  doubles x = input["x"];
  cpp11::doubles y = input["y"];
  R_xlen_t n_features = x.size();

  WKHandlerXPtr handler(handler_xptr);

  wk_vector_meta_t vector_meta;
  WK_VECTOR_META_RESET(vector_meta, WK_POINT);
  vector_meta.size = n_features;

  wk_meta_t geometry_meta;
  WK_META_RESET(geometry_meta, WK_POINT);
  geometry_meta.size = 1;

  handler.vector_start(&vector_meta);
  double coord[4];
  int result;

  for (R_xlen_t i = 0; i < n_features; i++) {
    HANDLE_CONTINUE_OR_BREAK(handler.feature_start(&vector_meta, i));
    HANDLE_CONTINUE_OR_BREAK(handler.geometry_start(&geometry_meta, WK_PART_ID_NONE));

    coord[0] = x[i];
    coord[1] = y[i];
    HANDLE_CONTINUE_OR_BREAK(handler.coord(&geometry_meta, coord, 0));

    HANDLE_CONTINUE_OR_BREAK(handler.geometry_end(&geometry_meta, WK_PART_ID_NONE));
    HANDLE_CONTINUE_OR_BREAK(handler.feature_end(&vector_meta, i));
  }

  return handler.vector_end(&vector_meta);
}
