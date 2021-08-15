#include <cmath>
#include "cpp11.hpp"
using namespace cpp11;
namespace writable = cpp11::writable;
#include "wk-v1-handler.hpp"
#include "wk-v1-impl.c"

class BBoxHandler: public WKVoidHandler {
public:
  BBoxHandler(): xmin(R_PosInf), ymin(R_PosInf), xmax(R_NegInf), ymax(R_NegInf) {}

  int coord(const wk_meta_t* meta, const double* coord, uint32_t coord_id) {
    this->xmin = std::min(coord[0], this->xmin);
    this->ymin = std::min(coord[1], this->ymin);
    this->xmax = std::max(coord[0], this->xmax);
    this->ymax = std::max(coord[1], this->ymax);
    return WK_CONTINUE;
  }

  SEXP vector_end(const wk_vector_meta_t* meta) {
    writable::doubles output = {this->xmin, this->ymin, this->xmax, this->ymax};
    output.names() = {"xmin", "ymin", "xmax", "ymax"};
    return output;
  }

private:
  double xmin, ymin, xmax, ymax;
};

[[cpp11::linking_to(wk)]]
[[cpp11::register]]
sexp cpp_bbox_handler_new() {
  return WKHandlerFactory<BBoxHandler>::create_xptr(new BBoxHandler());
}
